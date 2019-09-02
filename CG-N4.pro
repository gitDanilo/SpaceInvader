TEMPLATE = app
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lgdi32
LIBS += -lopengl32
LIBS += -lglu32
LIBS += -lwinmm

SOURCES += main.cpp \
    font.cpp \
    fps.cpp \
    scene.cpp \
    spaceship.cpp \
    glwindow.cpp \
    bullet.cpp \
    modelobj.cpp \
    globject.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    font.h \
    fps.h \
    scene.h \
    globject.h \
    spaceship.h \
    glwindow.h \
    bullet.h \
    modelobj.h

