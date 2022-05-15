//
// Created by ramizouari on 15/05/22.
//

#ifndef IMAGEPROCESSING_RELATIONALEQUATIONMASKFORM_H
#define IMAGEPROCESSING_RELATIONALEQUATIONMASKFORM_H

#include <QLineEdit>
#include "MaskForm.h"
#include "parser/PlanarRelationParser.h"
#include <QTextEdit>
#include <QPlainTextEdit>

namespace GUI::options {

        class RelationalEquationMaskForm : public MaskForm {
        Q_OBJECT
        public:

            explicit RelationalEquationMaskForm(int width, int height, QWidget *parent = nullptr);
            ~RelationalEquationMaskForm() override = default;
            void setImage(const image::Image &img,image::Real totalEnergy);
            void setImage(const image::Image *imagePtr, image::Real totalEnergy);
            std::vector<std::vector<bool>> generateMask() override;
        public:
            QPlainTextEdit* expressionInput;
            const image::Image *imagePtr;
            image::Real totalEnergy;
        };

    } // options

#endif //IMAGEPROCESSING_RELATIONALEQUATIONMASKFORM_H
