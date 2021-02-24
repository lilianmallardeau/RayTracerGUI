QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    src/environment/Camera.cpp \
    src/environment/Light.cpp \
    src/environment/Ray.cpp \
    src/environment/Scene.cpp \
    src/objects/Cube.cpp \
    src/objects/Object.cpp \
    src/objects/Plane.cpp \
    src/objects/Quad.cpp \
    src/objects/Sphere.cpp \
    src/ui/CommandLineInterface.cpp \
    src/utils/Color.cpp \
    src/utils/Material.cpp \
    src/utils/MathTools.cpp \
    src/utils/Vector3D.cpp

HEADERS += \
    mainwindow.h \
    src/environment/Camera.h \
    src/environment/Light.h \
    src/environment/Ray.h \
    src/environment/Scene.h \
    src/exceptions/exceptions.h \
    src/include/environment.h \
    src/include/objects.h \
    src/include/utils.h \
    src/objects/Cube.h \
    src/objects/Object.h \
    src/objects/Plane.h \
    src/objects/Quad.h \
    src/objects/Sphere.h \
    src/ui/CommandLineInterface.h \
    src/utils/Color.h \
    src/utils/Material.h \
    src/utils/MathTools.h \
    src/utils/Vector3D.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix|win32: LIBS += -lpng
