//
// Created by ramizouari on 15/05/22.
//
#include <QLayout>
#include <QLabel>
#include <QFormLayout>

#include "RelationalEquationMaskForm.h"
#include "image/Padding.h"

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
            parser::PlanarRelationParser parser(E, width, height);
            if(imagePtr) for(int i=0;i<imagePtr->nb_channel;i++)
            {
                std::string channelTotalEnergyName="E";
                channelTotalEnergyName+=std::to_string(i+1);
                parser.addDependentVariable(channelTotalEnergyName,
                                            [&img = *imagePtr, i](const std::array<unsigned int, 2> &X)->parser::Real {
                                                return img(i, X[0], X[1]);
                                            });

                std::string channelEnergyPercentageName="Q";
                channelEnergyPercentageName+=std::to_string(i+1);
                parser.addDependentVariable(channelEnergyPercentageName,
                                            [&img = *imagePtr, i,totalEnergy=this->totalEnergy](const std::array<unsigned int, 2> &X)->parser::Real {
                                                return img(i, X[0], X[1]) / totalEnergy;
                                            });
            }
            parser.addFunction("E",[](void* imgPtr,parser::Real c,parser::Real i,parser::Real j)->parser::Real
            {
                image::TranslationalPadding padding(*static_cast<image::Image*>(imgPtr));
               return padding(c,i,j);
            },imagePtr);
            std::vector<parser::Real> mins = {0, 0};
            std::vector<parser::Real> maxs = {static_cast<double>(width-1), static_cast<double>(height-1)};
            std::vector<int> nbPoints = {width, height};
            auto R=parser.parseInterval(mins, maxs, nbPoints);
            return R;
        }

    void RelationalEquationMaskForm::setImage(const image::Image & img, image::Real E) {
        imagePtr=&img;
        totalEnergy=E;
    }

    void RelationalEquationMaskForm::setImage(const image::Image* _imagePtr,image::Real E) {
            imagePtr=_imagePtr;
            totalEnergy=E;
    }
} // options