/********************************************************************************
** Form generated from reading UI file 'VTKRender.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VTKRENDER_H
#define UI_VTKRENDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VTKRenderClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *VTKRenderClass)
    {
        if (VTKRenderClass->objectName().isEmpty())
            VTKRenderClass->setObjectName(QString::fromUtf8("VTKRenderClass"));
        VTKRenderClass->resize(600, 400);
        menuBar = new QMenuBar(VTKRenderClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        VTKRenderClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(VTKRenderClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        VTKRenderClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(VTKRenderClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        VTKRenderClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(VTKRenderClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        VTKRenderClass->setStatusBar(statusBar);

        retranslateUi(VTKRenderClass);

        QMetaObject::connectSlotsByName(VTKRenderClass);
    } // setupUi

    void retranslateUi(QMainWindow *VTKRenderClass)
    {
        VTKRenderClass->setWindowTitle(QCoreApplication::translate("VTKRenderClass", "VTKRender", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VTKRenderClass: public Ui_VTKRenderClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VTKRENDER_H
