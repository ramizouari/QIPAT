//
// Created by ramizouari on 21/05/22.
//

#include <QFormLayout>
#include <QPlainTextEdit>
#include <QLabel>
#include <QSpinBox>
#include "MatrixExpression.h"
#include "parser/PlanarRelationParser.h"
#include "functional/zip.h"
#include "parser/PlanarFunctionParser.h"

namespace GUI::options {
        MatrixExpression::MatrixExpression(QWidget *parent) :MatrixInput(parent){

            mainLayout=new QFormLayout;
            generatorExpression=new QPlainTextEdit;
            rowSpinBox=new QSpinBox(this);
            columnSpinBox=new QSpinBox(this);
            mainLayout->addRow("Row:",rowSpinBox);
            mainLayout->addRow("Column:",columnSpinBox);
            mainLayout->addRow("Expression:",generatorExpression);
            rowSpinBox->setMinimum(1);
            columnSpinBox->setMinimum(1);
            rowSpinBox->setValue(3);
            columnSpinBox->setValue(3);
            normalizeCheckBox=new QCheckBox("Normalize",this);
            mainLayout->addRow(normalizeCheckBox);
            setLayout(mainLayout);

        }

    image::Matrix MatrixExpression::getConvolutionMatrix() {
        auto width=rowSpinBox->value(),height=columnSpinBox->value();
        image::Matrix M(0,linalg::m_shape{width,height});
        parser::PlanarFunctionParser parser(generatorExpression->toPlainText().toStdString(),width,height);
        std::vector<parser::Real> maxs({static_cast<parser::Real>(width-1),static_cast<parser::Real>(height-1)});
        auto N=parser.parseInterval({0,0},maxs,{width,height});
        parser::Real k=0;
        if(normalizeCheckBox->isChecked()) for(auto &A:N) for(auto &x:A) k+=x;
        else k=1;
        for(auto [A,B] : functional::zip(M,N)) for(auto [a,b] : functional::zip(A,B))
            a=b/k;
        return M;
    }
} // options