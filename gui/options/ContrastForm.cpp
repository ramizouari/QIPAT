//
// Created by ramizouari on 03/05/22.
//

#include <QPushButton>
#include <QFormLayout>
#include <QLabel>
#include "ContrastForm.h"

namespace GUI::options {
        ContrastForm::ContrastForm(QWidget *parent)
        {
            addPointButton = new QPushButton("Add point", this);
            auto boxLayout = new QVBoxLayout(this);
            setLayout(boxLayout);
            using namespace std::placeholders;
            for(int i=0;i<2;i++)
            {
                auto rowWidget=new ContrastFormRow(i==0?ContrastFormRow::Type::FIRST:ContrastFormRow::Type::LAST,this);
                connect(rowWidget, &ContrastFormRow::requestRemove, boxLayout,[boxLayout,rowWidget,this]()
                {
                    emit requestPointRemove(boxLayout->indexOf(rowWidget));
                    boxLayout->removeWidget(rowWidget);
                    rowWidget->deleteLater();
                });
                connect(rowWidget,&ContrastFormRow::valueUpdated,this,[this,boxLayout,rowWidget](int x,int y)
                {
                    emit valueUpdated(boxLayout->indexOf(rowWidget),x,y);
                });
                boxLayout->addWidget(rowWidget,Qt::AlignTop);
                boxLayout->setStretch(i,0);
            }
            boxLayout->addItem(new QSpacerItem(0,0,QSizePolicy::Minimum,QSizePolicy::Expanding));
            boxLayout->addWidget(addPointButton,Qt::AlignBottom);
            boxLayout->setAlignment(Qt::AlignTop);
            connect(addPointButton,&QPushButton::clicked,this,[this,boxLayout]
            {
                auto rowWidget=new ContrastFormRow(ContrastFormRow::Type::MIDDLE,this);
                connect(rowWidget, &ContrastFormRow::requestRemove, boxLayout,[boxLayout,rowWidget,this]()
                {
                    emit requestPointRemove(boxLayout->indexOf(rowWidget));
                    boxLayout->removeWidget(rowWidget);
                    rowWidget->deleteLater();
                });
                connect(rowWidget,&ContrastFormRow::valueUpdated,this,[this,boxLayout,rowWidget](int x,int y)
                {
                    emit valueUpdated(boxLayout->indexOf(rowWidget),x,y);
                });
                boxLayout->insertWidget(boxLayout->count()-3,rowWidget,Qt::AlignTop);
                boxLayout->setStretch(boxLayout->count()-4,0);
                emit requestPointAdd();
            });
        }

    ContrastFormRow::ContrastFormRow(Type type,QWidget *parent) : QWidget(parent)
    {
        auto layout=new QGridLayout;
        setLayout(layout);
        xCoordinate=new QSpinBox(this);
        yCoordinate=new QSpinBox(this);
        removeButton=new QPushButton(QIcon::fromTheme("list-remove"),QString(),this);
        xCoordinate->setRange(0,255);
        yCoordinate->setRange(0,255);
        switch (type)
        {
            case Type::FIRST:
                xCoordinate->setValue(0);
                yCoordinate->setValue(0);
                removeButton->setEnabled(false);
                xCoordinate->setReadOnly(true);
                //yCoordinate->setReadOnly(true);
                break;
            case Type::LAST:
                xCoordinate->setValue(255);
                yCoordinate->setValue(255);
                removeButton->setEnabled(false);
                xCoordinate->setReadOnly(true);
                //yCoordinate->setReadOnly(true);
                break;
            case Type::MIDDLE:
                xCoordinate->setValue(128);
                yCoordinate->setValue(128);

                break;
        }

        layout->addWidget(new QLabel("X: "),0,0);
        layout->addWidget(xCoordinate,0,1);
        layout->addWidget(new QLabel("Y: "),0,2);
        layout->addWidget(yCoordinate,0,3);
        layout->addWidget(removeButton,0,4);
        layout->setAlignment(Qt::AlignTop);
        connect(removeButton,&QPushButton::clicked,this,&ContrastFormRow::requestRemove);
        connect(xCoordinate,static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,[this](int x)
        {
            emit valueUpdated(x,yCoordinate->value());
        });
        connect(yCoordinate,static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,[this](int y)
        {
            emit valueUpdated(xCoordinate->value(),y);
        });
    }


