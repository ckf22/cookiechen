QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    class_config.cpp \
    class_format_in-out.cpp \
    class_handler.cpp \
    class_log.cpp \
    class_recipe.cpp \
    class_recipelist.cpp \
    convert.cpp \
    main.cpp \
    mainwindow.cpp \
    recipeedit.cpp \
    save_check_dialog.cpp \
    searchdialog.cpp \
    shell_command.cpp

HEADERS += \
    class_format_in-out.h \
    class_handler.h \
    class_log.h \
    class_recipe.h \
    class_recipelist.h \
    mainwindow.h \
    recipeedit.h \
    save_check_dialog.h \
    searchdialog.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS +=
