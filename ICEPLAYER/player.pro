#-------------------------------------------------
#
# Project created by QtCreator 2016-02-10T10:03:08
#
#-------------------------------------------------

QT       += core gui #network
QT += network
QT += multimedia
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = palyer
TEMPLATE = app


SOURCES += main.cpp\
    aboutform.cpp \
    icelabel.cpp \
    icelrc.cpp \
    iceplayer.cpp \
    icevolbutton.cpp \
    lyric.cpp \
    network.cpp \
    nofocusdelegate.cpp \
    single_application.cpp \
    iceButton.cpp \
    mini.cpp \
    movablewindow.cpp

HEADERS  += \
    aboutform.h \
    icelabel.h \
    icelrc.h \
    iceplayer.h \
    icevolbutton.h \
    lyric.h \
    network.h \
    nofocusdelegate.h \
    resource.h \
    single_application.h \
    iceButton.h \
    mini.h \
    songinfo.h \
    movablewindow.h

RESOURCES += \
    resources.qrc

DISTFILES += \
    Resources/default_album.jpg \
    Resources/about.png \
    Resources/background.png \
    Resources/full.png \
    Resources/logo-16.png \
    Resources/logo-32.png \
    Resources/logo-48.png \
    Resources/lrc_background.png \
    Resources/lyric.png \
    Resources/mini.png \
    Resources/mini底部窗口（2）.png \
    Resources/上一曲.png \
    Resources/上一曲2.png \
    Resources/下一曲.png \
    Resources/下一曲2.png \
    Resources/关闭按钮.png \
    Resources/关闭按钮2.png \
    Resources/前进按钮mini.png \
    Resources/左上角logo按钮.png \
    Resources/左上角logo按钮2.png \
    Resources/播放按钮mini.png \
    Resources/播放按钮-主界面.png \
    Resources/播放按钮-主界面2.png \
    Resources/播放模式.png \
    Resources/播放模式2.png \
    Resources/暂停按钮mini.png \
    Resources/暂停按钮-主界面.png \
    Resources/暂停按钮-主界面2.png \
    Resources/歌词按钮.png \
    Resources/歌词按钮2.png \
    Resources/添加歌曲.png \
    Resources/添加歌曲2.png \
    Resources/缩小按钮.png \
    Resources/缩小按钮2.png \
    Resources/迷你模式按钮.png \
    Resources/迷你模式按钮2.png \
    Resources/音量调节.png \
    Resources/音量调节2.png
