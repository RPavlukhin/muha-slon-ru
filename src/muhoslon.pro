TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11
SOURCES += main.cpp \
    wordrouter.cpp \
    branch.cpp

//QMAKE_LFLAGS        = --enable-stdcall-fixup -Wl,-enable-auto-import -Wl,-enable-runtime-pseudo-reloc
//QMAKE_LFLAGS        = --static, -enable-stdcall-fixup -Wl,-enable-auto-import -Wl,-enable-runtime-pseudo-reloc

QMAKE_LFLAGS = -static-libgcc -static --enable-stdcall-fixup -Wl,-enable-auto-import -Wl,-enable-runtime-pseudo-reloc
DEFINES += QT_STATIC_BUILD

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    wordrouter.h \
    branch.h
