QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    play.cpp \
    poker.cpp

HEADERS += \
    dialog.h \
    mainwindow.h \
    play.h \
    poker.h

FORMS += \
    dialog.ui \
    mainwindow.ui \
    play.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    PokerCardsPhoto/10C.jpg \
    PokerCardsPhoto/10D.jpg \
    PokerCardsPhoto/10H.jpg \
    PokerCardsPhoto/10S.jpg \
    PokerCardsPhoto/2C.jpg \
    PokerCardsPhoto/2D.jpg \
    PokerCardsPhoto/2H.jpg \
    PokerCardsPhoto/2S.jpg \
    PokerCardsPhoto/3C.jpg \
    PokerCardsPhoto/3D.jpg \
    PokerCardsPhoto/3H.jpg \
    PokerCardsPhoto/3S.jpg \
    PokerCardsPhoto/4C.jpg \
    PokerCardsPhoto/4D.jpg \
    PokerCardsPhoto/4H.jpg \
    PokerCardsPhoto/4S.jpg \
    PokerCardsPhoto/5C.jpg \
    PokerCardsPhoto/5D.jpg \
    PokerCardsPhoto/5H.jpg \
    PokerCardsPhoto/5S.jpg \
    PokerCardsPhoto/6C.jpg \
    PokerCardsPhoto/6D.jpg \
    PokerCardsPhoto/6H.jpg \
    PokerCardsPhoto/6S.jpg \
    PokerCardsPhoto/7C.jpg \
    PokerCardsPhoto/7D.jpg \
    PokerCardsPhoto/7H.jpg \
    PokerCardsPhoto/7S.jpg \
    PokerCardsPhoto/8C.jpg \
    PokerCardsPhoto/8D.jpg \
    PokerCardsPhoto/8H.jpg \
    PokerCardsPhoto/8S.jpg \
    PokerCardsPhoto/9C.jpg \
    PokerCardsPhoto/9D.jpg \
    PokerCardsPhoto/9H.jpg \
    PokerCardsPhoto/9S.jpg \
    PokerCardsPhoto/AC.jpg \
    PokerCardsPhoto/AD.jpg \
    PokerCardsPhoto/AH.jpg \
    PokerCardsPhoto/AS.jpg \
    PokerCardsPhoto/BIGJOKER.jpg \
    PokerCardsPhoto/JC.jpg \
    PokerCardsPhoto/JD.jpg \
    PokerCardsPhoto/JH.jpg \
    PokerCardsPhoto/JS.jpg \
    PokerCardsPhoto/KC.jpg \
    PokerCardsPhoto/KD.jpg \
    PokerCardsPhoto/KH.jpg \
    PokerCardsPhoto/KS.jpg \
    PokerCardsPhoto/QC.jpg \
    PokerCardsPhoto/QD.jpg \
    PokerCardsPhoto/QH.jpg \
    PokerCardsPhoto/QS.jpg \
    PokerCardsPhoto/SMALLJOKER.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_10.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_11.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_12.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_13.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_14.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_15.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_16.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_17.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_18.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_19.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_2.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_20.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_21.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_22.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_23.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_24.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_25.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_26.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_27.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_28.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_29.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_3.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_30.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_31.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_32.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_33.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_34.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_35.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_36.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_37.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_38.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_39.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_4.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_40.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_41.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_42.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_43.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_44.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_45.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_46.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_47.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_48.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_49.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_5.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_50.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_51.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_52.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_53.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_54.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_6.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_7.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_8.jpg \
    PokerCardsPhoto/veryhuo.com_pkp_9.jpg

RESOURCES += \
    PokerCardsPhoto.qrc

QT += multimedia
