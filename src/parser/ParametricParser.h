//
// Created by ramizouari on 15/05/22.
//
#undef UNICODE
#undef _UNICODE
#ifndef IMAGEPROCESSING_PARAMETRICPARSER_H
#define IMAGEPROCESSING_PARAMETRICPARSER_H

#include <vector>
#include <muParser.h>
#include <span>
#include "algebra/abstract_algebra.h"
#include <variant>
#include <cmath>
#include <numeric>

namespace parser {

    template<typename T,int n>
    struct tensor_t
    {
        using tensor = std::vector<typename tensor_t<T,n-1>::tensor>;
    };

    template<typename T>
    struct tensor_t<T,0>
    {
        using tensor = T;
    };

    template<typename R, int n>
    using tensor=typename tensor_t<R ,n>::tensor;

    enum Precedence
    {
        NONE=0,
        OR,
        AND,
        LOGIC,
        COMPARISON,
        ADDITION,
        MULTIPLICATION,
        EXPONENTIATION,
        UNARY=MULTIPLICATION
    };

    enum Associativity
    {
        LEFT=0,
        RIGHT
    };


    using Real=double;

    namespace FunctionTypes
    {
        using UnaryFunctionPtr = Real(*)(Real);
        using BinaryFunctionPtr = Real(*)(Real,Real);
        using TernaryFunctionPtr = Real(*)(Real,Real,Real);
        using QuaternaryFunctionPtr = Real(*)(Real,Real,Real,Real);
        template<typename... R> requires (std::is_same<R...,Real>::value)
        using NaryFunctionPtr = Real(*)(R...);
        using VariadicFunctionPtr= Real(*)(const Real*,int);
    }

    template<int n,typename ResultType>
    class ParametricParser {
    public:
        template<typename ...T> requires (sizeof...(T)==n)
        explicit ParametricParser(const std::string &expression, T&& ...varNames);
        ~ParametricParser() = default;
        std::vector<ResultType>  parse(const std::vector<std::array<Real,n>> &values);
        tensor<ResultType,n> parseInterval(const std::vector<Real> &mins,const std::vector<Real> &maxs,const std::vector<int> &counts);
        template<typename Function>
        void addDependentVariable(const std::string &name, Function &&f);
        virtual void setParameter(int index,Real val,int pos,bool updateDependedVariables=true);
        virtual void updateDependentVariables();
        template<typename Function>
        void addFunction(const std::string &name,Function &&f);
        template<typename Function,typename UserData>
        void addFunction(const std::string &name, Function &&f,UserData *data);
        void addConstant(const std::string &name,Real val);
        template<typename Operator>
        void addOperator(const std::string &name,Operator &&op);
        template<typename Operator>
        void addOperator(const std::string &name,Operator &&op,unsigned precedence);
        template<typename Operator>
        void addOperator(const std::string &name,Operator &&op,unsigned precedence, bool rightAssociative);
    protected:
        std::array<std::string,n> variableNames;
        std::array<Real,n> variables;
        std::array<unsigned int,n> indexes;
        using ParametricArrayType=std::array<Real,n>;
        using IndexArrayType=std::array<unsigned int,n>;
        using FunctionType=std::variant<std::function<Real(const ParametricArrayType &)>,std::function<Real(const IndexArrayType &)>>;
        std::vector<std::pair<std::unique_ptr<Real>,FunctionType>> dependentVariables;
        mu::Parser parser;
    };

