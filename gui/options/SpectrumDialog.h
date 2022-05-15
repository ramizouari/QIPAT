//
// Created by ramizouari on 14/05/22.
//

#ifndef IMAGEPROCESSING_SPECTRUMDIALOG_H
#define IMAGEPROCESSING_SPECTRUMDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QStatusBar>
#include <QDialogButtonBox>
#include <QComboBox>
#include <QStackedWidget>
#include <QFormLayout>
#include <QCheckBox>
#include "gui/spectrum/SpectrumFilterView.h"

namespace GUI::options {

        class SpectrumDialog: public QDialog {
            Q_OBJECT
        public:
            explicit SpectrumDialog(const image::Image & img, QWidget *parent = nullptr);
            ~SpectrumDialog() override = default;
            std::vector<std::vector<bool>> getMask();
            bool isInverted() const;
        public slots:
            void preview();
        private:
            QLabel *label;
            QStatusBar *statusBar;
            QBoxLayout *layout,*subLayout;
            QFormLayout *formLayout;
            QDialogButtonBox *dialogButtonBox;
            QComboBox* maskChoice;
            spectrum::SpectrumFilterView *view;
            QStackedWidget *stackedWidget;
            QWidget *rectangleForm,*circleForm;
            QPushButton *previewButton;
            QCheckBox *invertMaskCheckBox;
        };

    } // options

#endif //IMAGEPROCESSING_SPECTRUMDIALOG_H
