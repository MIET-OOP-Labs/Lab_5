#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mylessonsHandler = new lessonsHandler(myLessons, myLessonsOnline, myLessonsOpen);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::printLessonsRecords(vector<lesson> lessonRecords) {
    QString outStr;
    outStr.sprintf("%-3s %6s %15s %10s %5s","ID", "Num", "Subject", "Type", "Classroom");
    ui->textOut->append(outStr);
    for (lesson currLesson : lessonRecords) {            //function for printing all records in recordStruct vector
        QString outStr;
        lessonStruct lessonParams = currLesson.getLessonParams();
        outStr.sprintf("%-3d %6d %15s %10s %5d\n", lessonParams.id, lessonParams.num, lessonParams.subjectName.c_str(), getLessonStr(lessonParams.lessonType).c_str(), lessonParams.classroom);
        ui->textOut->append(outStr);
    }
    ui->textOut->append("\n");
}

void MainWindow::printLessonsRecords(vector<lessonOpen> lessonRecords) {
    QString outStr;
    outStr.sprintf("%-3s %6s %15s %10s %10s %3d %10s","ID", "Num", "Subject", "Type", "Link", "Students num", "Teacher");
    ui->textOut->append(outStr);
    for (lessonOpen currLesson : lessonRecords) {            //function for printing all records in recordStruct vector
        QString outStr;
        openLessonStruct lessonParams = currLesson.getLessonParams();
        outStr.sprintf("%-3d %6d %15s %10s %10s %3d %10s\n", lessonParams.id, lessonParams.num, lessonParams.subjectName.c_str(), getLessonStr(lessonParams.lessonType).c_str(), lessonParams.link.c_str(), lessonParams.studentsNum, lessonParams.teacherName.c_str());
        ui->textOut->append(outStr);
    }
    ui->textOut->append("\n");
}


void MainWindow::printLessonsRecords(vector<lessonOnline> lessonRecords) {
    QString outStr;
    outStr.sprintf("%-3s %6s %15s %10s %5s %10s","ID", "Num", "Subject", "Type", "Platform", "Link");
    ui->textOut->append(outStr);
    for (lessonOnline currLesson : lessonRecords) {            //function for printing all records in recordStruct vector
        QString outStr;
        onlineLessonStruct lessonParams = currLesson.getLessonParams();
        outStr.sprintf("%-3d %6d %15s %10s %5s %10s\n", lessonParams.id, lessonParams.num, lessonParams.subjectName.c_str(), getLessonStr(lessonParams.lessonType).c_str(), lessonParams.platform, lessonParams.link.c_str());
        ui->textOut->append(outStr);
    }
    ui->textOut->append("\n");
}

void MainWindow::findLesson() {
    QString logStr = "You entered: ";
    QString userRequest = ui->editSearch->text();
    ui->textOut->append(logStr.append(userRequest) + "\n");
    lessonStruct filter;
    char subjectName_c[16];
    char lessonType_c[16];
    char *userRequest_c = new char[userRequest.length() + 1];
    strcpy(userRequest_c, userRequest.toStdString().c_str());
    sscanf(userRequest_c, "%[^;];%[^;];%d", subjectName_c, lessonType_c, &filter.classroom);
    delete[] userRequest_c;
    filter.lessonType = getLessonEnum(lessonType_c);
    filter.subjectName = subjectName_c;

    printLessonsRecords(mylessonsHandler->getFilteredCmnRecords(filter));
}

void MainWindow::on_chooseFile_clicked() {
    string myFilePath = QFileDialog::getOpenFileName(this, "Open a .csv file", QDir::currentPath()).toStdString();
    if (!mylessonsHandler->readNewCmnLessonsArrFromFile(myFilePath)){
        QMessageBox::information(this,"Failed to open file ",QString::fromStdString(myFilePath));
        return;
    }
    QMessageBox::information(this,"Opened file ", QString::fromStdString(myFilePath));

    printLessonsRecords(myLessons);
}

void MainWindow::on_choose_JSON_clicked(){
    string my_JSON_Path = QFileDialog::getOpenFileName(this, "Open a JSON file", QDir::currentPath()).toStdString();
    mylessonsHandler->readNewCmnLessonsArrFrom_JSON(my_JSON_Path);
    printLessonsRecords(myLessons);
}

