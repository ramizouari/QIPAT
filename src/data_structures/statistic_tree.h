//
// Created by ramizouari on 17/11/2021.
//

#ifndef __STATISTIC_NODE__
#define __STATISTIC_NODE__
#include <tuple>
#include "algebra/binary_operation.h"
#include <variant>
namespace data_structures {

/**
* @definition Order Statistic Tree: It is an AVL-tree augmented with a statistic.
* The statistic is a function of:
 * </ol>
* <li> The key
* <li> The value
* <li> left and right subtree
 * </ol>
* @Requirements
* <ol><li> a class A
* <li> (A,<=) is a totally ordered set
* <li> S is a statistic type
* </ol>
* @tparam T the type of the key
* @tparam V the type of the value
* @tparam S the statistic type: a statistic S is a class having some attributes serving as additional informations
* Those informations can be aggregated via the static update method
* @Requirements
* <ol>
* <li> class S
* <li> S has a public static method called update which accepts Tree<A,V,S>.
* <li> the update method "updates" adequately the statistics, and only the statistics
 * </ol>
*/
    template<typename T, typename V, typename S>
    struct statistic_node;

    template<typename T, typename V, typename S>
    struct statistic_node {
        T v;
        V data;
        int h;
        S statistic;
        statistic_node *left, *right, *parent;

        statistic_node(T _v, V _data, statistic_node *_parent = nullptr) : v(_v), data(_data), left(nullptr),
                                                                           right(nullptr), parent(_parent), h(1),
                                                                           statistic(v, data) {}

        void update() {
            h = std::max(left ? left->h : 0, right ? right->h : 0) + 1;
            S::update(this);
        }
    };


/*
* Get the height of the (sub)-tree
*/
    template<typename T, typename V, typename S>
    int height(statistic_node<T, V, S> *node) {
        return node ? node->h : 0;
    }


/*
* Get the balance of the current node
*/
    template<typename T, typename V, typename S>
    int balance(statistic_node<T, V, S> *tree) {
        return height(tree->left) - height(tree->right);
    }

/**
* Find node that has the given key, return nullptr otherwise
* @Notes
* 1. If the value is altered, and the statistic depends on that value. The calculated statistic will not be updated.
*   In that case, better use the insert_or_assign function or the update function
* 2. If the key is altered, It will probably cause the tree to be in an inconsistent state unless the tree does not have a key
* on the interval whose limit points are the old key value, and the new one.
*/
    template<typename T, typename V, typename S>
    statistic_node<T, V, S> *find(statistic_node<T, V, S> *node, const typename std::common_type<T>::type &v) {
        if (!node)
            return nullptr;
        if (node->v == v)
            return node;
        else if (node->v < v)
            return find(node->right, v);
        else return find(node->left, v);
    }

/*
* Find the data mapped by the given key
* @Requirements
* The Order Statistic Tree must contain at least one such key
* @Exception
* std::logic_error thrown if no such key is found
* @Notes
* If the value is altered, and the statistic depends on that value. The calculated statistic will not be updated.
* In that case, better use the insert_or_assign function or the update function
*/
    template<typename T, typename V, typename S>
    V &value_at(statistic_node<T, V, S> *node, const typename std::common_type<T>::type &v) {
        [[unlikely]]
        if (!node)
            throw std::out_of_range("key does not exist");
        if (node->v == v)
            return node;
        else if (node->v < v)
            return value_at(node->right, v);
        else return value_at(node->left, v);
    }

/*
* Get the node whose key is strictly bigger than v
*/
    template<typename T, typename V, typename S>
    statistic_node<T, V, S> *upper_bound(statistic_node<T, V, S> *tree, const
    typename std::common_type<T>::type &v) {
        if (tree == nullptr)
            return nullptr;
        if (tree->v <= v)
            return upper_bound(tree->right, v);
        else {
            auto w = upper_bound(tree->left, v);
            if (w == nullptr)
                return tree;
            return w;
        }
    }

/*
* Get the node whose key is strictly smaller than v
*/
    template<typename T, typename V, typename S>
    statistic_node<T, V, S> *reverse_upper_bound(statistic_node<T, V, S> *tree,
                                                 const typename std::common_type<T>::type &v) {
        if (tree == nullptr)
            return nullptr;
        if (tree->v >= v)
            return reverse_upper_bound(tree->left, v);
        else {
            auto w = reverse_upper_bound(tree->right, v);
            if (w == nullptr)
                return tree;
            return w;
        }
    }

/*
* Get the node whose key is not smaller than v
*/
    template<typename T, typename V, typename S>
    statistic_node<T, V, S> *lower_bound(statistic_node<T, V, S> *tree,
                                         const typename std::common_type<T>::type &v) {
        if (tree == nullptr)
            return nullptr;
        if (tree->v < v)
            return lower_bound(tree->right, v);
        else {
            auto w = lower_bound(tree->left, v);
            if (w == nullptr)
                return tree;
            return w;
        }
    }

