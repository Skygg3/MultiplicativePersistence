TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../mpir-3.0.0/dll/x64/release/ -lmpir
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../mpir-3.0.0/dll/x64/debug/ -lmpir

INCLUDEPATH += $$PWD/../mpir-3.0.0/dll/x64/Release
DEPENDPATH += $$PWD/../mpir-3.0.0/dll/x64/Release

DISTFILES += \
    README.md
