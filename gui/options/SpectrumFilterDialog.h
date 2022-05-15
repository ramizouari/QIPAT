//
// Created by ramizouari on 15/05/22.
//

#ifndef IMAGEPROCESSING_SPECTRUMFILTERDIALOG_H
#define IMAGEPROCESSING_SPECTRUMFILTERDIALOG_H

#include <QDialog>
#include <QStatusBar>
#include <QBoxLayout>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QComboBox>
#include <QStackedWidget>
#include <QPushButton>
#include <QCheckBox>
#include "image/Image.h"
#include "gui/spectrum/SpectrumMaskView.h"
#include "gui/spectrum/mask/MaskForm.h"
#include "gui/spectrum/filter/FilterForm.h"

namespace GUI::options {

        class SpectrumFilterDialog :public QDialog{
            Q_OBJECT
        public:
            explicit SpectrumFilterDialog(const image::Image & img, QWidget *parent = nullptr);
            ~SpectrumFilterDialog() override = default;
        public slots:
            void preview();
            [[nodiscard]] std::pair<image::Image,image::Image> apply() const;
        private:
            QStatusBar *statusBar;
            QBoxLayout *layout,*subLayout;
            QFormLayout *formLayout;
            QDialogButtonBox *dialogButtonBox;
            QComboBox* maskChoice;
            spectrum::SpectrumMaskView *view;
            QStackedWidget *stackedWidget;
            spectrum::filter::FilterForm *gaussianForm,*meanForm,*medianForm,*functionalForm;
            QPushButton *previewButton;
            QCheckBox *invertMaskCheckBox;
            image::Image* imagePtr;
            std::unique_ptr<image::Image> realImagePtr,imaginaryImagePtr;
        };

    } // options

#endif //IMAGEPROCESSING_SPECTRUMFILTERDIALOG_H
