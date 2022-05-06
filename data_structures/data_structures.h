//
// Created by ASUS on 01/12/2021.
//
#ifndef __DATA_STRUCTURES_H__
#define __DATA_STRUCTURES_H__
#include <vector>
#include "statistic_tree.h"

inline unsigned int bit_log(unsigned int n)
{
    unsigned char a=0,b=30,r=0;
    while(a<=b)
    {
        auto c=(a+b)/2;
        if(n>>c)
            a=c+1;
        else
        {
            b=c-1;
            r=c-1;
        }
    }
    if((1<<(r-1))==n)
        return r-1;
    return r;
}

inline unsigned int bit_floor(unsigned int n)
{
    return 1<<bit_log(n);
}

inline unsigned int bit_ceil(unsigned int n)
{
    return 1<<(bit_log(n)+1);
}


template<typename R,typename O>
struct segment_tree
{
    std::vector<std::vector<R>> S;
    std::vector<R> A;
    int n,h;
    segment_tree(const std::vector<R> &_A):A(_A)
    {
        n=bit_ceil(A.size());
        A.resize(n,O::neutral);
        int m=n;
        h=0;
        while(m)
        {
            m/=2;
            h++;
        }
        S.resize(h);
        for(int i=0;i<h;i++)
            S[i].resize(1<<i);
        build();
    }

    void update(int i,R u)
    {
        A[i]=u;
        S[h-1][i]=u;
        int m=h-2;
        i/=2;
        while(m>=0)
        {
            S[m][i]=F(S[m+1][2*i],S[m+1][2*i+1]);
            m--;
            i/=2;
        }
    }

    R query(int l,int r)
    {
        return query(std::max(l,0),std::min(r,n),0,n,0);
    }
private:
    inline static constexpr O F=O();
    void build()
    {
        for(int i=0;i<n;i++)
            S.back()[i]=A[i];
        for(int i=h-2;i>=0;i--) for(int k=0;k<(1<<i);k++)
                S[i][k]=F(S[i+1][2*k],S[i+1][2*k+1]);
    }
    R query(int l,int r,int a,int b,int depth)
    {
        if(l>=r)
            return O::neutral;
        if(l==a && r==b)
            return S[depth][l>>(h-1-depth)];
        int mid=(a+b)/2;
        if(mid>r)
            return query(l,r,a,mid,depth+1);
        else if(mid<l)
            return query(l,r,mid,b,depth+1);
        else
            return F(query(l,mid,a,mid,depth+1),query(mid,r,mid,b,depth+1));
    }
};

template<typename T,typename O>
class sparse_array
{
    inline static constexpr O F=O();
    int n,h;
    std::vector<std::vector<T>> S;
public:
    sparse_array(const std::vector<T>&A):n(bit_ceil(A.size())),h(bit_log(n)),S(h+1)
    {
        int r=1;
        for(int i=h;i>=0;i--,r*=2)
            S[i].resize(n-r+1);
        for(int i=0;i<n;i++)
            S[h][i]=A[i];
        r=1;
        for(int i=h-1;i>=0;i--,r*=2) for(int j=0;j<=n-2*r;j++)
                S[i][j]=F(S[i+1][j],S[i+1][j+r]);
    }

    T query(int l,int r) const
    {
        if(l>=r)
            return O::neutral;
        auto d=r-l;
        auto s=bit_floor(d);
        auto b=bit_log(s);
        return F(S[h-b][l],S[h-b][r-s]);
    }
};

template<typename R,typename O>
struct segment_matrix
{
    std::vector<std::vector<segment_tree<R,O>>> S;
    std::vector<segment_tree<R,O>> segment_forest;
    std::vector<std::vector<R>> A;
    int n,h;
    segment_matrix(std::vector<std::vector<R>> &&_A):A(std::move(_A)),h(0)
    {
        n=bit_ceil(A.size());
        A.resize(n,std::vector<R>(bit_ceil(A[0].size()),O::neutral));
        int w=n;
        while(w)
        {
            w/=2;
            h++;
        }
        S.resize(h);
        int m=A[0].size();
        for(int i=0;i<m;i++)
        {
            std::vector<R> C;
            for(int j=0;j<n;j++)
                C.push_back(A[j][i]);
            segment_forest.emplace_back(C);
        }
        std::vector<R> C(m);
        for(int i=h-1;i>=0;i--) for(int j=0;j<(1<<i);j++)
            {
                for(int p=0;p<m;p++)
                    C[p]=segment_forest[p].S[i][j];
                S[i].emplace_back(C);
            }
    }

    void update(int i,int j,R u)
    {
        A[i][j]=u;
        segment_forest[j].update(i,u);
        int r=h-1;
        while(r>=0)
        {
            S[r][i].update(j,segment_forest[j].S[r][i]);
            r--;
            i/=2;
        }
    }

