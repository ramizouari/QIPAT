//
// Created by ramizouari on 01/12/2021.
//

#ifndef __ML_H__
#define __ML_H__
#include "algebra/abstract_algebra.h"
#include "topology/optimisation.h"
#include "linear_algebra/linear_algebra.h"
#include "functional/zip.h"
#include "functional/functional.h"
#include <algorithm>
#include <numeric>
#include <queue>
/*
* Basic Machine Learning Support
*/
namespace ml {
    using namespace linalg;
    using namespace topology;
    using namespace functional;
    class ml_model {
    public:
        virtual ml_model &fit(const d_matrix <real> &X, const d_vector <real> &y) = 0;

        virtual d_vector <real> predict(const d_matrix <real> &X) const = 0;

        virtual real score(const d_matrix <real> &X, const d_vector <real> &y) const = 0;
    };

/**
* @brief Linear Regression
* @refitem Linear Regression,
* @Input
* n p-dimensional samples X
* @Cost
* Mean Square Error
* @Training
* Solve the normal Equation
* @Output
* n samples. each representing the predicted value
*/
    class linear_regression : public ml_model {
        d_vector <real> w;
    public:
        ml_model &fit(const d_matrix <real> &X, const d_vector <real> &y) override {
            w = (X.T() * X).solve(X.T() * y);
            return *this;
        }

        d_vector <real> predict(const d_matrix <real> &X) const override {
            return X * w;
        }

        real score(const d_matrix <real> &X, const d_vector <real> &y) const override {
            auto y_pred = X * w;
            real err = 0;
            for (auto [p, s]: zip(y_pred, y))
                err += pow(p - s, 2);
            return err;
        }
    };

/**
* Logistic Regression
* @Input
* n p-dimensional samples X
* @DecisionFunction
* n samples, each representing the probability of belonging to class 1 
* @Cost
* Cross Entropy loss function
* @Training
* Minimise Cost Function
* @Output
* n samples. each representing the correspending class 
*/
    class logistic_regression : public ml_model {
        d_vector <real> w;
    public:
        int limit = 2000;

        ml_model &fit(const d_matrix <real> &X, const d_vector <real> &y) override {
            derivator <d_vector<real>, real, d_vector<real>> D;
            barzilai_borwein_gradient_descent < d_vector < real > , real, L2_inner_product < real, d_vector < real>>>
            GD(D, 1e-3);
            int k = 0;
            w = GD.argmin([&X, &y, &k](const d_vector <real> &u) -> std::pair<real, d_vector < real>> {
                k++;
                d_vector <real> y_pred = pointwise_function([](auto s) {
                    return 1 / (1 + std::exp(-s));
                }, X * u), residual = y - y_pred, df{v_shape{(int) X.col_dim()}};
                real err = 0;
                for (auto [p, q]: zip(y, y_pred))
                    err += p == 0 ? -std::log(1 - q) : -std::log(q);
                err /= X.row_dim();
                for (auto [R, r]: zip(X, residual))
                    for (auto [g, s]: zip(df, R))
                        g -= s * r / X.row_dim();
                return std::make_pair(std::move(err), std::move(df));
            },d_vector < real > {v_shape{(int) X.col_dim()}}, limit);
            return *this;
        }

        d_vector <real> boundary_function(const d_matrix <real> &X) const {
            return X * w;
        }

        d_vector <real> decision_function(const d_matrix <real> &X) const {
            return pointwise_function([](auto s) {
                return 1 / (1 + std::exp(-s));
            }, boundary_function(X));
        }

        d_vector <real> predict(const d_matrix <real> &X) const {
            auto y = decision_function(X);
            for (auto &s: y)
                s = std::round(s);
            return y;
        }

        real score(const d_matrix <real> &X, const d_vector <real> &y) const override {
            auto y_pred = predict(X);
            int a = 0;
            for (auto [s, p]: zip(y, y_pred))
                if (s == p)
                    a++;
            return a / (real) y.dim();
        }

