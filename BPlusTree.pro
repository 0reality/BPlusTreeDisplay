QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# SOURCES += \
#     BPlusTree.cpp \
#     arrowoverlay.cpp \
#     isConfirm.cpp \
#     main.cpp \
#     mainwindow.cpp

# HEADERS += \
#     BPlusTree.h \
#     arrowoverlay.h \
#     isConfirm.h \
#     mainwindow.h

# FORMS += \
#     isConfirm.ui \
#     mainwindow.ui

INCLUDE_PATH = $$PWD/head
SOURCES_PATH = $$PWD/src
FORMS_PATH = $$PWD/ui

HEADERS += $$files($$INCLUDE_PATH/*.h)
SOURCES += $$files($$SOURCES_PATH/*.cpp)
FORMS += $$files($$FORMS_PATH/*.ui)


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resourse.qrc
