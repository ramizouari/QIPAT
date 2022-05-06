//
// Created by ramizouari on 03/05/22.
//

#ifndef IMAGEPROCESSING_CONTRASTDIALOG_H
#define IMAGEPROCESSING_CONTRASTDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include "ContrastForm.h"
#include "ContrastTransformationView.h"

namespace GUI::options {

        class ContrastDialog:public QDialog {
            Q_OBJECT
        public:
            explicit ContrastDialog(QWidget *parent = nullptr);

            std::vector<image::Vector2> getPoints();
            std::vector<std::pair<image::Real,image::Real>> getPointsPair();
        private:
            ContrastForm* form;
            ContrastTransformationView *contrastView;
            QLayout *layout,*subLayout;
            QDialogButtonBox *dialogButtonBox;
        };

    } // options

#endif //IMAGEPROCESSING_CONTRASTDIALOG_H
