//
// Created by ramizouari on 22/05/22.
//

#ifndef IMAGEPROCESSING_LINEPARSER_H
#define IMAGEPROCESSING_LINEPARSER_H

#include "ParametricParser.h"

namespace parser {

    template<typename ResultType>
    class LineParser :public ParametricParser<1,ResultType> {
        using ParametricParser<1,ResultType>::parser;
        using ParametricParser<1,ResultType>::indexes;
        using ParametricParser<1,ResultType>::variables;
    public:
        explicit LineParser(const std::string &expression,Real xmin,Real xmax):ParametricParser<1,ResultType>(expression,"x"),xmin(xmin),xmax(xmax)
        {
            parser->DefineVar("t",&normalizedVariable);
            parser->DefineVar("i",&indexReal);
        }

        void setParameter(int index,Real val,int pos,bool updateDependentVariables=true) override
        {
            normalizedVariable = (val-xmin)/(xmax-xmin);
            indexes[index]=pos;
            indexReal = pos;
            variables[index] = val;
            if(updateDependentVariables)
                this->updateDependentVariables();
        }
        ~LineParser() override = default;
    private:
        Real normalizedVariable;
        Real indexReal;
        Real xmin,xmax;
    };

    using LineParserFunction = LineParser<Real>;
    using LineParserRelation = LineParser<bool>;

} // parser

#endif //IMAGEPROCESSING_LINEPARSER_H
