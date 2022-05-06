//
// Created by ramizouari on 03/05/22.
//

#include <QHBoxLayout>
#include "ContrastDialog.h"

namespace GUI::options {
        ContrastDialog::ContrastDialog(QWidget *parent) : QDialog(parent){
            layout = new QVBoxLayout;
            subLayout = new QHBoxLayout;
            form=new ContrastForm(this);
            contrastView=new ContrastTransformationView(this);
            subLayout->addWidget(contrastView);
            subLayout->addWidget(form);
            layout->addItem(subLayout);

            dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
            layout->addWidget(dialogButtonBox);
            connect(form,&ContrastForm::valueUpdated,contrastView,&ContrastTransformationView::addOrReplace);
            connect(form,static_cast<void(ContrastForm::*)()>(&ContrastForm::requestPointAdd),contrastView,&ContrastTransformationView::appendPoint);
            connect(form,&ContrastForm::requestPointRemove,contrastView,&ContrastTransformationView::removePoint);
            connect(dialogButtonBox, &QDialogButtonBox::accepted, this, &ContrastDialog::accept);
            connect(dialogButtonBox, &QDialogButtonBox::rejected, this, &ContrastDialog::reject);
            setLayout(layout);
            resize(500,500);
        }

    std::vector<image::Vector2> ContrastDialog::getPoints() {
        return contrastView->getPoints();
    }

    std::vector<std::pair<image::Real, image::Real>> ContrastDialog::getPointsPair() {
        return contrastView->getPointsPair();
    }
} // options