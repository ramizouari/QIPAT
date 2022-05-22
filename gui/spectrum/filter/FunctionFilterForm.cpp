//
// Created by ramizouari on 16/05/22.
//

#include <QLabel>
#include "FunctionFilterForm.h"
#include "parser/PlanarParser.h"
#include "functional/zip.h"
#include "parser/ImageFunctionParser.h"

namespace GUI::spectrum::filter {
            FunctionFilterForm::FunctionFilterForm(int width, int height, QWidget *parent) : FilterForm(width, height,
                                                                                                        parent) {
                    expressionInput = new QPlainTextEdit(this);
                    setLayout(new QFormLayout);
                    layout()->addWidget(new QLabel("Expression"));
                    layout()->addWidget(expressionInput);
            }

    void FunctionFilterForm::setImage(const image::Image &img, image::Real totalEnergy) {
                this->totalEnergy=totalEnergy;
                this->imagePtr=&img;

    }

    void FunctionFilterForm::setImage(const image::Image *imagePtr, image::Real totalEnergy) {
        this->totalEnergy=totalEnergy;
        this->imagePtr=imagePtr;
    }

    image::Image FunctionFilterForm::apply(const image::Image &src) const {
        auto E=expressionInput->toPlainText().toStdString();
        if(E.empty())
            E="1";
        parser::ImageFunctionParser parser(E, width, height);
       for(int i=0;i<src.nb_channel;i++)
            {
                std::string channelTotalEnergyName="E";
                channelTotalEnergyName+=std::to_string(i+1);
                parser.addDependentVariable(channelTotalEnergyName,
                                            [&img = src, i](const std::array<unsigned int, 3> &X)->parser::Real {
                                                return img(i, X[0], X[1]);
                                            });

                std::string channelEnergyPercentageName="Q";
                channelEnergyPercentageName+=std::to_string(i+1);
                parser.addDependentVariable(channelEnergyPercentageName,
                                            [&img = src, i,totalEnergy=this->totalEnergy](const std::array<unsigned int, 3> &X)->parser::Real {
                                                return img(i, X[0], X[1]) / totalEnergy;
                                            });
            }
       parser.addDependentVariable("E",[&img = src](const std::array<unsigned int, 3> &X)->parser::Real {
           return img(X[2],X[0],X[1]);});
        parser.addFunction("E",[](void* imgPtr,parser::Real c,parser::Real i,parser::Real j)->parser::Real
        {
            image::TranslationalPadding padding(*static_cast<image::Image*>(imgPtr));
            return padding(c,i,j);
        },&src);
        std::vector<parser::Real> mins = {0, 0,0};
        std::vector<parser::Real> maxs = {static_cast<double>(width-1), static_cast<double>(height-1),static_cast<double>(src.nb_channel-1)};
        std::vector<int> nbPoints = {width, height,src.nb_channel};
        image::Image dst(src);
        auto S=parser.parseInterval(mins,maxs,nbPoints);
        for(int c=0;c<src.nb_channel;c++) for(int i=0;i<src.width;i++) for(int j=0;j<src.height;j++)
            dst(c,i,j)=S[i][j][c];
        return dst;
    }
} // filter