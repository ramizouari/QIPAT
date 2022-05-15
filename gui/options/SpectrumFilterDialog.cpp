//
// Created by ramizouari on 15/05/22.
//

#include "SpectrumFilterDialog.h"
#include "gui/spectrum/filter/GaussianBlurForm.h"
#include "gui/spectrum/filter/MeanBlurForm.h"
#include "image/utils.h"
#include "functional/zip.h"
#include "gui/spectrum/filter/MedianForm.h"

namespace GUI::options {
        SpectrumFilterDialog::SpectrumFilterDialog(const image::Image &img, QWidget *parent):QDialog(parent) {
            auto &&[imageReal,imageImaginary] = image::convolution::spectrumToImagePair(image::convolution::imageToSpectrum(img));
            realImagePtr = std::make_unique<image::Image>(image::convolution::phaseTransform(imageReal));
            imaginaryImagePtr = std::make_unique<image::Image>(image::convolution::phaseTransform(imageImaginary));
            layout = new QVBoxLayout;
            layout->setObjectName("SpectrumDialogLayout");
            subLayout = new QHBoxLayout;
            subLayout->setObjectName("SpectrumDialogSubLayout");
            view=new spectrum::SpectrumMaskView(img, this);
            subLayout->addWidget(view);

            formLayout=new QFormLayout;
            formLayout->setObjectName("SpectrumDialogFormLayout");
            maskChoice = new QComboBox(this);
            maskChoice->addItem("Gaussian Blur");
            maskChoice->addItem("Mean Blur");
            maskChoice->addItem("Median");
            maskChoice->addItem("Function Equation");
            stackedWidget=new QStackedWidget(this);
            gaussianForm=new spectrum::filter::GaussianBlurForm(img.width,img.height,stackedWidget);
            stackedWidget->addWidget(gaussianForm);
            meanForm=new spectrum::filter::MeanBlurForm(img.width,img.height,stackedWidget);
            stackedWidget->addWidget(meanForm);
            medianForm=new spectrum::filter::MedianForm(img.width,img.height,stackedWidget);
            stackedWidget->addWidget(medianForm);

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
            connect(previewButton,&QPushButton::clicked,this,&SpectrumFilterDialog::preview);
            resize(500,500);
        }

    void SpectrumFilterDialog::preview()
    {
            auto filterForm=dynamic_cast<spectrum::filter::FilterForm*>(stackedWidget->currentWidget());
            realImagePtr = std::make_unique<image::Image>(filterForm->apply(*realImagePtr));
            imaginaryImagePtr = std::make_unique<image::Image>(filterForm->apply(*imaginaryImagePtr));
            image::Image energySpectrum(realImagePtr->width,realImagePtr->height,realImagePtr->nb_channel);
            for(auto [A,B,C] : functional::zip(realImagePtr->data,imaginaryImagePtr->data,energySpectrum.data))
                for(auto [U,V,W] : functional::zip(A,B,C)) for(auto [x,y,z]: functional::zip(U,V,W))
                    z=std::sqrt(x*x+y*y);
        view->setSpectrum(energySpectrum);
        statusBar->showMessage("Remaining Energy: "+QString::number(static_cast<double>(view->getRemainingEnergy()/view->getTotalEnergy()*100))+"%");
    }

    std::pair<image::Image,image::Image> SpectrumFilterDialog::apply() const {
        return std::make_pair(*realImagePtr,*imaginaryImagePtr);
    }
} // options