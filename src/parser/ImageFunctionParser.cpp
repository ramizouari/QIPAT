//
// Created by ramizouari on 16/05/22.
//

#include "ImageFunctionParser.h"

namespace parser {
    ImageFunctionParser::ImageFunctionParser(const std::string &expression, Real width, Real height):ParametricParser(expression, "x", "y","c"), width(width), height(height)
    {
        parser.DefineVar("i", &indexesReal[0]);
        parser.DefineVar("j", &indexesReal[1]);
        parser.DefineVar("u", &normalizedVariables[0]);
        parser.DefineVar("v", &normalizedVariables[1]);
        parser.DefineVar("r", &polarVariables[0]);
        parser.DefineVar("t", &polarVariables[1]);
    }

    void ImageFunctionParser::setParameter(int index, Real val, int pos,bool updateDependentVariables) {
        if (index == 0) {
            normalizedVariables[0] = 2*val/width-1;
            variables[0] = val-width/2;
        } else if(index==1){
            normalizedVariables[1] = 2*val/height-1;
            variables[1] = val-height/2;
        }
        else
            variables[2]=val;
        indexes[index]=pos;
        indexesReal[index]=pos;
        std::complex<Real> z(variables[0], variables[1]);
        polarVariables[0] = std::abs(z);
        polarVariables[1] = std::arg(z);
        if(updateDependentVariables)
            this->updateDependentVariables();
    }
} // parser