    R query(int l,int r,int p,int q)
    {
        return query(l,r,p,q,0,n,0);
    }
private:
    inline static constexpr O F=O();

    R query(int l,int r,int p,int q,int a,int b,int depth)
    {
        if(l>=r)
            return O::neutral;
        if(l==a && r==b)
            return S[depth][l>>(h-1-depth)].query(p,q);
        int mid=(a+b)/2;
        if(mid>r)
            return query(l,r,p,q,a,mid,depth+1);
        else if(mid<l)
            return query(l,r,p,q,mid,b,depth+1);
        else
            return F(query(l,mid,p,q,a,mid,depth+1),query(mid,r,p,q,mid,b,depth+1));
    }

};

template<typename T,typename O>
struct fenwick_tree {
    int n;
    std::vector<T> bit;
    inline static constexpr O F = O();

    fenwick_tree(int _n):n(_n),bit(n,O::neutral){}
    T sum(int x) {
        if(x<0)
            return O::neutral;
        T ret = O::neutral;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
            ret = F(ret,bit[i]);
        return ret;
    }

    T query(int a,int b)
    {
        return F(F.inv(sum(a-1)),sum(b));
    }

    T sum(int a,int b)
    {
        return query(a,b);
    }

    void add(int x, T delta) {
        for (int i = x; i < n; i = i | (i + 1))
            bit[i] = F(bit[i], delta);
    }

    void update(int x, T delta) {
        add(x,F(F.inv(sum(x,x)),delta));
    }
};


template<typename T,typename O>
struct fenwick_matrix {
    inline static constexpr O F=O();
    int n, m;
    std::vector<std::vector<T>> bit;

    fenwick_matrix(int _n,int _m):n(_n),m(_m),bit(n,std::vector<T>(m,O::neutral)){}
    int sum(int x, int y) {
        if(x<0||y<0)
            return O::neutral;
        int ret = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
            for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
                ret = F(ret,bit[i][j]);
        return ret;
    }

    int sum(int a,int b,int c,int d)
    {
        //To Do
        //........................................
    }


    int query(int a,int b,int c,int d)
    {
        return F(F.inv(sum(a,c),sum(b,d)));
    }

    void add(int x, int y, int delta) {
        for (int i = x; i < n; i = i | (i + 1))
            for (int j = y; j < m; j = j | (j + 1))
                bit[i][j] = F(bit[i][j],delta);
    }

    void update(int x, int y, int delta) {
        add(x,y,F(F.inv(sum(x,x,y,y)),delta));
    }
};


template<typename T,typename O>
class sparse_segment_tree
{
    sum_node<int, T, O>* tree;
public:
    sparse_segment_tree():tree(nullptr) {}
    ~sparse_segment_tree()
    {
        destroy(tree);
        tree = nullptr;
    }

    void insert(int k, const T& v)
    {
        tree = ::insert(tree, k, v);
    }

    void update(int k, const T& v)
    {
        tree = insert_or_assign(k, v);
    }

    void erase(int k)
    {
        tree = ::erase(tree, k);
    }

    T query(int l, int r) const
    {
        return sum(tree, l, r);
    }

    T index_query(int l, int r) const
    {
        return index_sum(tree,l, r);
    }
};

template<typename T, typename O>
class dynamic_segment_tree
{
    sum_node<int, T, O>* tree;
    int size;
public:
    dynamic_segment_tree() :tree(nullptr),size(0) {}
    ~dynamic_segment_tree()
    {
        destroy(tree);
        tree = nullptr;
        size = 0;
    }

    void push_back(const T& v)
    {
        tree = insert(tree, size++, v);
    }

    void update(int k, const T& v)
    {
        tree = insert_or_assign(k, v);
    }

    void pop_back()
    {
        tree = erase(tree, size--);
    }

    T query(int l, int r) const
    {
        return sum(tree, l, r);
    }

    T index_query(int l, int r) const
    {
        return query(l, r);
    }
};

template<typename T, typename O>
class ordered_segment_tree
{
    key_sum_node<T,O>* tree;
public:
    ordered_segment_tree() :tree(nullptr) {}
    ~ordered_segment_tree()
    {
        destroy(tree);
        tree = nullptr;
    }

    void insert(const T& v)
    {
        tree = ::insert(tree, v);
    }

    void erase(const T&v)
    {
        tree = ::erase(tree, v);
    }

    T query(const T& l, const T& r) const
    {
        return key_sum(tree, l, r);
    }

    T index_query(int a, int b) const
    {
        return index_key_sum(tree, a, b);
    }
};


#endif