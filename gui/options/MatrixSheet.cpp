//
// Created by ramizouari on 05/05/22.
//

#include <set>
#include <QRegularExpression>
#include <QHeaderView>
#include "MatrixSheet.h"

namespace GUI::options {
        MatrixSheet::MatrixSheet(QWidget *parent) : MatrixInput(parent)
        {
            mainLayout = new QGridLayout(this);
            mainLayout->setSpacing(0);
            tableWidget = new QTableWidget(this);
            tableWidget->setColumnCount(3);
            tableWidget->setRowCount(3);
            for(int i=0;i<3;i++)for(int j=0;j<3;j++)
            {
                auto *item = new QTableWidgetItem();
                item->setTextAlignment(Qt::AlignCenter);
                tableWidget->setItem(i,j,item);
                item->setText((j==1 && i==1)?"-8":"1");
                validCells.emplace(i,j);
            }
            mainLayout->setContentsMargins(0,0,0,0);
            mainLayout->addWidget(tableWidget, 0, 0, 1, 4);
            addRowButton = new QPushButton("+R", this);
            addRowButton->setFixedSize(20, 20);
            addRowButton->setToolTip("Add last row");
            mainLayout->addWidget(addRowButton, 1, 0);
            addColumnButton = new QPushButton("+C", this);
            addColumnButton->setFixedSize(20, 20);
            addColumnButton->setToolTip("Add last column");
            mainLayout->addWidget(addColumnButton, 1, 1);
            removeRowButton = new QPushButton("-R", this);
            removeRowButton->setFixedSize(20, 20);
            removeRowButton->setToolTip("Remove last row");
            mainLayout->addWidget(removeRowButton, 1, 2);
            removeColumnButton = new QPushButton("-C", this);
            removeColumnButton->setFixedSize(20, 20);
            removeColumnButton->setToolTip("Remove last column");
            mainLayout->addWidget(removeColumnButton, 1, 3);
            tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            setLayout(mainLayout);
            connect(addRowButton, &QPushButton::clicked, tableWidget, [this,widget=tableWidget]()
            {
                widget->insertRow(widget->rowCount());
                emitValiditySignal();
            });
            connect(addColumnButton, &QPushButton::clicked, tableWidget, [this,widget=tableWidget]()
            {
                widget->insertColumn(widget->columnCount());
                emitValiditySignal();

            });
            connect(removeRowButton, &QPushButton::clicked, tableWidget, [this,widget=tableWidget,&valid=validCells,&invalid=invalidCells]()
            {
                for(int i=0;i<widget->columnCount();i++)
                {
                    valid.erase(std::make_pair(widget->rowCount()-1,i));
                    invalid.emplace(widget->rowCount()-1,i);
                }
                widget->removeRow(widget->rowCount()-1);
                emitValiditySignal();
            });
            connect(removeColumnButton, &QPushButton::clicked, tableWidget, [this,widget=tableWidget,&valid=validCells,&invalid=invalidCells]()
            {
                for(int i=0;i<widget->rowCount();i++)
                {
                    valid.erase(std::make_pair(i,widget->columnCount()-1));
                    invalid.emplace(i,widget->columnCount()-1);
                }
                widget->removeColumn(widget->columnCount()-1);
                emitValiditySignal();
            });
            connect(tableWidget, &QTableWidget::itemChanged, this, [this](QTableWidgetItem *item)
            {
                auto index=this->tableWidget->indexFromItem(item);
                auto col=index.column(),row=index.row();
                if (item->text().isEmpty())
                {
                    item->setBackground(Qt::yellow);
                    validCells.erase(std::make_pair(row,col));
                    invalidCells.erase(std::make_pair(row,col));
                }
                else {
                    QRegularExpression numberRegex(R"(^[+-]?[0-9]+(\.[0-9]*)?$)");
                    if (!numberRegex.match(item->text()).hasMatch()) {
                        item->setBackground(Qt::red);
                        validCells.erase(std::make_pair(row,col));
                        invalidCells.emplace(row,col);
                    } else {
                        validCells.emplace(row,col);
                        invalidCells.erase(std::make_pair(row,col));
                        item->setBackground(Qt::white);
                    }
                }
                emitValiditySignal();
            });
        }

    image::Matrix MatrixSheet::getConvolutionMatrix() {
            auto rows=tableWidget->rowCount(),cols=tableWidget->columnCount();
            image::Matrix  M(0,linalg::m_shape{rows,cols});
        for(int i=0;i<rows;i++) for(int j=0;j<cols;j++)
            M[i][j]=tableWidget->item(i,j)->text().toDouble();
        return M;
    }

    void MatrixSheet::emitValiditySignal() {
        auto totalDimension=tableWidget->rowCount()*tableWidget->columnCount();
        if(validCells.size()==totalDimension)
                emit validityUpdated(ValidityType::VALID);
        else if(!invalidCells.empty())
                emit validityUpdated(ValidityType::INVALID);
        else emit validityUpdated(ValidityType::MISSING);
    }

} // options