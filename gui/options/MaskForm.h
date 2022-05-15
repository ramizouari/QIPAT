//
// Created by ramizouari on 14/05/22.
//

#ifndef IMAGEPROCESSING_MASKFORM_H
#define IMAGEPROCESSING_MASKFORM_H

#include <QWidget>

namespace GUI::options {

        class MaskForm :public QWidget{
            Q_OBJECT
        protected:
            int width,height;
        public:
            explicit MaskForm(int width,int height,QWidget *parent = nullptr);
            ~MaskForm() override = default;
            virtual std::vector<std::vector<bool>> generateMask()=0;
        };

    } // options

#endif //IMAGEPROCESSING_MASKFORM_H
