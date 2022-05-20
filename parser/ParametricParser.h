//
// Created by ramizouari on 15/05/22.
//

#ifndef IMAGEPROCESSING_PARAMETRICPARSER_H
#define IMAGEPROCESSING_PARAMETRICPARSER_H

#include <vector>
#include <muParser.h>
#include <span>
#include "algebra/abstract_algebra.h"
#include <variant>

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

    using Real=double;
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


} // parser

#endif //IMAGEPROCESSING_PARAMETRICPARSER_H