    template<int n,typename ResultType>
    template<typename ...T> requires (sizeof...(T)==n)
    ParametricParser<n,ResultType>::ParametricParser(const std::string &expression,T &&... varNames): variableNames{std::forward<T>(varNames)...}
    {
        parser.SetExpr(expression);
        std::fill(variables.begin(),variables.end(),0);
        std::fill(indexes.begin(),indexes.end(),0);
        for(int i=0;i<n;i++)
            parser.DefineVar(variableNames[i].c_str(), &variables[i]);
        addOperator("//", [](auto x,auto y)->parser::Real{return std::llround(x)/std::llround(y);},parser::Precedence::MULTIPLICATION,parser::Associativity::LEFT);
        addOperator("%", [](auto x,auto y)->parser::Real{return std::llround(x)%std::llround(y);},parser::Precedence::MULTIPLICATION,parser::Associativity::LEFT);
        addOperator("~=", [](auto x,auto y)->parser::Real{return std::abs(x-y)<1e-6;},parser::Precedence::COMPARISON,parser::Associativity::LEFT);
        addOperator("|<|", [](auto x,auto y)->parser::Real{return std::abs(x)<std::abs(y);}, parser::Precedence::COMPARISON,parser::Associativity::LEFT);
        addOperator("|>|", [](auto x,auto y)->parser::Real{return std::abs(x)>std::abs(y);}, parser::Precedence::COMPARISON,parser::Associativity::LEFT);
        addOperator("|<=|", [](auto x,auto y)->parser::Real{return std::abs(x)<=std::abs(y);}, parser::Precedence::COMPARISON,parser::Associativity::LEFT);
        addOperator("|>=|", [](auto x,auto y)->parser::Real{return std::abs(x)>=std::abs(y);}, parser::Precedence::COMPARISON,parser::Associativity::LEFT);
        addOperator("**",static_cast<FunctionTypes::BinaryFunctionPtr>(std::pow),parser::Precedence::EXPONENTIATION,parser::Associativity::RIGHT);
        addFunction("floor",static_cast<FunctionTypes::UnaryFunctionPtr>(std::floor));
        addFunction("ceil",static_cast<FunctionTypes::UnaryFunctionPtr>(std::ceil));
        addFunction("round",static_cast<FunctionTypes::UnaryFunctionPtr>(std::round));
        addFunction("gamma",static_cast<FunctionTypes::UnaryFunctionPtr>(std::lgamma));
        addFunction("erf",static_cast<FunctionTypes::UnaryFunctionPtr>(std::erf));
        addFunction("beta",static_cast<FunctionTypes::BinaryFunctionPtr>(std::beta));
        addFunction("zeta",static_cast<FunctionTypes::UnaryFunctionPtr>(std::riemann_zeta));
        addFunction("expint",static_cast<FunctionTypes::UnaryFunctionPtr>(std::expint));

        addFunction("N1",[](const Real* u,int m)->Real
        {
            std::span U(u,u+m);
            return std::accumulate(U.begin(),U.end(),0.0,[](auto x,auto y){return x+std::abs(y);});
        });
        addFunction("N2",[](const Real* u,int m)->Real
        {
            std::span U(u,u+m);
            return std::sqrt(std::inner_product(U.begin(),U.end(),U.begin(),0.));
        });
        addFunction("Ninf",[](const Real* u,int m)->Real
        {
            std::span U(u,u+m);
            return std::accumulate(U.begin(),U.end(),0.0,[](auto x,auto y){return std::max(x,std::abs(y));});
        });

        addFunction("Norm",[](const Real* u,int m)->Real
        {
            std::span U(u,u+m-1);
            if(std::isinf(u[m-1]))
                return std::accumulate(U.begin(),U.end(),0.0,[](auto x,auto y){return std::max(x,std::abs(y));});
            else if(u[m-1]==1)
                return std::accumulate(U.begin(),U.end(),0.0,[](auto x,auto y){return x+std::abs(y);});
            else if(u[m-1]==2)
                return std::sqrt(std::inner_product(U.begin(),U.end(),U.begin(),0.));
            else return std::pow(std::accumulate(U.begin(),U.end(),0.0,[s=u[m-1]](auto x,auto y){return x+std::pow(std::abs(y),s);}),1./u[m-1]);
        });
    }

