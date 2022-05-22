//
// Created by ramizouari on 21/05/22.
//

#ifndef IMAGEPROCESSING_PLANARPARSER_H
#define IMAGEPROCESSING_PLANARPARSER_H

#include "ParametricParser.h"

namespace parser {

    template<typename ResultType>
    class PlanarParser : public ParametricParser<2,ResultType>
    {
        using ParametricParser<2,ResultType>::parser;
        using ParametricParser<2,ResultType>::indexes;
        using ParametricParser<2,ResultType>::variables;
        using ParametricParser<2,ResultType>::addConstant;
    public:
        explicit PlanarParser(const std::string &expression, Real width, Real height,bool discrete=false):ParametricParser<2,ResultType>(expression, "x", "y"),
                width(width), height(height), discreteBasis(discrete)
        {
            parser.DefineVar("i", &indexesReal[0]);
            parser.DefineVar("j", &indexesReal[1]);
            parser.DefineVar("u", &normalizedVariables[0]);
            parser.DefineVar("v", &normalizedVariables[1]);
            parser.DefineVar("r", &polarVariables[0]);
            parser.DefineVar("t", &polarVariables[1]);
            addConstant("n",width);
            addConstant("m",height);
            addConstant("size",width*height);
            addConstant("N",width);
            addConstant("M",height);
            addConstant("S",width*height);
        }
        ~PlanarParser() = default;
        void setParameter(int index,Real val,int pos,bool updateDependentVariables) override
        {
            if (index == 0) {
                normalizedVariables[0] = 2*val/width-1;
                variables[0] = recenter(val,width,discreteBasis);
            } else {
                normalizedVariables[1] = 2*val/height-1;
                variables[1] = recenter(val,height,discreteBasis);
            }
            indexes[index]=pos;
            indexesReal[index] = pos;
            std::complex<Real> z(variables[0], variables[1]);
            polarVariables[0] = std::abs(z);
            polarVariables[1] = std::arg(z);
            if(updateDependentVariables)
                this->updateDependentVariables();
        }
    private:
        Real width,height;
        std::array<Real,2> normalizedVariables;
        std::array<Real,2> indexesReal;
        std::array<Real,2> polarVariables;
        bool discreteBasis;
        static Real recenter(Real val,Real w,bool discrete)
        {
            if(discrete)
                return val-std::lround(w)/2;
            else
                return val-w/2;
        }
    };

    using PlanarFunctionParser = PlanarParser<Real>;
    using PlanarRelationParser = PlanarParser<bool>;

} // parser

#endif //IMAGEPROCESSING_PLANARPARSER_H
