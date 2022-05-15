/*
3) Записи о занятиях: номер записи, название предмета, тип занятия
(перечисление enum), год выпуска.: лекция, практика, лабораторная, экзамен), аудитория.
*/

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