    template<typename T, typename V, typename S>
    statistic_node<T, V, S> *reverse_lower_bound(statistic_node<T, V, S> *tree,
                                                 const typename std::common_type<T>::type &v) {
        if (tree == nullptr)
            return nullptr;
        if (tree->v > v)
            return reverse_lower_bound(tree->left, v);
        else {
            auto w = reverse_lower_bound(tree->right, v);
            if (w == nullptr)
                return tree;
            return w;
        }
    }

/*
* Get the node with the smallest key
*/
    template<typename T, typename V, typename S>
    statistic_node<T, V, S> *begin(statistic_node<T, V, S> *tree) {
        if (!tree)
            return nullptr;
        while (tree->left)
            tree = tree->left;
        return tree;
    }

/*
* Get the successor of the current node
*/
    template<typename T, typename V, typename S>
    statistic_node<T, V, S> *next(statistic_node<T, V, S> *tree) {
        if (tree == nullptr)
            return nullptr;
        if (tree->right) {
            tree = tree->right;
            while (tree->left)
                tree = tree->left;
            return tree;
        } else {
            auto tmp = tree;
            tree = tree->parent;
            while (tree && tree->v < tmp->v)
                tree = tree->parent;
            if (!tree)
                return nullptr;
            return tree;
        }
    }

/*
* Get the previous of the current node
*/
    template<typename T, typename V, typename S>
    statistic_node<T, V, S> *prev(statistic_node<T, V, S> *tree) {
        if (tree == nullptr)
            return nullptr;
        if (tree->left) {
            tree = tree->left;
            while (tree->right)
                tree = tree->right;
            return tree;
        } else {
            auto tmp = tree;
            tree = tree->parent;
            while (tree && tree->v > tmp->v)
                tree = tree->parent;
            if (!tree)
                return nullptr;
            return tree;
        }
    }

/*
* Applies a right rotation to the ordered statistic tree on the current node.
*/
    template<typename T, typename V, typename S>
    statistic_node<T, V, S> *rebalance_right(statistic_node<T, V, S> *x) {
        auto y = x->left, B = y->right;
        y->right = x;
        y->parent = x->parent;
        if (x->parent) {
            if (x->parent->left == x)
                x->parent->left = y;
            else x->parent->right = y;
        }
        x->parent = y;
        x->left = B;
        if (B) B->parent = x;
        x->update();
        return y;
    }

/*
* Applies a left rotation to the ordered statistic tree on the current node.
*/
    template<typename T, typename V, typename S>
    statistic_node<T, V, S> *rebalance_left(statistic_node<T, V, S> *x) {
        auto y = x->right, B = y->left;
        y->left = x;
        y->parent = x->parent;
        if (x->parent) {
            if (x->parent->left == x)
                x->parent->left = y;
            else x->parent->right = y;
        }
        x->parent = y;
        x->right = B;
        if (B) B->parent = x;
        x->update();
        return y;
    }

/*
* Rebalance the ordered statistic tree. 
*/
    template<typename T, typename V, typename S>
    statistic_node<T, V, S> *rebalance(statistic_node<T, V, S> *x) {
        if (!x)
            return nullptr;
        if (balance(x) < -1) {
            if (balance(x->right) == 1)
                rebalance_right(x->right);
            x = rebalance_left(x);
        } else if (balance(x) > 1) {
            if (balance(x->left) == -1)
                rebalance_left(x->left);
            x = rebalance_right(x);
        }
        x->update();
        if (!x->parent)
            return x;
        return rebalance(x->parent);
    }

/*
* Insert (v,data) into the ordered statistic tree
* @Cases
* 1. If or_assign is false, (v,data) is inserted while allowing duplicates
* 2. if or_assign is true, (v,data) is inserted if the tree does not have a key v. Otherwise the value mapped by v is changed to data.
*/
    template<typename T, typename V, typename S>
    statistic_node<T, V, S> *insert(statistic_node<T, V, S> *tree, const typename std::common_type<T>::type &v,
                                    const typename std::common_type<V>::type &data, bool or_assign = false) {
        if (!tree) {
            tree = new statistic_node<T, V, S>(v, data);
            return tree;
        }
        auto p = lower_bound(tree, v);
        if (p == nullptr) {
            p = tree;
            while (p->right) p = p->right;
        } else if (or_assign && p->v == v) {
            p->data = data;
            p->update();
            return rebalance(p);
        } else if (p->left) {
            p = p->left;
            while (p->right)
                p = p->right;
        }
        auto u = new statistic_node<T, V, S>(v, data, p);
        if (v <= p->v)
            p->left = u;
        else p->right = u;
        p->update();
        return rebalance(p);
    }

