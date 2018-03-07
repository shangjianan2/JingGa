QT += charts qml quick

HEADERS += \
    datasource.h

SOURCES += \
    main.cpp \
    datasource.cpp

RESOURCES += \
    resources.qrc

DISTFILES += \
    qml/qmloscilloscope/* \
    timg.jpg

target.path = $$[QT_INSTALL_EXAMPLES]/charts/qmloscilloscope
INSTALLS += target
