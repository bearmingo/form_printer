/********************************************************************************
** Form generated from reading UI file 'form_printer.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_PRINTER_H
#define UI_FORM_PRINTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_form_printerClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *form_printerClass)
    {
        if (form_printerClass->objectName().isEmpty())
            form_printerClass->setObjectName(QStringLiteral("form_printerClass"));
        form_printerClass->resize(600, 400);
        centralWidget = new QWidget(form_printerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        horizontalLayout->addWidget(graphicsView);

        form_printerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(form_printerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 26));
        form_printerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(form_printerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        form_printerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(form_printerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        form_printerClass->setStatusBar(statusBar);

        retranslateUi(form_printerClass);

        QMetaObject::connectSlotsByName(form_printerClass);
    } // setupUi

    void retranslateUi(QMainWindow *form_printerClass)
    {
        form_printerClass->setWindowTitle(QApplication::translate("form_printerClass", "form_printer", 0));
    } // retranslateUi

};

namespace Ui {
    class form_printerClass: public Ui_form_printerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_PRINTER_H