void MainWindow::addLesson() {
    lessonCategoryEnum lessonCat = static_cast<lessonCategoryEnum>(ui->comboCat->currentIndex() + 1);


    if (((myLessons.size() == maxLessonsNum) && (lessonCat == Lesson)) ||
        ((myLessonsOnline.size() == maxLessonsNum) && (lessonCat == Online)) ||
        ((myLessonsOpen.size() == maxLessonsNum) && (lessonCat == Open))) {
        QMessageBox::information(this,"Failed to add more subjects ", "Sorry, but students can't cope with so many subjects, take pity on them");
        return;
    }

    switch (lessonCat) {
    case Lesson: {
            lessonStruct newCmnLessonData;
            newCmnLessonData.subjectName = ui->lineSubject->text().toStdString();
            newCmnLessonData.lessonType = static_cast<lessonTypesEnum>(ui->comboType->currentIndex() + 1);
            newCmnLessonData.classroom = ui->lineClassroom->text().toInt();
            newCmnLessonData.num = myLessons[myLessons.size() - 1].getLessonParams().num + 1;
            newCmnLessonData.id = mylessonsHandler->getUniqRandID(Lesson);


            lesson newCmnLesson;
            newCmnLesson.setLessonParams(newCmnLessonData);
            myLessons.push_back(newCmnLesson);

            if(!mylessonsHandler->writeNewCmnLessonInFile(newCmnLesson, mylessonsHandler->getFilePath())){
                ui->textOut->append("Failed to open file");
                return;
            }
            QString outStr1;
            outStr1.sprintf("Added new record: Category - %s; ID - %d; Num - %d; Subject - %s; Type - %s; Classroom - %d\n",
                           getLessonCatEnum(lessonCat).c_str(), newCmnLessonData.id, newCmnLessonData.num,
                           newCmnLessonData.subjectName.c_str(), getLessonStr(newCmnLessonData.lessonType).c_str(),
                           newCmnLessonData.classroom);
            ui->textOut->append(outStr1);

            break;
    }
    case Online: {
            onlineLessonStruct newOnlineLessonData;
            newOnlineLessonData.subjectName = ui->lineSubject->text().toStdString();
            newOnlineLessonData.lessonType = static_cast<lessonTypesEnum>(ui->comboType->currentIndex() + 1);
            newOnlineLessonData.platform = static_cast<onlinePlatformEnum>(ui->comboPlatformOnline->currentIndex() + 1);
            newOnlineLessonData.link = ui->lineLink->text().toStdString();
            newOnlineLessonData.id = mylessonsHandler->getUniqRandID(Online);

            if (myLessonsOnline.size()) {
                newOnlineLessonData.num = myLessonsOnline[myLessonsOnline.size() - 1].getLessonParams().num + 1;
            } else {
                newOnlineLessonData.num = 1;
            }

            lessonOnline newLessonOnline;
            newLessonOnline.setLessonParams(newOnlineLessonData);
            myLessonsOnline.push_back(newLessonOnline);

            QString outStr2;
            outStr2.sprintf("Added new record: Category - %s; ID - %d; Num - %d; Subject - %s; Type - %s; Platform - %s; Link - %s\n",
                            getLessonCatEnum(lessonCat).c_str(), newOnlineLessonData.id, newOnlineLessonData.num,
                            newOnlineLessonData.subjectName.c_str(), getLessonStr(newOnlineLessonData.lessonType).c_str(),
                            getPlatformStr(newOnlineLessonData.platform).c_str(), newOnlineLessonData.link.c_str());
            ui->textOut->append(outStr2);

            break;
    }
    case Open: {
            openLessonStruct newOpenLessonData;
            newOpenLessonData.subjectName = ui->lineSubject->text().toStdString();
            newOpenLessonData.lessonType = static_cast<lessonTypesEnum>(ui->comboType->currentIndex() + 1);
            newOpenLessonData.link = ui->lineLink->text().toStdString();
            newOpenLessonData.studentsNum = ui->lineStudentsNum->text().toInt();
            newOpenLessonData.teacherName = ui->lineTeacher->text().toStdString();
            newOpenLessonData.id = mylessonsHandler->getUniqRandID(Open);

            if (myLessonsOpen.size()) {
                newOpenLessonData.num = myLessonsOpen[myLessonsOpen.size() - 1].getLessonParams().num + 1;
            } else {
                newOpenLessonData.num = 1;
            }

            lessonOpen newLessonOpen;
            newLessonOpen.setLessonParams(newOpenLessonData);
            myLessonsOpen.push_back(newLessonOpen);

            QString outStr3;
            outStr3.sprintf("Added new record: Category - %s; ID - %d; Num - %d; Subject - %s; Type - %s; Students - %d; Teacher - %s; Link - %s\n",
                           getLessonCatEnum(lessonCat).c_str(), newOpenLessonData.id, newOpenLessonData.num,
                           newOpenLessonData.subjectName.c_str(), getLessonStr(newOpenLessonData.lessonType).c_str(),
                           newOpenLessonData.studentsNum, newOpenLessonData.teacherName.c_str(),
                           newOpenLessonData.link.c_str());
            ui->textOut->append(outStr3);

            break;
    }
        default:
            break;
    }
}

