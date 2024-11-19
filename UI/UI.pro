QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Admin.cpp \
    ../BankAccount.cpp \
    ../LoanAccount.cpp \
    ../RegularAccount.cpp \
    ../SavingAccount.cpp \
    ../TimeUtils.cpp \
    ../Transaction.cpp \
    ../User.cpp \
    ../main.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../Account.h \
    ../Admin.h \
    ../BankAccount.h \
    ../LoanAccount.h \
    ../RegularAccount.h \
    ../SavingAccount.h \
    ../SortedLinkedList.h \
    ../TimeUtils.h \
    ../Transaction.h \
    ../User.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
