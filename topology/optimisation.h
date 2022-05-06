//
// Created by ASUS on 01/12/2021.
//

#ifndef __OPTIMISATION__
#define __OPTIMISATION__
#include "../linear_algebra/linear_algebra.h"
#include "../algebra/abstract_algebra.h"
#include "topology.h"
#include <functional>

template<int n>
s_vector<real,n> point_wise_divide(const s_vector<real,n> &x,const s_vector<real,n> &y)
{
    s_vector<real,n> z;
    for(int i=0;i<n;i++)
        z[i]=x[i]/y[i];
    return z;
}

template<int n,int m>
s_vector<real,n> get_column(const s_matrix<real,n,m> &A,int k)
{
    s_vector<real,n> C;
    for(int i=0;i<n;i++)
        C[i]=A[i][k];
    return C;
}

template<int n>
real max(const s_vector<real,n> &x)
{
    real r=x[0];
    for(auto s:x)
        r=std::max(r,s);
    return r;
}

template<int n>
int argmax(const s_vector<real,n> &x)
{
    int k=0;
    for(int i=1;i<n;i++) if(x[i]>x[k])
            k=i;
    return k;
}

template<int n, int m>
s_vector<real,m> simplex(
        const s_vector<real,m>& _Z,
        const s_matrix<real,n, m>& _A,
        s_vector<real,n> b)
{
    s_vector<real, n + m > Z;
    for (int i = 0; i < m; i++)
        Z[i] = _Z[i];
    s_matrix<real,n, n + m>A;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
            A[i][j] = _A[i][j];
    for (int i = m; i < n + m; i++)
        A[i - m][i] = 1;
    while (max(Z) > 0)
    {
        auto q = argmax(Z);
        int p = -1;
        auto c = point_wise_divide(b,get_column(A,q));
        for (int k = 0; k < n; k++)
            if (A[k][q] > 0 && c[k] >= 0 && (p == -1 || c[k] < c[p]))
                p = k;
        if (p == -1)
            break;
        for (int i = 0; i < n; i++) if (i != p)
            {
                auto k=A[i][q];
                b[i] -= (k / A[p][q]) * b[p];
                for(int j=0;j<n+m;j++)
                    A[i][j] -= (k / A[p][q]) * A[p][j];
                A[i][q] = 0;

            }
        auto k=Z[q];
        for(int j=0;j<n+m;j++)
            Z[j] -= (k / A[p][q]) * A[p][j];
        Z[q] = 0;
    }
    s_vector<real,n + m> h;
    for (int i = 0; i < n; i++)
        h[i] = b[i];
    s_matrix<real,n + m, n + m> Q;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n + m; j++)
            Q[i][j] = A[i][j];
    int r = 0;
    for (int i = 0; i < n + m ; i++)
        if (Z[i] < 0)
        {
            Q[n + r++][i] = 1;
            for (int j = 0; j < n; j++)
                A[j][i] = 0;
        }
    s_vector<real,m> d;
    auto g = Q.solve(h);
    for (int i = 0; i < m; i++)
        d[i] = g[i];
    return d;
}


d_vector<real> point_wise_divide(const d_vector<real> &x,const d_vector<real> &y)
{
    int n=x.dim();
    d_vector<real> z(v_shape{n});
    for(int i=0;i<n;i++)
        z[i]=x[i]/y[i];
    return z;
}

d_vector<real> get_column(const d_matrix<real> &A,int k)
{
    int n=A.row_dim(),m=A.col_dim();
    d_vector<real> C(v_shape{m});
    for(int i=0;i<n;i++)
        C[i]=A[i][k];
    return C;
}

real max(const d_vector<real> &x)
{
    real r=x[0];
    for(auto s:x)
        r=std::max(r,s);
    return r;
}

int argmax(const d_vector<real> &x)
{
    int k=0,n=x.dim();
    for(int i=1;i<n;i++) if(x[i]>x[k])
        k=i;
    return k;
}

