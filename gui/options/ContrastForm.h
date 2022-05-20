//
// Created by ramizouari on 03/05/22.
//

#ifndef IMAGEPROCESSING_CONTRASTFORM_H
#define IMAGEPROCESSING_CONTRASTFORM_H

#include <QWidget>
#include <QSpinBox>
#include "image/Image.h"

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

    class SplineContrastForm :public QWidget{
    Q_OBJECT
    public:
        explicit SplineContrastForm(QWidget *parent = nullptr);
        ~SplineContrastForm() override = default;
    signals:
        void valueUpdated(int,int,int,image::Real);
        void requestPointAdd(int);
        void requestPointAdd();
        void requestPointRemove(int);
    private:
        std::vector<std::pair<QSpinBox*,QSpinBox*>> spinBoxes;
        std::pair<QSpinBox*,QSpinBox*> lastSpinBox;
        QPushButton *addPointButton;
    };

    class SplineContrastFormRow :public QWidget{
    Q_OBJECT
    public:
        enum class Type{
            FIRST,
            MIDDLE,
            LAST
        };
        explicit SplineContrastFormRow(Type type,QWidget *parent = nullptr);
        ~SplineContrastFormRow() override = default;
    signals:
        void valueUpdated(int,int,image::Real);
        void requestRemove();

    private:
        QSpinBox *xCoordinate;
        QSpinBox *yCoordinate;
        QDoubleSpinBox *yDerivative;
        QPushButton *removeButton;
    };
    } // options

#endif //IMAGEPROCESSING_CONTRASTFORM_H
