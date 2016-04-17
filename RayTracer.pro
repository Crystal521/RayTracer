#-------------------------------------------------
#
# Project created by QtCreator 2016-02-24T15:31:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RayTracer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Utilities/Matrix.cpp \
    Utilities/Normal.cpp \
    Utilities/Point2D.cpp \
    Utilities/Point3D.cpp \
    Utilities/Ray.cpp \
    Utilities/RGBColor.cpp \
    Utilities/ShadeRec.cpp \
    Utilities/Vector3D.cpp \
    GeneratedFiles/Debug/moc_mainwindow.cpp \
    Tracers/SingleShpere.cpp \
    Tracers/Tracer.cpp \
    GeometricObjects/Primitives/Plane.cpp \
    GeometricObjects/Primitives/Sphere.cpp \
    GeometricObjects/GeometricObject.cpp \
    World/ViewPlane.cpp \
    World/World.cpp \
    BRDFs/BRDF.cpp \
    BRDFs/FresnelReflector.cpp \
    BRDFs/GlossySpecular.cpp \
    BRDFs/Lambertian.cpp \
    BRDFs/PerfectSpecular.cpp \
    BTDFs/BTDF.cpp \
    BTDFs/FresnelTransmitter.cpp \
    BTDFs/PerfectTransmitter.cpp \
    Cameras/Camera.cpp \
    Cameras/Pinhole.cpp \
    GeometricObjects/CompoundObjects/Compound.cpp \
    GeometricObjects/CompoundObjects/Grid.cpp \
    GeometricObjects/Primitives/Rectangle.cpp \
    GeometricObjects/Triangle/FlatMeshTriangle.cpp \
    GeometricObjects/Triangle/MeshTriangle.cpp \
    GeometricObjects/Triangle/SmoothMeshTriangle.cpp \
    GeometricObjects/Triangle/SmoothTriangle.cpp \
    GeometricObjects/Triangle/Triangle.cpp \
    GeometricObjects/BBox.cpp \
    GeometricObjects/Instance.cpp \
    Lights/Ambient.cpp \
    Lights/AreaLight.cpp \
    Lights/Directional.cpp \
    Lights/Light.cpp \
    Lights/PointLight.cpp \
    Materials/Dielectric.cpp \
    Materials/Material.cpp \
    Materials/Matte.cpp \
    Materials/Phong.cpp \
    Materials/Reflective.cpp \
    Materials/Transparent.cpp \
    Tracers/RayCast.cpp \
    Tracers/Whitted.cpp \
    Utilities/Mesh.cpp \
    Utilities/ply.cpp \
    World/WorldBuild.cpp \

HEADERS  += mainwindow.h \
    GeometricObjects/Primitives/Plane.h \
    GeometricObjects/Primitives/Sphere.h \
    GeometricObjects/GeometricObject.h \
    Utilities/Constants.h \
    Utilities/Matrix.h \
    Utilities/Normal.h \
    Utilities/Point2D.h \
    Utilities/Point3D.h \
    Utilities/Ray.h \
    Utilities/RGBColor.h \
    Utilities/ShadeRec.h \
    Utilities/Vector3D.h \
    GeneratedFiles/ui_mainwindow.h \
    Tracers/SingleSphere.h \
    Tracers/Tracer.h \
    GeometricObjects/Primitives/Plane.h \
    GeometricObjects/Primitives/Sphere.h \
    GeometricObjects/GeometricObject.h \
    World/ViewPlane.h \
    World/World.h \
    BRDFs/BRDF.h \
    BRDFs/FresnelReflector.h \
    BRDFs/GlossySpecular.h \
    BRDFs/Lambertian.h \
    BRDFs/PerfectSpecular.h \
    BTDFs/BTDF.h \
    BTDFs/FresnelTransmitter.h \
    BTDFs/PerfectTransmitter.h \
    Cameras/Camera.h \
    Cameras/Pinhole.h \
    GeometricObjects/CompoundObjects/Compound.h \
    GeometricObjects/CompoundObjects/Grid.h \
    GeometricObjects/Primitives/Rectangle.h \
    GeometricObjects/Triangle/FlatMeshTriangle.h \
    GeometricObjects/Triangle/MeshTriangle.h \
    GeometricObjects/Triangle/SmoothMeshTriangle.h \
    GeometricObjects/Triangle/SmoothTriangle.h \
    GeometricObjects/Triangle/Triangle.h \
    GeometricObjects/BBox.h \
    GeometricObjects/Instance.h \
    Lights/Ambient.h \
    Lights/AreaLight.h \
    Lights/Directional.h \
    Lights/Light.h \
    Lights/PointLight.h \
    Materials/Dielectric.h \
    Materials/Material.h \
    Materials/Matte.h \
    Materials/Phong.h \
    Materials/Reflective.h \
    Materials/Transparent.h \
    Tracers/RayCast.h \
    Tracers/Whitted.h \
    Utilities/Maths.h \
    Utilities/Mesh.h \
    Utilities/ply.h

FORMS    += mainwindow.ui

INCLUDEPATH += World Utilities BRDFs BTDFs Cameras Lights Materials GeometricObjects GeometricObjects/Primitives GeometricObjects/Triangle GeometricObjects/CompoundObjects Tracers GeneratedFiles
