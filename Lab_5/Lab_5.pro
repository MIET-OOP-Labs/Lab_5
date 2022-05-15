QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abstractReader.cpp \
    csv_reader.cpp \
    csv_writer.cpp \
    json_reader.cpp \
    lesson.cpp \
    lessonOnline.cpp \
    lessonOpen.cpp \
    lessonsHandler.cpp \
    main.cpp \
    mainwindow.cpp \
    myTextBrowser.cpp \
    searchHandler.cpp

HEADERS += \
    abstractReader.h \
    csv_reader.h \
    csv_writer.h \
    json.hpp \
    json_reader.h \
    lesson.h \
    lessonOnline.h \
    lessonOpen.h \
    lessonTypedefs.h \
    lessonsHandler.h \
    mainwindow.h \
    myTextBrowser.h \
    searchHandler.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
