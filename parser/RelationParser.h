//
// Created by ramizouari on 15/05/22.
//

#ifndef IMAGEPROCESSING_RELATIONPARSER_H
#define IMAGEPROCESSING_RELATIONPARSER_H
#include "muParser.h"
#include "image/Image.h"
#include "ParametricParser.h"

namespace parser {

    class RelationParser :public ParametricParser<2,bool>
    {
    public:
        explicit RelationParser(const std::string &expression,Real width,Real height);
        ~RelationParser() = default;
        bool parse(const std::vector<image::Real> &values);
        [[nodiscard]] image::Real getValue() const;
        void setParameter(int index,Real val,int pos) override;
    private:
        Real width,height;
        std::array<Real,2> normalizedVariables;
        std::array<Real,2> indices;
        std::array<Real,2> polarVariables;
    };

} // parser

#endif //IMAGEPROCESSING_RELATIONPARSER_H
