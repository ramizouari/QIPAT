//
// Created by ramizouari on 07/06/22.
//

#ifndef IMAGEPROCESSING_TESTUTILITIES_H
#define IMAGEPROCESSING_TESTUTILITIES_H
#include <QAction>
#include <QMenu>
#include <QFileDialog>

namespace Test
{
    QAction* findActionOrThrow(QMenu *menu,const QString& actionName);

    QAction* findAction(QMenu *menu,const QString& actionName);

    QString actionNotFound(const QString &name);

    class FileDialog : public QFileDialog
    {
    public:
        using QFileDialog::QFileDialog;
        void accept() override;
    };

}

#endif //IMAGEPROCESSING_TESTUTILITIES_H