    template<typename T, typename S>
    statistic_node<T, std::monostate, S> *insert(statistic_node<T, std::monostate, S> *tree,
                                                 const typename std::common_type<T>::type &v, bool or_assign = false) {
        return insert(tree, v, {}, or_assign);
    }


/*
* Insert (v,data) into the ordered statistic tree if it does not have a key v
* Otherwise, change the value mapped by v to data.
*/
    template<typename T, typename V, typename S>
    statistic_node<T, V, S> *insert_or_assign(statistic_node<T, V, S> *tree, const
    typename std::common_type<T>::type &v, const typename std::common_type<V>::type &data) {
        return insert(tree, v, data, true);
    }

/*
* Insert (v,data) into the ordered statistic tree if it does not have a key v
* Otherwise, Do nothing
*/
    template<typename T, typename S>
    statistic_node<T, std::monostate, S> *insert_or_assign(statistic_node<T, std::monostate, S> *tree, const
    typename std::common_type<T>::type &v) {
        return insert_or_assign(tree, v, {});
    }

/*
* Extract a node from an ordered statistic tree given its key
* The node is not deleted
* @Requirements
* The tree does have a node with the given key
*/
    template<typename T, typename V, typename S>
    std::pair<statistic_node<T, V, S> *, statistic_node<T, V, S> *> extract(statistic_node<T, V, S> *tree, const
    typename std::common_type<T>::type &v) {
        auto p = lower_bound(tree, v);
        if (!p)
            return {nullptr, tree};
        if (!p->left) {
            auto w = p->parent ? p->parent : p->right;
            if (p->parent) {
                if (p->parent->left == p) p->parent->left = p->right;
                else p->parent->right = p->right;
            }
            if (p->right) p->right->parent = p->parent;
            p->right = nullptr;
            p->parent = nullptr;
            return {p, rebalance(w)};
        } else if (!p->left->right) {
            auto w = p->left;
            if (p->parent) {
                if (p->parent->left == p) p->parent->left = p->left;
                else p->parent->right = p->left;
            }
            if (p->right) p->right->parent = w;
            w->right = p->right;
            w->parent = p->parent;
            p->right = nullptr;
            p->left = nullptr;
            p->parent = nullptr;
            return {p, rebalance(w)};
        } else {
            auto u = p->left;//Position of replacement
            while (u->right)
                u = u->right;
            auto s = u->parent;//Position of path to be updated
            s->right = u->left;
            if (u->left) u->left->parent = s;
            std::swap(u->v, p->v);
            std::swap(u->data, p->data);
            u->left = nullptr;
            u->right = nullptr;
            u->parent = nullptr;
            return {u, rebalance(s)};
        }

    }