string MainWindow::repr(lessonCategoryEnum cat, int currId) {
    if(cat == Lesson){
        if (!myLessons.size()) {
            return "";
        }
        vector<lesson>::iterator it = begin(myLessons);
        while ((it != (end(myLessons) - 1)) && ((*it).getLessonParams().id != currId)) {
            ++it;
        }
        if ((*it).getLessonParams().id != currId) {
            return "";
        }

        char buff[128] = "";
        sprintf(buff, "ID: %d; Subject: %s; Type: %s; Classroom: %d\n",
                (*it).getLessonParams().id, (*it).getLessonParams().subjectName.c_str(),
                getLessonStr((*it).getLessonParams().lessonType).c_str(), (*it).getLessonParams().classroom);

        return string(buff);

    } else if(cat == Online) {
        if (!myLessonsOnline.size()) {
            return "";
        }

        vector<lessonOnline>::iterator it = begin(myLessonsOnline);
        while ((it != (end(myLessonsOnline) - 1)) && ((*it).getLessonParams().id != currId)) {
            ++it;
        }
        if ((*it).getLessonParams().id != currId) {
            return "";
        }

        char buff[128] = "";
        sprintf(buff, "ID: %d; Subject: %s; Type: %s; Platform: %s; Link: %s\n",
                (*it).getLessonParams().id, (*it).getLessonParams().subjectName.c_str(),
                getLessonStr((*it).getLessonParams().lessonType).c_str(), (*it).getLessonParams().platform, (*it).getLessonParams().link.c_str());

        return string(buff);
    } else if(cat == Open) {
        if (!myLessonsOpen.size()) {
            return "";
        }

        vector<lessonOpen>::iterator it = begin(myLessonsOpen);
        while ((it != (end(myLessonsOpen) - 1)) && ((*it).getLessonParams().id != currId)) {
            ++it;
        }
        if ((*it).getLessonParams().id != currId) {
            return "";
        }

        char buff[128] = "";
        sprintf(buff, "ID: %d; Subject: %s; Type: %s; Link: %s; Students num: %d; Teacher name: %s\n",
                (*it).getLessonParams().id, (*it).getLessonParams().subjectName.c_str(), getLessonStr((*it).getLessonParams().lessonType).c_str(),
                (*it).getLessonParams().link.c_str(), (*it).getLessonParams().studentsNum, (*it).getLessonParams().teacherName.c_str());

        return string(buff);
    }
}

void MainWindow::reprLesson() {
    lessonCategoryEnum cat = static_cast<lessonCategoryEnum>(ui->comboCatRepr->currentIndex() + 1);
    int id = ui->lineID->text().toInt();
    string reprVal = repr(cat, id);
    if (!reprVal.size()) {
        ui->textOut->RedText("Can't find this ID");
        return;
    }
    ui->textOut->append(QString::fromStdString(reprVal));
}
