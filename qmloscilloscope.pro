QT += charts qml quick

HEADERS += \
    datasource.h \
    udpreceiver.h

SOURCES += \
    main.cpp \
    datasource.cpp \
    udpreceiver.cpp

RESOURCES += \
    resources.qrc

DISTFILES += \
    qml/qmloscilloscope/* \
    timg.jpg

target.path = $$[QT_INSTALL_EXAMPLES]/charts/qmloscilloscope
INSTALLS += target
