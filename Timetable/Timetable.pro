#-------------------------------------------------
#
# Project created by QtCreator 2013-06-06T23:11:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Timetable
TEMPLATE = app


SOURCES += main.cpp\
        geracaogrades.cpp \
    Turma.cpp \
    Professor.cpp \
    operacoes.cpp \
    Horario.cpp \
    Disciplina.cpp \
    Ant.cpp \
    principal.cpp \
    table.cpp \
    addturma.cpp \
    constantes.cpp \
    saida.cpp \
    creditosprofessores.cpp \
    getparemetros.cpp \
    compararesultado.cpp

HEADERS  += geracaogrades.h \
    Turma.h \
    Professor.h \
    operacoes.h \
    Horario.h \
    Disciplina.h \
    Ant.h \
    principal.h \
    table.h \
    addturma.h \
    constantes.h \
    saida.h \
    creditosprofessores.h \
    getparemetros.h \
    compararesultado.h

FORMS    += geracaogrades.ui \
    addturma.ui \
    saida.ui \
    creditosprofessores.ui \
    getparemetros.ui \
    compararesultado.ui