    template<int n,int m, typename ResultType>
    tensor<ResultType, n> multiDimensionalParse(mu::Parser &parser,ParametricParser<m,ResultType> &P,
                                                std::span<const Real> mins, std::span<const Real> maxs,std::span<const int> counts)
    {
        tensor<ResultType,n> result;
        if constexpr (n==0)
        {
            P.updateDependentVariables();
            return parser.Eval();
        }
        else
        {
            std::span<const Real> subMin(mins.begin()+1,mins.end());
            std::span<const Real> subMax(maxs.begin()+1,maxs.end());
            std::span<const int> subCount(counts.begin()+1,counts.end());
            for(int i=0;i<counts[0];i++) {
                P.setParameter(m-n, mins[0] + i * (maxs[0] - mins[0]) / (counts[0] - 1),i,false);
                result.push_back(multiDimensionalParse<n - 1,m, ResultType>(parser,P, subMin, subMax, subCount));
            }
            return result;
        }
    }

    template<int n,typename ResultType>
    std::vector<ResultType> ParametricParser<n,ResultType>::parse(const std::vector<std::array<Real, n>> &values) {
        std::vector<ResultType> result;
        for (const auto &value : values) {
            for (int i = 0; i < n; i++)
                variables[i] = value[i];
            result.push_back(parser.Eval());
        }
        return result;
    }

    template<int n, typename ResultType>
    tensor<ResultType, n> ParametricParser<n, ResultType>::parseInterval(const std::vector<Real> &mins, const std::vector<Real> &maxs,const std::vector<int> &counts)
    {
        return multiDimensionalParse<n,n,ResultType>(parser,*this,
                                                   std::span(mins.begin(),mins.size()),std::span(maxs.begin(),maxs.size()),std::span(counts.begin(),counts.size()));
    }

    template<int n, typename ResultType>
    void ParametricParser<n, ResultType>::setParameter(int index, Real val,int pos,bool updateDependentVariables) {
        variables[index] = val;
        if(updateDependentVariables)
            this->updateDependentVariables();
    }

    template<int n, typename ResultType>
    template<typename Function>
    void ParametricParser<n, ResultType>::addDependentVariable(const std::string &name, Function &&f) {
        dependentVariables.emplace_back(std::make_unique<Real>(0),std::forward<Function>(f));
        parser.DefineVar(name.c_str(),dependentVariables.back().first.get());
    }

    template<int n, typename ResultType>
    template<typename Function>
    void ParametricParser<n, ResultType>::addFunction(const std::string &name, Function &&f) {
        parser.DefineFun(name,std::forward<Function>(f),false);
    }

    template<int n, typename ResultType>
    template<typename Function,typename UserData>
    void ParametricParser<n, ResultType>::addFunction(const std::string &name, Function &&f,UserData *data) {
        parser.DefineFunUserData(name,std::forward<Function>(f),const_cast<std::remove_const_t<UserData>*>(data),true);
    }

    template<int n, typename ResultType>
    void ParametricParser<n, ResultType>::updateDependentVariables()
    {
        for (auto &[v, f]: dependentVariables)
            if (f.index() == 0)
                *v = std::get<0>(f)(variables);
            else
                *v = std::get<1>(f)(indexes);
    }

    template<int n, typename ResultType>
    void ParametricParser<n, ResultType>::addConstant(const std::string &name, Real val) {
        parser.DefineConst(name, val);
    }

    template<int n,typename ResultType>
    template<typename Operator>
    void ParametricParser<n, ResultType>::addOperator(const std::string &name,Operator &&op)
    {
        parser.DefineOprt(name,std::forward<Operator>(op));
    }

    template<int n, typename ResultType>
    template<typename Operator>
    void ParametricParser<n, ResultType>::addOperator(const std::string &name, Operator &&op, unsigned int precedence) {
        parser.DefineOprt(name,std::forward<Operator>(op),precedence);
    }

    template<int n, typename ResultType>
    template<typename Operator>
    void ParametricParser<n, ResultType>::addOperator(const std::string &name, Operator &&op, unsigned int precedence,bool rightAssociative) {
        parser.DefineOprt(name,std::forward<Operator>(op),precedence,static_cast<mu::EOprtAssociativity>(rightAssociative));
    }


} // parser

#endif //IMAGEPROCESSING_PARAMETRICPARSER_H