    template<typename T, typename V, typename S>
    statistic_node<T, V, S> *erase(statistic_node<T, V, S> *tree,
                                   const typename std::common_type<T>::type &v) {
        auto P = extract(tree, v);
        delete P.first;
        return P.second;
    }

    template<typename T, typename V, typename S>
    statistic_node<T, V, S> *update(statistic_node<T, V, S> *tree,
                                    const typename std::common_type<T>::type &v,
                                    const typename std::common_type<V>::type &data) {
        auto p = lower_bound(tree, v);
        p->data = data;
        return rebalance(p);
    }

    template<typename T, typename V, typename S>
    void destroy(statistic_node<T, V, S> *node) {
        if (!node)
            return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

/*
* Merge a node with two trees
* @Requirements
* 1. all keys of left are less or equal to the key of the root node
* 2. all keys of right are greater or equal to the key of the root node
* 3. the left & right trees do not have a parent
*/
    template<typename T, typename V, typename S>
    statistic_node<T, V, S> *merge_with_root(statistic_node<T, V, S> *root,
                                             statistic_node<T, V, S> *left, statistic_node<T, V, S> *right) {
        if (left == nullptr)
            return insert(right, root->v, root->data);
        else if (right == nullptr)
            return insert(left, root->v, root->data);
        auto potential = height(left) - height(right);
        if (potential <= 0) {
            while (potential < -1)
                potential = height(left) - height(right = right->left);
            if (right && right->parent)
                right->parent->left = root;
            if (right)
                root->parent = right->parent;
        } else {
            while (potential > 1)
                potential = height(left = left->right) - height(right);
            if (left && left->parent)
                left->parent->right = root;
            if (left)
                root->parent = left->parent;
        }
        root->left = left;
        root->right = right;
        root->update();
        if (left)
            left->parent = root;
        if (right)
            right->parent = root;
        return rebalance(root);
    }

/*
* Merge two trees
* @Requirements
* The biggest key of left is smaller than the smallest key of right
*/
    template<typename T, typename V, typename S>
    statistic_node<T, V, S> *merge(statistic_node<T, V, S> *left, statistic_node<T, V, S> *right) {
        if (!left)
            return right;
        statistic_node<T, V, S> *last = left;
        while (last->right)
            last = last->right;
        auto [root, L] = extract(last, last->v);
        return merge_with_root(root, L, right);
    }

/*
* Split a tree into two trees with respect to threshold
* - The left part is the resultant tree whose keys are smaller than threshold
* - The right part is the resultant tree whose keys are not smaller than threshold
*/
    template<typename T, typename V, typename S>
    std::pair<statistic_node<T, V, S> *, statistic_node<T, V, S> *>
    split(statistic_node<T, V, S> *node, T threshold) {
        statistic_node<T, V, S> *left = nullptr, *right = nullptr;
        if (!node)
            return std::make_pair(left, right);
        if (node->right)
            node->right->parent = nullptr;
        if (node->left)
            node->left->parent = nullptr;
        if (node->v < threshold) {
            auto [L, R] = split(node->right, threshold);
            if (L)
                L->parent = nullptr;
            if (R)
                R->parent = nullptr;
            left = merge_with_root(node, node->left, L);
            right = R;
        } else {
            auto [L, R] = split(node->left, threshold);
            if (L)
                L->parent = nullptr;
            if (R)
                R->parent = nullptr;
            right = merge_with_root(node, R, node->right);
            left = L;
        }
        return std::make_pair(left, right);
    }

/*
* Order Statistic:
* It is a Self Balanced Binary Search Tree augmented with an order:
* - The order of an element can be calculated in O(log(n))
* - An element can be selected given its order in O(log(n))
*/

    struct order_stats {
        int size;

        order_stats() {}

        template<typename T, typename V>
        order_stats(T v, V data):size(1) {}

        template<typename T, typename V>
        static void update(statistic_node<T, V, order_stats> *node);
    };

    template<typename T, typename V>
    void order_stats::update(statistic_node<T, V, order_stats> *node) {
        node->statistic.size =
                (node->left ? node->left->statistic.size : 0) + 1 + (node->right ? node->right->statistic.size : 0);
    }

    template<typename T, typename V, typename OrderStats>
    int size(statistic_node<T, V, OrderStats> *node) {
        return node ? node->statistic.size : 0;
    }

    template<typename T, typename V, typename OrderStats>
    T order_inf(statistic_node<T, V, OrderStats> *tree, const typename std::common_type<T>::type &v) {
        if (!tree)
            return -1;
        if (v < tree->v)
            return order_inf(tree->left, v);
        else if (tree->v == v) {
            auto o = order_inf(tree->left, v);
            if (o != -1)
                return o;
            else return size(tree->left);
        } else {
            auto o = order_inf(tree->right, v);
            if (o != -1)
                return size(tree->left) + 1 + o;
            else return -1;
        }
    }

    template<typename T, typename V, typename OrderStats>
    T order_sup(statistic_node<T, V, OrderStats> *tree, const typename std::common_type<T>::type &v) {
        if (!tree)
            return 0;
        if (v < tree->v)
            return order_sup(tree->left, v);
        else if (tree->v == v) {
            if (tree->right && tree->right->v == v)
                return size(tree->left) + 1 + order_sup(tree->right, v);
            else return size(tree->left);
        } else return size(tree->left) + 1 + order_sup(tree->right, v);
    }

    template<typename T, typename V, typename OrderStats>
    int order(statistic_node<T, V, OrderStats> *tree, const typename std::common_type<T>::type &v) {
        if (!tree)
            return 0;
        if (v < tree->v)
            return order(tree->left, v);
        else if (tree->v == v) {
            if (tree->right && tree->right->v == v)
                return size(tree->left) + 1 + order(tree->right, v);
            else return size(tree->left);
        } else return size(tree->left) + 1 + order(tree->right, v);
    }

    template<typename T, typename V, typename OrderStats>
    statistic_node<T, V, OrderStats> *select(statistic_node<T, V, OrderStats> *tree, int o) {
        int s = size(tree->left);
        if (s == o)
            return tree;
        else if (s < o)
            return select(tree->right, o - s - 1);
        else return select(tree->left, o);
    }

    template<typename T, typename V, typename OrderStats>
    statistic_node<T, V, OrderStats> *median(statistic_node<T, V, OrderStats> *tree) {
        return select(tree, size(tree) / 2);
    }

/**
* Sum Statistic:
* It is an Ordered Statistic Tree augmented with a sum acting on data:
* The sum is defined over an associative binary operation having a neutral element
* It supports range sum (L,R) for keys belonging to an interval [L,R[ 
* @Requirements
* 1. a class V
* 2. an associative binary operation O: VxV->V 
* 3. O has a neutral element named 'neutral'. and it is defined as a public static attribute.
* 4. O has an overload for the ternary case: VxVxV->V, and its definition is compatible with the binary case.
* @Notes
* Formally, (V,O) is a monoid
*/
    template<typename V, typename O>
    struct sum_stats {
        inline static constexpr O F = O();
        int size;
        V sum;

        sum_stats() {}

        template<typename T>
        sum_stats(T v, V data) :size(1), sum(data) {}

        template<typename T>
        static void update(statistic_node<T, V, sum_stats> *node);

        inline static const V &neutral = O::neutral;
    };

    template<typename V, typename O>
    template<typename T>
    void sum_stats<V, O>::update(statistic_node<T, V, sum_stats<V, O>> *node) {
        node->statistic.size =
                (node->left ? node->left->statistic.size : 0) + 1 + (node->right ? node->right->statistic.size : 0);
        node->statistic.sum = F(tree_sum(node->left), node->data, tree_sum(node->right));
    }

    template<typename T, typename V, typename SumStats>
    V tree_sum(statistic_node<T, V, SumStats> *node) {
        return node ? node->statistic.sum : SumStats::neutral;
    }

    template<typename T, typename V, typename SumStats>
    V prefix_sum(statistic_node<T, V, SumStats> *tree, const
    typename std::common_type<T>::type &U) {
        if (!tree)
            return SumStats::neutral;
        else if (tree->v >= U)
            return prefix_sum(tree->left, U);
        else return SumStats::F(tree_sum(tree->left), tree->data, prefix_sum(tree->right, U));
    }

    template<typename T, typename V, typename SumStats>
    V suffix_sum(statistic_node<T, V, SumStats> *tree, const
    typename std::common_type<T>::type &L) {
        if (!tree)
            return SumStats::neutral;
        else if (tree->v < L)
            return suffix_sum(tree->right, L);
        else return SumStats::F(suffix_sum(tree->left, L), tree->data, tree_sum(tree->right));
    }

    template<typename T, typename V, typename SumStats>
    V sum(statistic_node<T, V, SumStats> *tree, const
    typename std::common_type<T>::type &L, const typename std::common_type<T>::type &R) {
        if (!tree)
            return SumStats::neutral;
        if (tree->v < L)
            return sum(tree->right, L, R);
        else if (tree->v >= R)
            return sum(tree->left, L, R);
        else return SumStats::F(suffix_sum(tree->left, L), tree->data, prefix_sum(tree->right, R));
    }

    template<typename T, typename V, typename SumStats>
    V prefix_index_sum(statistic_node<T, V, SumStats> *tree, int n) {
        if (!tree || n <= 0)
            return SumStats::neutral;
        else if (size(tree->left) >= n)
            return prefix_index_sum(tree->left, n);
        else
            return SumStats::F(tree_sum(tree->left), tree->data,
                               prefix_index_sum(tree->right, n - 1 - size(tree->left)));
    }

    template<typename T, typename V, typename SumStats>
    V suffix_index_sum(statistic_node<T, V, SumStats> *tree, int n) {
        if (!tree)
            return SumStats::neutral;
        else if (size(tree->right) >= n)
            return suffix_index_sum(tree->right, n);
        else
            return SumStats::F(suffix_index_sum(tree->left, n - 1 - size(tree->right)), tree->data,
                               tree_sum(tree->right));
    }

    template<typename T, typename V, typename SumStats>
    V index_sum(statistic_node<T, V, SumStats> *tree, int a, int b) {
        if (!tree || a >= b)
            return SumStats::neutral;
        int left_size = size(tree->left);
        if (left_size < a)
            return SumStats::F(tree->data, index_sum(tree->right, a - left_size - 1, b - left_size - 1));
        else if (left_size >= b)
            return index_sum(tree->left, a, b);
        else
            return SumStats::F(suffix_index_sum(tree->left, left_size), tree->data,
                               prefix_index_sum(tree->right, left_size - 1));
    }

/** Key Sum Statistic:
* It is an Ordered Statistic Tree augmented with a sum acting on keys:
* The sum is defined over an associative binary operation having a neutral element
* It supports range sum (L,R) for keys belonging to the interval [L,R[ 
* @Requirements
* 1. a class A
* 2. an associative binary operation O: TxT->A
* 3. O has a neutral element named 'neutral'. and it is defined as a public static attribute.
* 4. O has an overload for the ternary case: TxTxT->A, and its definition is compatible with the binary case.
* @Notes
* Formally, (A,O) is a monoid
* The order of A does not need to be compatible with O
*/

    template<typename T, typename O>
    struct key_sum_stats {
        inline static constexpr O F = O();
        int size;
        T key_sum;

        key_sum_stats() {}

        template<typename V>
        key_sum_stats(T v, V data) :size(1), key_sum(v) {}

        template<typename V>
        static void update(statistic_node<T, V, key_sum_stats> *node);

        inline static const T &key_neutral = O::neutral;
    };

    template<typename T, typename O>
    template<typename V>
    void key_sum_stats<T, O>::update(statistic_node<T, V, key_sum_stats<T, O>> *node) {
        node->statistic.size =
                (node->left ? node->left->statistic.size : 0) + 1 + (node->right ? node->right->statistic.size : 0);
        node->statistic.key_sum = F(tree_key_sum(node->left), node->v, tree_key_sum(node->right));
    }


    template<typename T, typename V, typename KeySumStats>
    T tree_key_sum(statistic_node<T, V, KeySumStats> *node) {
        return node ? node->statistic.key_sum : KeySumStats::key_neutral;
    }

    template<typename T, typename V, typename KeySumStats>
    T prefix_key_sum(statistic_node<T, V, KeySumStats> *tree, const
    typename std::common_type<T>::type &U) {
        if (!tree)
            return KeySumStats::key_neutral;
        else if (tree->v >= U)
            return prefix_key_sum(tree->left, U);
        else return KeySumStats::F(tree_key_sum(tree->left), tree->v, prefix_key_sum(tree->right, U));
    }

    template<typename T, typename V, typename KeySumStats>
    T suffix_key_sum(statistic_node<T, V, KeySumStats> *tree, const
    typename std::common_type<T>::type &L) {
        if (!tree)
            return KeySumStats::key_neutral;
        else if (tree->v < L)
            return suffix_key_sum(tree->right, L);
        else return KeySumStats::F(suffix_key_sum(tree->left, L), tree->v, tree_key_sum(tree->right));
    }

    template<typename T, typename V, typename KeySumStats>
    T key_sum(statistic_node<T, V, KeySumStats> *tree, const typename std::common_type<T>::type &L,
              const typename std::common_type<T>::type &R) {
        if (!tree)
            return KeySumStats::key_neutral;
        if (tree->v < L)
            return key_sum(tree->right, L, R);
        else if (tree->v >= R)
            return key_sum(tree->left, L, R);
        else return KeySumStats::F(suffix_key_sum(tree->left, L), tree->v, prefix_key_sum(tree->right, R));
    }

    template<typename T, typename V, typename KeySumStats>
    T prefix_index_key_sum(statistic_node<T, V, KeySumStats> *tree, int n) {
        if (!tree || n <= 0)
            return KeySumStats::key_neutral;
        else if (size(tree->left) >= n)
            return prefix_index_key_sum(tree->left, n);
        else
            return KeySumStats::F(tree_key_sum(tree->left), tree->v,
                                  prefix_index_key_sum(tree->right, n - 1 - size(tree->left)));
    }

    template<typename T, typename V, typename KeySumStats>
    T suffix_index_key_sum(statistic_node<T, V, KeySumStats> *tree, int n) {
        if (!tree)
            return KeySumStats::key_neutral;
        else if (size(tree->right) >= n)
            return suffix_index_key_sum(tree->right, n);
        else
            return KeySumStats::F(suffix_index_key_sum(tree->left, n - 1 - size(tree->right)), tree->v,
                                  tree_key_sum(tree->right));
    }

    template<typename T, typename V, typename KeySumStats>
    T index_key_sum(statistic_node<T, V, KeySumStats> *tree, int a, int b) {
        if (!tree || a >= b)
            return KeySumStats::key_neutral;
        int left_size = size(tree->left);
        if (left_size < a)
            return KeySumStats::F(tree->v, index_key_sum(tree->right, a - left_size - 1, b - left_size - 1));
        else if (left_size >= b)
            return index_key_sum(tree->left, a, b);
        else
            return KeySumStats::F(suffix_index_key_sum(tree->left, left_size - a), tree->v,
                                  prefix_index_key_sum(tree->right, b - left_size - 1));
    }

/*
* The following aliases gives the possibility to a much shorter and compact code
* For example:
* 1. sum_node_t<int,double,multiplies_t> is a shorthand for this atrocity:
*   statistic_node<int,double,sum_stats<double,multiplies_t<double>>>
*   this is a statistic_node whose key is of type int and values are doubles, the considered statistic is 
*   an aggregation stats whose operation is multiplication
* The first two considers the case when the binary operator's class is a template
* The last two considers the case when the binary operator's class is not a template
*/

//
    template<typename T, typename V, template<typename S = T> typename O>
    using sum_node_t = statistic_node<T, V, sum_stats<V, O<V>>>;

    template<typename T, template<typename S = T> typename O, typename V=std::monostate>
    using key_sum_node_t = statistic_node<T, V, key_sum_stats<T, O<T>>>;

    template<typename T, typename V, typename O>
    using sum_node = statistic_node<T, V, sum_stats<V, O>>;

    template<typename T, typename O, typename V = std::monostate>
    using key_sum_node = statistic_node<T, V, key_sum_stats<T, O>>;

    template<typename T, typename V = std::monostate>
    using order_node = statistic_node<T, V, order_stats>;

/*
* A
*/
}
#endif