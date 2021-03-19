cmake_minimum_required(VERSION 3.5)

project(lanceur-de-rayons LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

include_directories(src/environment)
include_directories(src/include)
include_directories(src/objects)
include_directories(src/ui)
include_directories(src/utils)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        src/environment/Camera.cpp
        src/environment/Camera.h
        src/environment/Ray.cpp
        src/environment/Ray.h
        src/environment/Scene.cpp
        src/environment/Scene.h
        src/include/environment.h
        src/include/objects.h
        src/include/utils.h
        src/objects/Object.cpp
        src/objects/Object.h
        src/objects/Quad.cpp
        src/objects/Quad.h
        src/objects/Sphere.cpp
        src/objects/Sphere.h
        src/ui/CommandLineInterface.cpp
        src/ui/CommandLineInterface.h
        src/utils/Color.cpp
        src/utils/Color.h
        src/utils/Material.cpp
        src/utils/Material.h
        src/utils/Vector3D.cpp
        src/utils/Vector3D.h
        src/environment/Light.cpp
        src/environment/Light.h
        src/objects/Plane.cpp
        src/objects/Plane.h
        src/exceptions/exceptions.h
        src/utils/MathTools.cpp
        src/utils/MathTools.h
        src/objects/Cube.cpp
        src/objects/Cube.h
        src/utils/Serializable.cpp
        src/utils/Serializable.h
        widgets/floatedit.cpp
        widgets/floatedit.h
        widgets/vectorentrywidget.cpp
        widgets/vectorentrywidget.h
        widgets/propertieseditorwidget.cpp
        widgets/propertieseditorwidget.h
        widgets/camerapropertieswidget.cpp
        widgets/camerapropertieswidget.h
        widgets/lightpropertieswidget.cpp
        widgets/lightpropertieswidget.h
        widgets/objects/spherepropertieswidget.cpp
        widgets/objects/spherepropertieswidget.h
        widgets/objects/planepropertieswidget.cpp
        widgets/objects/planepropertieswidget.h
        widgets/objects/quadpropertieswidget.cpp
        widgets/objects/quadpropertieswidget.h
        widgets/objects/cubepropertieswidget.cpp
        widgets/objects/cubepropertieswidget.h
        widgets/widgets.h
        qtCustomType/qsceneobject.h
        qtCustomType/qsceneobject.cpp
        resources.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(lanceur-de-rayons
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(lanceur-de-rayons SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(lanceur-de-rayons
            ${PROJECT_SOURCES}
        )
    endif()
endif()


# PNG++ library
find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

# JSON library
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(src/lib/json)


target_link_libraries(lanceur-de-rayons PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${PNG_LIBRARY} nlohmann_json::nlohmann_json)
