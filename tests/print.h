//
// Created by ramizouari on 11/04/2022.
//

#ifndef CPLIBRARY_PRINT_H
#define CPLIBRARY_PRINT_H
#include <ostream>
#include "linear_algebra/linear_algebra.h"
#include "nt/modular_arithmetic.h"
template<algebra::integer n>
inline std::ostream & operator<<(std::ostream & os,const nt::cyclic<n>& v)
{
    return os << static_cast<algebra::integer>(v);
}

template<typename T,int n>
inline std::ostream & operator<<(std::ostream & os,const linalg::s_vector<T,n> & v)
{
    os << '[';
    for(auto &s:v)
        os<<s<<",";
    os  << "]";
    return os;
}

template<typename T,int n,int m>
inline std::ostream & operator<<(std::ostream & os,const linalg::s_matrix<T,n,m> & v)
{
    os << '[';
    for(auto &R:v) {
        os << '[';
        for (auto &s:R)
            os << s << ",";
        os << "],";
    }
    os  << "]";
    return os;
}


template<typename T>
inline std::ostream& operator<<(std::ostream& os, const poly::polynomial<T>& a)
{
    os << "[";
    for(auto& x:a)
        os << x << ",";
    os << "]";
    return os;
}

template<typename A,typename B>
inline std::ostream& operator<<(std::ostream& os,const std::pair<A,B>& p)
{
    return os<<"("<<p.first<<","<<p.second<<")";
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const std::vector<T>& a)
{
    os << "[";
    for(auto& x:a)
        os << x << ",";
    os << "]";
    return os;
}




#endif //CPLIBRARY_PRINT_H