    SplineContrastForm::SplineContrastForm(QWidget *parent)
    {
        addPointButton = new QPushButton("Add point", this);
        auto boxLayout = new QVBoxLayout(this);
        setLayout(boxLayout);
        using namespace std::placeholders;
        for(int i=0;i<2;i++)
        {
            auto rowWidget=new SplineContrastFormRow(i==0?SplineContrastFormRow::Type::FIRST:SplineContrastFormRow::Type::LAST,this);
            connect(rowWidget, &SplineContrastFormRow::requestRemove, boxLayout,[boxLayout,rowWidget,this]()
            {
                emit requestPointRemove(boxLayout->indexOf(rowWidget));
                boxLayout->removeWidget(rowWidget);
                rowWidget->deleteLater();
            });
            connect(rowWidget,&SplineContrastFormRow::valueUpdated,this,[this,boxLayout,rowWidget](int x,int y,image::Real dy)
            {
                emit valueUpdated(boxLayout->indexOf(rowWidget),x,y,dy);
            });
            boxLayout->addWidget(rowWidget,Qt::AlignTop);
            boxLayout->setStretch(i,0);
        }
        boxLayout->addItem(new QSpacerItem(0,0,QSizePolicy::Minimum,QSizePolicy::Expanding));
        boxLayout->addWidget(addPointButton,Qt::AlignBottom);
        boxLayout->setAlignment(Qt::AlignTop);
        connect(addPointButton,&QPushButton::clicked,this,[this,boxLayout]
        {
            auto rowWidget=new SplineContrastFormRow(SplineContrastFormRow::Type::MIDDLE,this);
            connect(rowWidget, &SplineContrastFormRow::requestRemove, boxLayout,[boxLayout,rowWidget,this]()
            {
                emit requestPointRemove(boxLayout->indexOf(rowWidget));
                boxLayout->removeWidget(rowWidget);
                rowWidget->deleteLater();
            });
            connect(rowWidget,&SplineContrastFormRow::valueUpdated,this,[this,boxLayout,rowWidget](int x,int y,image::Real dy)
            {
                emit valueUpdated(boxLayout->indexOf(rowWidget),x,y,dy);
            });
            boxLayout->insertWidget(boxLayout->count()-3,rowWidget,Qt::AlignTop);
            boxLayout->setStretch(boxLayout->count()-4,0);
            emit requestPointAdd();
        });
    }

    SplineContrastFormRow::SplineContrastFormRow(Type type,QWidget *parent) : QWidget(parent)
    {
        auto layout=new QGridLayout;
        setLayout(layout);
        xCoordinate=new QSpinBox(this);
        yCoordinate=new QSpinBox(this);
        yDerivative=new QDoubleSpinBox(this);
        removeButton=new QPushButton(QIcon::fromTheme("list-remove"),QString(),this);
        xCoordinate->setRange(0,255);
        yCoordinate->setRange(0,255);
        yDerivative->setRange(-255,255);
        switch (type)
        {
            case Type::FIRST:
                xCoordinate->setValue(0);
                yCoordinate->setValue(0);
                removeButton->setEnabled(false);
                xCoordinate->setReadOnly(true);
                yDerivative->setValue(1);
                //yCoordinate->setReadOnly(true);
                break;
            case Type::LAST:
                xCoordinate->setValue(255);
                yCoordinate->setValue(255);
                removeButton->setEnabled(false);
                xCoordinate->setReadOnly(true);
                yDerivative->setValue(1);
                //yCoordinate->setReadOnly(true);
                break;
            case Type::MIDDLE:
                xCoordinate->setValue(128);
                yCoordinate->setValue(128);
                yDerivative->setValue(1);

                break;
        }

        layout->addWidget(new QLabel("X: "),0,0);
        layout->addWidget(xCoordinate,0,1);
        layout->addWidget(new QLabel("Y: "),0,2);
        layout->addWidget(yCoordinate,0,3);
        layout->addWidget(new QLabel("Y': "),0,4);
        layout->addWidget(yDerivative,0,5);
        layout->addWidget(removeButton,0,6);
        layout->setAlignment(Qt::AlignTop);
        connect(removeButton,&QPushButton::clicked,this,&SplineContrastFormRow::requestRemove);
        connect(xCoordinate,static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,[this](int x)
        {
            emit valueUpdated(x,yCoordinate->value(),yDerivative->value());
        });
        connect(yCoordinate,static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,[this](int y)
        {
            emit valueUpdated(xCoordinate->value(),y,yDerivative->value());
        });

        connect(yDerivative,static_cast<void(QDoubleSpinBox::*)(qreal)>(&QDoubleSpinBox::valueChanged),this,[this](qreal y)
        {
            emit valueUpdated(xCoordinate->value(),yCoordinate->value(),y);
        });
    }
} // options