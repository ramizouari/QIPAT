//
// Created by ramizouari on 15/05/22.
//
#include <QLayout>
#include <QLabel>
#include <QFormLayout>

#include "RelationalEquationMaskForm.h"

namespace GUI::options {
        RelationalEquationMaskForm::RelationalEquationMaskForm(int width, int height, QWidget *parent) : MaskForm(width,
                                                                                                                  height,parent) {
            expressionInput = new QPlainTextEdit(this);
            setLayout(new QFormLayout);
            layout()->addWidget(new QLabel("Expression"));
            layout()->addWidget(expressionInput);
        }

        std::vector<std::vector<bool>> RelationalEquationMaskForm::generateMask() {
            auto E=expressionInput->toPlainText().toStdString();
            if(E.empty())
                E="1";
            parser::RelationParser parser(E,width,height);
            std::vector<parser::Real> mins = {0, 0};
            std::vector<parser::Real> maxs = {static_cast<double>(width), static_cast<double>(height)};
            std::vector<int> nbPoints = {width, height};
            auto R=parser.parseInterval(mins, maxs, nbPoints);
            return R;
        }
    } // options