        real error(const d_matrix <real> &X, const d_vector <real> &y) const {
            auto y_pred = decision_function(X);
            real err = 0;
            for (auto [p, q]: zip(y, y_pred))
                err += p == 0 ? -std::log(1 - q) : -std::log(q);
            return err / y.dim();
        }
    };


    auto xlogy(auto x, auto y) {
        if (x == 0)
            return 0;
        return x * std::log(y);
    }


/**
* MultiLogistic Regression
* @Input
* n p-dimensional samples X
* @DecisionFunction
* n C-dimensional samples Y. for each sample, the k'th coordinate represents the probability that Y belongs
* to the k'th class
* @Cost
* Cross Entropy loss function
* @Training
* Minimise Cost Functon
* @Output
* n samples. each representing the correspending class
*/
    class multilogistic_regression : public ml_model {
        d_matrix <real> W;
    public:
        int limit = 2000;
        int C;
        real lambda = 0.1;

        multilogistic_regression(real lambda) : lambda(lambda) {}

        ml_model &fit(const d_matrix <real> &X, const d_vector <real> &y) override {
            d_vector <real> w;
            C = 0;
            for (auto s: y)
                C = std::max(C, (int) s);
            C++;
            d_matrix <real> Y(0, m_shape{(int) y.dim(), C});
            for (auto [s, R]: zip(y, Y))
                R[(int) s] = 1;
            derivator <d_vector<real>, real, d_vector<real>> D;
            barzilai_borwein_gradient_descent < d_vector < real > , IR, L2_inner_product < real, d_vector < real>>>
            GD(D, 1e-3);
            int k = 0;
            w = GD.argmin([&X, &y, &k, C = this->C, lambda = this->lambda](const d_vector <real> &u) -> std::pair<real,
                    d_vector < real>> {
                k++;
                d_matrix <real> U(0, m_shape{(int) X.col_dim(), C});
                for (int i = 0; i < X.col_dim(); i++)
                    for (int j = 0; j < C; j++)
                        U[i][j] = u[i * C + j];
                d_matrix <real> Y_pred = X * U;
                for (auto &y_pred: Y_pred) {
                    for (auto &s: y_pred)
                        s = std::exp(s);
                    real r = std::reduce(y_pred.begin(), y_pred.end());
                    for (auto &s: y_pred)
                        s /= r;
                }
                real err = 0;
                d_vector <real> du(v_shape{(int) u.dim()});
                int i = 0;
                for (auto [p, Q, x]: zip(y, Y_pred, X)) {
                    int k = (int) p;
                    err -= std::log(Q[k]);
                    for (int h = 0; h < X.col_dim(); h++)
                        for (int r = 0; r < C; r++)
                            du[h * C + r] += x[h] * Q[r];
                    for (int h = 0; h < X.col_dim(); h++)
                        du[h * C + k] -= x[h];
                    i++;
                }
                du += lambda * u;
                du /= X.row_dim() * C;
                for (auto &s: u)
                    err += lambda * s * s / 2;
                err /= X.row_dim() * C;
                return std::make_pair(err, du);
            }, d_vector < real > {v_shape{(int) X.col_dim() * C}}, limit);
            W = d_matrix<real>(0, m_shape{(int) X.col_dim(), C});
            for (int i = 0; i < X.col_dim(); i++)
                for (int j = 0; j < C; j++)
                    W[i][j] = w[i * C + j];
            return *this;
        }

        d_matrix <real> boundary_function(const d_matrix <real> &X) const {
            return X * W;
        }

        d_matrix <real> decision_function(const d_matrix <real> &X) const {
            auto Y_pred = boundary_function(X);
            for (auto &y_pred: Y_pred) {
                for (auto &s: y_pred)
                    s = std::exp(s);
                real r = std::reduce(y_pred.begin(), y_pred.end());
                for (auto &s: y_pred)
                    s /= r;
            }
            return Y_pred;
        }

        d_vector <real> predict(const d_matrix <real> &X) const {
            auto Y = decision_function(X);
            d_vector <real> y_pred(v_shape{(int) X.row_dim()});
            for (auto [y, s]: zip(Y, y_pred)) {
                int k = 0;
                real M = -1;
                for (int i = 0; i < C; i++)
                    if (y[i] > M) {
                        k = i;
                        M = y[i];
                    }
                s = k;
            }
            return y_pred;
        }

