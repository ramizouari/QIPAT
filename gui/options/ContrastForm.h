//
// Created by ramizouari on 03/05/22.
//

#ifndef IMAGEPROCESSING_CONTRASTFORM_H
#define IMAGEPROCESSING_CONTRASTFORM_H

#include <QWidget>
#include <QSpinBox>

namespace GUI::options {

        class ContrastForm :public QWidget{
            Q_OBJECT
        public:
            explicit ContrastForm(QWidget *parent = nullptr);
            ~ContrastForm() override = default;
            signals:
            void valueUpdated(int,int,int);
            void requestPointAdd(int);
            void requestPointAdd();
            void requestPointRemove(int);
        private:
            std::vector<std::pair<QSpinBox*,QSpinBox*>> spinBoxes;
            std::pair<QSpinBox*,QSpinBox*> lastSpinBox;
            QPushButton *addPointButton;
        };

        class ContrastFormRow :public QWidget{
            Q_OBJECT
        public:
            enum class Type{
                FIRST,
                MIDDLE,
                LAST
            };
            explicit ContrastFormRow(Type type,QWidget *parent = nullptr);
            ~ContrastFormRow() override = default;
        signals:
            void valueUpdated(int,int);
            void requestRemove();

        private:
            QSpinBox *xCoordinate;
            QSpinBox *yCoordinate;
            QPushButton *removeButton;
        };
    } // options

#endif //IMAGEPROCESSING_CONTRASTFORM_H
