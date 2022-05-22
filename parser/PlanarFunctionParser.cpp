//
// Created by ramizouari on 21/05/22.
//

#include "PlanarFunctionParser.h"

namespace parser {
    PlanarFunctionParser::PlanarFunctionParser(const std::string &expression, Real width, Real height): ParametricParser(expression, "x", "y"), width(width), height(height)
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

    void PlanarFunctionParser::setParameter(int index, Real val, int pos,bool updateDependentVariables) {
        if (index == 0) {
            normalizedVariables[0] = 2*val/width-1;
            variables[0] = val-std::lround(width)/2;
        } else {
            normalizedVariables[1] = 2*val/height-1;
            variables[1] = val-std::lround(height)/2;
        }
        indexes[index]=pos;
        indexesReal[index] = pos;
        std::complex<Real> z(variables[0], variables[1]);
        polarVariables[0] = std::abs(z);
        polarVariables[1] = std::arg(z);
        if(updateDependentVariables)
            this->updateDependentVariables();
    }
} // parser