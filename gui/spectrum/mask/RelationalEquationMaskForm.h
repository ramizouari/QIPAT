//
// Created by ramizouari on 15/05/22.
//

#ifndef IMAGEPROCESSING_RELATIONALEQUATIONMASKFORM_H
#define IMAGEPROCESSING_RELATIONALEQUATIONMASKFORM_H

#include <QLineEdit>
#include "MaskForm.h"
#include "parser/RelationParser.h"
#include <QTextEdit>
#include <QPlainTextEdit>

namespace GUI::options {

        class RelationalEquationMaskForm : public MaskForm {
        Q_OBJECT
        public:

            explicit RelationalEquationMaskForm(int width, int height, QWidget *parent = nullptr);
            ~RelationalEquationMaskForm() override = default;
            std::vector<std::vector<bool>> generateMask() override;
        public:
            QPlainTextEdit* expressionInput;
        };

    } // options

#endif //IMAGEPROCESSING_RELATIONALEQUATIONMASKFORM_H
