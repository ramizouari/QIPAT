//
// Created by ramizouari on 15/05/22.
//

#include "PlanarRelationParser.h"

namespace parser {
    PlanarRelationParser::PlanarRelationParser(const std::string &expression, Real width, Real height): ParametricParser(expression, "x", "y"), width(width), height(height)
    {
        parser.DefineVar("i", &indexesReal[0]);
        parser.DefineVar("j", &indexesReal[1]);
        parser.DefineVar("u", &normalizedVariables[0]);
        parser.DefineVar("v", &normalizedVariables[1]);
        parser.DefineVar("r", &polarVariables[0]);
        parser.DefineVar("t", &polarVariables[1]);
    }

    void PlanarRelationParser::setParameter(int index, Real val, int pos) {
        if (index == 0) {
            normalizedVariables[0] = 2*val/width-1;
            indexesReal[0] = pos;
            indexes[0] = pos;
            variables[0] = val-width/2;
        } else {
            normalizedVariables[1] = 2*val/height-1;
            indexesReal[1] = pos;
            variables[1] = val-height/2;
            indexes[1]=pos;
        }
        std::complex<Real> z(variables[0], variables[1]);
        polarVariables[0] = std::abs(z);
        polarVariables[1] = std::arg(z);
        for(auto &[v,f]:dependentVariables) {
            if (f.index() == 0)
                *v = std::get<0>(f)(variables);
            else *v = std::get<1>(f)(indexes);
        }
    }
} // parser