        real score(const d_matrix <real> &X, const d_vector <real> &y) const override {
            auto y_pred = predict(X);
            int a = 0;
            for (auto [s, p]: zip(y, y_pred))
                if (s == p)
                    a++;
            return a / static_cast<real>(y.dim());
        }

        real error(const d_matrix <real> &X, const d_vector <real> &y) const {
            auto Y_pred = decision_function(X);
            real err = 0;
            for (auto [p, Q]: zip(y, Y_pred))
                err -= std::log(Q[(int) p]);
            err /= X.row_dim();
            return err;
        }
    };

/**
* K-NearestNeighbours Classifier
* @Input
* n p-dimensional samples X
* @DecisionFunction
* n C-dimensional samples Y. for each sample, the k'th coordinate represents the probability that Y belongs
* to the k'th class
* @Cost
* None
* @Training
* Memorize given samples
* @Output
* n samples. each representing the correspending class
*/

    template<typename metric=L2_inner_product <real, d_vector<real>>>
    class k_nearest_neighbour_classifier : public ml_model {
        d_matrix <real> X;
        d_vector <real> y;
        inline static constexpr metric d = metric{};
    public:
        int k;

        k_nearest_neighbour_classifier(int k = 5) : k(k) {}

        ml_model &fit(const d_matrix <real> &_X, const d_vector <real> &_y) override {
            X = _X;
            y = _y;
            return *this;
        }

        d_vector <real> predict(const d_matrix <real> &_X) const override {
            d_vector <real> _y(v_shape{(int) _X.row_dim()});
            for (auto [_x, _s]: zip(_X, _y)) {
                std::priority_queue<std::pair<real, real>> P;
                for (auto [x, s]: zip(X, y)) {
                    P.emplace(d.distance(x, _x), s);
                    if (P.size() > k)
                        P.pop();
                }
                std::map<int, int> occurence;
                int chosen_class = 0;
                int max_votes = 0;
                while (!P.empty()) {
                    auto [distance, s] = P.top();
                    P.pop();
                    occurence[s]++;
                    if (occurence[s] >= max_votes) {
                        chosen_class = s;
                        max_votes = occurence[s];
                    }
                }
                _s = chosen_class;
            }
            return _y;
        }

        real score(const d_matrix <real> &X, const d_vector <real> &y) const override {
            auto y_pred = predict(X);
            int a = 0;
            for (auto [s, p]: zip(y, y_pred))
                if (s == p)
                    a++;
            return a / static_cast<real>(y.dim());
        }
    };

    template<typename metric = L2_inner_product <real, d_vector<real>>>
    class k_nearest_neighbour_regression : public ml_model {
        d_matrix <real> X;
        d_vector <real> y;
        inline static constexpr metric d = metric{};
    public:
        int k = 5;

        ml_model &fit(const d_matrix <real> &_X, const d_vector <real> &_y) override {
            X = _X;
            y = _y;
            return *this;
        }

        d_vector <real> predict(const d_matrix <real> &_X) const override {
            d_vector <real> _y(v_shape{(int) _X.row_dim()});
            for (auto [_x, _s]: zip(_X, _y)) {
                std::priority_queue<std::pair<real, real>> P;
                for (auto [x, s]: zip(X, y)) {
                    P.emplace(d.distance(x, _x), s);
                    if (P.size() > k)
                        P.pop();
                }
                _s = 0;
                while (!P.empty()) {
                    auto [distance, s] = P.top();
                    P.pop();
                    _s += s;
                }
                _s /= k;
            }
            return _y;
        }

        real score(const d_matrix <real> &X, const d_vector <real> &y) const override {
            auto y_pred = predict(X);
            int a = 0;
            for (auto [s, p]: zip(y, y_pred))
                if (s == p)
                    a++;
            return a / static_cast<real>(y.dim());
        }
    };
}
#endif //__ML_H__
