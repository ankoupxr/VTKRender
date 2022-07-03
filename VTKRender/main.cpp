#include "VTKRender.h"
#include <QtWidgets/QApplication>
#include <vtkAutoInit.h>
#include <vtkObject.h>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2);

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    vtkObject::GlobalWarningDisplayOff();
    VTKRender w;
    w.show();
    return app.exec();
}
