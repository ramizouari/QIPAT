//
// Created by ramizouari on 14/05/22.
//

#include <QVBoxLayout>
#include <QHBoxLayout>
#include "SpectrumMaskDialog.h"
#include "gui/spectrum/mask/MaskForm.h"
#include "gui/spectrum/mask/RectangleMaskForm.h"
#include "gui/spectrum/mask/CircleMaskForm.h"
#include "gui/spectrum/mask/RelationalEquationMaskForm.h"
#include <QPushButton>

namespace GUI::options {
        SpectrumMaskDialog::SpectrumMaskDialog(const image::Image &img, QWidget *parent) {
            layout = new QVBoxLayout;
            layout->setObjectName("SpectrumDialogLayout");
            subLayout = new QHBoxLayout;
            subLayout->setObjectName("SpectrumDialogSubLayout");
            view=new spectrum::SpectrumMaskView(img, this);
            subLayout->addWidget(view);


            formLayout=new QFormLayout;
            formLayout->setObjectName("SpectrumDialogFormLayout");
            maskChoice = new QComboBox(this);
            maskChoice->addItem("Rectangle");
            maskChoice->addItem("Circle");
            maskChoice->addItem("Relation");
            stackedWidget=new QStackedWidget(this);
            rectangleForm=new RectangleMaskForm(img.width,img.height,stackedWidget);
            stackedWidget->addWidget(rectangleForm);
            circleForm=new CircleMaskForm(img.width,img.height,stackedWidget);
            stackedWidget->addWidget(circleForm);
            relationalEquationForm=new RelationalEquationMaskForm(img.width,img.height,stackedWidget);
            stackedWidget->addWidget(relationalEquationForm);

            connect(maskChoice, &QComboBox::currentIndexChanged, stackedWidget, &QStackedWidget::setCurrentIndex);
            formLayout->addRow("Choose mask type:",maskChoice);
            formLayout->addWidget(stackedWidget);
            previewButton=new QPushButton("Preview",this);
            invertMaskCheckBox=new QCheckBox("Invert mask",this);
            formLayout->addWidget(invertMaskCheckBox);
            formLayout->addWidget(previewButton);
            subLayout->addLayout(formLayout);
            layout->addLayout(subLayout);

            dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
            layout->addWidget(dialogButtonBox);
            statusBar=new QStatusBar(this);
            layout->addWidget(statusBar);
            setLayout(layout);
            connect(dialogButtonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
            connect(dialogButtonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
            connect(previewButton,&QPushButton::clicked,this,&SpectrumMaskDialog::preview);
            resize(500,500);
        }

    void SpectrumMaskDialog::preview() {
            view->setMask(dynamic_cast<MaskForm*>(stackedWidget->currentWidget())->generateMask(),invertMaskCheckBox->isChecked());
            statusBar->showMessage("Remaining Energy: "+QString::number(static_cast<double>(view->getRemainingEnergy()/view->getTotalEnergy()*100))+"%");
    }

    std::vector<std::vector<bool>> SpectrumMaskDialog::getMask() {
        return view->getMask();
    }

    bool SpectrumMaskDialog::isInverted() const {
        return invertMaskCheckBox->isChecked();
    }
} // options