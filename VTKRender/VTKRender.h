#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VTKRender.h"

class VTKRender : public QMainWindow
{
    Q_OBJECT

public:
    VTKRender(QWidget *parent = nullptr);
    ~VTKRender();

private:
    Ui::VTKRenderClass ui;
};
