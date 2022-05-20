//
// Created by ramizouari on 16/05/22.
//

#ifndef IMAGEPROCESSING_IMAGEFUNCTIONPARSER_H
#define IMAGEPROCESSING_IMAGEFUNCTIONPARSER_H

#include "image/Image.h"
#include "ParametricParser.h"

namespace parser {

class ImageFunctionParser  : public ParametricParser<3,image::Real>{
public:
        explicit ImageFunctionParser(const std::string &expression, Real width, Real height);
        ~ImageFunctionParser() = default;
        void setParameter(int index,Real val,int pos,bool updateDependentVariables=true) override;
    private:
        Real width,height;
        std::array<Real,2> normalizedVariables;
        std::array<Real,3> indexesReal;
        std::array<Real,2> polarVariables;
    };

} // parser

#endif //IMAGEPROCESSING_IMAGEFUNCTIONPARSER_H
