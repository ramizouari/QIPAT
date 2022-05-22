//
// Created by ramizouari on 21/05/22.
//

#ifndef IMAGEPROCESSING_PLANARFUNCTIONPARSER_H
#define IMAGEPROCESSING_PLANARFUNCTIONPARSER_H

#include "ParametricParser.h"

namespace parser {
    class PlanarFunctionParser : public ParametricParser<2,parser::Real>
    {
    public:
        explicit PlanarFunctionParser(const std::string &expression, Real width, Real height);
        ~PlanarFunctionParser() = default;
        void setParameter(int index,Real val,int pos,bool updateDependentVariables=true) override;
    private:
        Real width,height;
        std::array<Real,2> normalizedVariables;
        std::array<Real,2> indexesReal;
        std::array<Real,2> polarVariables;
    };

} // parser

#endif //IMAGEPROCESSING_PLANARFUNCTIONPARSER_H
