#ifndef LESSON_H
#define LESSON_H

#include "lessonTypedefs.h"
#include "csv_writer.h"

inline lessonTypesEnum getLessonEnum(string lessonStr) {
    lessonTypesEnum lesson = noneType;
    if (!lessonStr.compare("Lection")) {
        lesson = Lection;
    } else if (!lessonStr.compare("Practice")) {
        lesson = Practice;
    } else if (!lessonStr.compare("Lab")) {
        lesson = Lab;
    } else if (!lessonStr.compare("Exam")) {
        lesson = Exam;
    }
    return lesson;
}


inline string getLessonStr(lessonTypesEnum lesson){       //functions to convert enum type of lessons to string and vice-versa
    switch (lesson) {
    case Lection:   return "Lection";
    case Practice:   return "Practice";
    case Lab:   return "Lab";
    case Exam:   return "Exam";
    default: return "None";
    }
}

class lesson {
    lessonStruct lessonParams;
    const int param_num = 5;
public:
    lesson();
    lesson(const lesson &src) {lessonParams = src.lessonParams; }
    lesson(lesson && src) {lessonParams = src.lessonParams; }

    lessonStruct getLessonParams() const;
    void setLessonParams(lessonStruct newRecord);
    int getParamNum();
};

#endif // LESSON_H
