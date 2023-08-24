QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cpea.cpp \
    cpeabox.cpp \
    cplant.cpp \
    cplantbox.cpp \
    cplantpeashooter.cpp \
    cplantsunflower.cpp \
    cplantvszombieapp.cpp \
    cplantwallnut.cpp \
    csun.cpp \
    csunbox.cpp \
    czombie.cpp \
    czombiebasic.cpp \
    czombiebox.cpp \
    main.cpp \
    widget.cpp \
    widget1.cpp

HEADERS += \
    GameConfig.h \
    cpea.h \
    cpeabox.h \
    cplant.h \
    cplantbox.h \
    cplantpeashooter.h \
    cplantsunflower.h \
    cplantvszombieapp.h \
    cplantwallnut.h \
    csun.h \
    csunbox.h \
    czombie.h \
    czombiebasic.h \
    czombiebox.h \
    widget.h \
    widget1.h

FORMS += \
    widget.ui \
    widget1.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    res/卡片/卡片选择/卡片选择区.bmp \
    res/卡片/卡片选择/卡片选择区.bmp
