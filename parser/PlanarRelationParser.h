//
// Created by ramizouari on 15/05/22.
//

#ifndef IMAGEPROCESSING_PLANARRELATIONPARSER_H
#define IMAGEPROCESSING_PLANARRELATIONPARSER_H
#include "muParser.h"
#include "image/Image.h"
#include "ParametricParser.h"

namespace parser {

    class PlanarRelationParser : public ParametricParser<2,bool>
    {
    public:
        explicit PlanarRelationParser(const std::string &expression, Real width, Real height);
        ~PlanarRelationParser() = default;
        bool parse(const std::vector<image::Real> &values);
        [[nodiscard]] image::Real getValue() const;
        void setParameter(int index,Real val,int pos) override;
    private:
        Real width,height;
        std::array<Real,2> normalizedVariables;
        std::array<Real,2> indexesReal;
        std::array<Real,2> polarVariables;
    };

} // parser

#endif //IMAGEPROCESSING_PLANARRELATIONPARSER_H
