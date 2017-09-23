# =================================================
# * This file is part of the TTK Downloader project
# * Copyright (c) 2016 - 2017 Greedysky Studio
# * All rights reserved!
# * Redistribution and use of the source code or any derivative
# * works are strictly forbiden.
# =================================================

INCLUDEPATH += $$PWD

!contains(CONFIG, DOWNLOAD_NO_MSVC_LINK_NEED){
HEADERS  += \
    $$PWD/downloadbackgroundskindialog.h \
    $$PWD/downloadfuntionanimationwidget.h \
    $$PWD/downloadbackgroundlistwidget.h \
    $$PWD/downloadbackgroundpopwidget.h \
    $$PWD/downloadbackgroundremotewidget.h \
    $$PWD/downloadsystemtraymenu.h \
    $$PWD/downloadwindowextras.h \
    $$PWD/downloadnewfiledialog.h\
    $$PWD/downloadlistitemwidget.h \
    $$PWD/downloadlistwidgets.h \
    $$PWD/downloadfunctionlistwidget.h

}

contains(CONFIG, DOWNLOAD_BUILD_LIB){
SOURCES += \
    $$PWD/downloadbackgroundskindialog.cpp \
    $$PWD/downloadfuntionanimationwidget.cpp \
    $$PWD/downloadbackgroundpopwidget.cpp \
    $$PWD/downloadbackgroundlistwidget.cpp \
    $$PWD/downloadsystemtraymenu.cpp \
    $$PWD/downloadbackgroundremotewidget.cpp \
    $$PWD/downloadwindowextras.cpp \
    $$PWD/downloadnewfiledialog.cpp\
    $$PWD/downloadlistitemwidget.cpp \
    $$PWD/downloadlistwidgets.cpp \
    $$PWD/downloadfunctionlistwidget.cpp

}