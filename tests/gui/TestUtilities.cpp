//
// Created by ramizouari on 07/06/22.
//
#include "TestUtilities.h"

QAction *Test::findActionOrThrow(QMenu *menu, const QString &actionName)
{
    for(auto action:menu->actions())
        if(action->text()==actionName)
            return action;
    throw std::runtime_error("Requested Action " + actionName.toStdString() + " Not found");
}

QAction *Test::findAction(QMenu *menu, const QString &actionName)
{
    for(auto action:menu->actions())
        if(action->text()==actionName)
            return action;
    return nullptr;
}

QString Test::actionNotFound(const QString &name)
{
    return "Requested action '" + name + "' not found";
}

void Test::FileDialog::accept()
{
    QFileDialog::accept();
    close();
}