d_vector<real> simplex(
        const d_vector<real>& _Z,
        const d_matrix<real>& _A,
        d_vector<real> b)
{
    int n=b.dim(),m=_Z.dim();
    d_vector<real> Z(v_shape{n+m});
    for (int i = 0; i < m; i++)
        Z[i] = _Z[i];
    d_matrix<real>A(0,m_shape{n,n+m});
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
            A[i][j] = _A[i][j];
    for (int i = m; i < n + m; i++)
        A[i - m][i] = 1;
    while (max(Z) > 0)
    {
        auto q = argmax(Z);
        int p = -1;
        auto c = point_wise_divide(b,get_column(A,q));
        for (int k = 0; k < n; k++)
            if (A[k][q] > 0 && c[k] >= 0 && (p == -1 || c[k] < c[p]))
                p = k;
        if (p == -1)
            break;
        for (int i = 0; i < n; i++) if (i != p)
            {
                auto k=A[i][q];
                b[i] -= (k / A[p][q]) * b[p];
                for(int j=0;j<n+m;j++)
                    A[i][j] -= (k / A[p][q]) * A[p][j];
                A[i][q] = 0;

            }
        auto k=Z[q];
        for(int j=0;j<n+m;j++)
            Z[j] -= (k / A[p][q]) * A[p][j];
        Z[q] = 0;
    }
    d_vector<real> h(v_shape{n+m});
    for (int i = 0; i < n; i++)
        h[i] = b[i];
    d_matrix<real> Q(0,m_shape{n+m,n+m});
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n + m; j++)
            Q[i][j] = A[i][j];
    int r = 0;
    for (int i = 0; i < n + m ; i++)
        if (Z[i] < 0)
        {
            Q[n + r++][i] = 1;
            for (int j = 0; j < n; j++)
                A[j][i] = 0;
        }
    d_vector<real> d(v_shape{m});
    auto g = Q.solve(h);
    for (int i = 0; i < m; i++)
        d[i] = g[i];
    return d;
}

template<typename E,real_type IK=IR,typename Norm=L2_inner_product<real,E>>
class gradient_descent
{
    inline static constexpr Norm N=Norm();
protected:
    IK p=.05;
    IK eps;
    derivator<E,real,E>& D;
public:
    gradient_descent(derivator<E,IK,E> &d,IK _eps=1e-3):D(d),eps(_eps) {}
    E argmin(const std::function<IK(E)>& f,E x) const
    {
        for (; N.norm(D.gradient(f, x)) > eps; x -= p * D.gradient(f, x));
        return x;
    }
    E argmin(const std::function<IK(E)>& f, E x,int L) const
    {
        for (; N.norm(D.gradient(f, x)) > eps && L--; x -= p * D.gradient(f, x));
        return x;
    }
    E argmin(const std::function<std::pair<IK,E>(E)>& f, E x) const
    {
        auto P = f(x);
        while (N.norm(P.second) > eps)
        {
            x -= p * P.second;
            P = f(x);
        }
        return x;
    }

    E argmin(const std::function<std::pair<real, E>(E)>& f, E x,int L) const
    {
        auto P = f(x);
        while (N.norm(P.second) > eps && L--)
        {
            x -= p * P.second;
            P = f(x);
        }
        return x;
    }

};

template<typename E,real_type IK=IR,typename InnerProduct=L2_inner_product<IK,E>>
class barzilai_borwein_gradient_descent
{
    IK p=.1;
    IK eps=1e-8;
    derivator<E,real,E>& D;
    inline static constexpr InnerProduct B = InnerProduct();
public:
    barzilai_borwein_gradient_descent(derivator<E, IK,E>& d, real _p):D(d),p(_p){}

    E argmin(const std::function<IK(E)>& f, E s,int L)
    {
        this->p = 0.1;
        E x = s- this->p*this->D.gradient(f, s);
        for (; B.norm(this->D.gradient(f, x)) > this->eps && L; x -= this->p * this->D.gradient(f, x))
        {
            update_rate(f, x,s);
            s = x;
            L--;
        }
        return x;
    }

    E argmin(const std::function<std::pair<IK, E>(E)>& f, E s, int L)
    {
        auto P = f(s);
        E x = s - this->p * f(s).second;
        auto Q = f(x);
        while (B.norm(P.second) > eps && L--)
        {
            update_rate(x, s,Q.second,P.second);
            s = x;
            x -= this->p * Q.second;
            P = std::move(Q);
            Q = f(x);
        }
        return x;
    }


    virtual void update_rate(const std::function<IK(E)>& f, const E& x,const E& s)
    {
        auto L = this->D.gradient(f, x) - this->D.gradient(f, s);
        this->p = B.inner_product(L,x - s) / B.inner_product(L,L);
    }

    virtual void update_rate(const E& x, const E& s,const E& dx,const E& ds)
    {
        auto L = dx - ds;
        this->p = B.inner_product(L, x - s) / B.inner_product(L, L);
    }
};
#endif
