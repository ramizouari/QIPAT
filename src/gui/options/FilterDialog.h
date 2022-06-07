//
// Created by ramizouari on 03/05/22.
//

#ifndef IMAGEPROCESSING_FILTERDIALOG_H
#define IMAGEPROCESSING_FILTERDIALOG_H
#include <QWidget>
#include <QDialog>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QStatusBar>
#include "GrayFilterInput.h"
#include "PaddingInput.h"
#include "MatrixSheet.h"

#ifdef TEST_MODE
#define private public
#define protected public
#endif

namespace GUI::options {

        class FilterDialog : public QDialog {
            Q_OBJECT
        public:
            explicit FilterDialog(QWidget *parent = nullptr);
            GrayFilterInput* createGrayFilterInput();
            PaddingInput* createPaddingInput();
            MatrixInput* createMatrixInput();
            QWidget* addWidget(const QString& title,QWidget* widget);
            QWidget* addWidget(QWidget* widget);
            void finalize();
        private:
            QFormLayout *layout;
            QVBoxLayout *mainLayout;
            QDialogButtonBox *dialogButtonBox;
            QStatusBar *statusBar;
        };

    } // options

#ifdef TEST_MODE
#undef private
#undef protected
#endif

#endif //IMAGEPROCESSING_FILTERDIALOG_H
