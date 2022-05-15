//
// Created by ramizouari on 14/05/22.
//

#ifndef IMAGEPROCESSING_SPECTRUMMASKDIALOG_H
#define IMAGEPROCESSING_SPECTRUMMASKDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QStatusBar>
#include <QDialogButtonBox>
#include <QComboBox>
#include <QStackedWidget>
#include <QFormLayout>
#include <QCheckBox>
#include "gui/spectrum/SpectrumMaskView.h"
#include "gui/spectrum/mask/MaskForm.h"

namespace GUI::options {

        class SpectrumMaskDialog: public QDialog {
            Q_OBJECT
        public:
            explicit SpectrumMaskDialog(const image::Image & img, QWidget *parent = nullptr);
            ~SpectrumMaskDialog() override = default;
            std::vector<std::vector<bool>> getMask();
            bool isInverted() const;
        public slots:
            void preview();
        private:
            QStatusBar *statusBar;
            QBoxLayout *layout,*subLayout;
            QFormLayout *formLayout;
            QDialogButtonBox *dialogButtonBox;
            QComboBox* maskChoice;
            spectrum::SpectrumMaskView *view;
            QStackedWidget *stackedWidget;
            MaskForm *rectangleForm,*circleForm,*relationalEquationForm;
            QPushButton *previewButton;
            QCheckBox *invertMaskCheckBox;
        };

    } // options

#endif //IMAGEPROCESSING_SPECTRUMMASKDIALOG_H
