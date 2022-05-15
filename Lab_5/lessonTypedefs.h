#ifndef LESSONTYPEDEFS_H
#define LESSONTYPEDEFS_H

#include <string>

using namespace std;

typedef enum {noneType, Lection, Practice, Lab, Exam} lessonTypesEnum;  //enumeration of types of lessons
typedef enum {nonePlatform, Zoom, Moodle, Discord, Skype} onlinePlatformEnum;  //enumeration of types of lessons
typedef enum {noneCat, Lesson, Online, Open} lessonCategoryEnum;  //enumeration of types of lessons

inline string getLessonCatEnum(lessonCategoryEnum cat){       //functions to convert enum type of lessons to string and vice-versa
    switch (cat) {
    case Lesson:   return "Lesson";
    case Online:   return "Online";
    case Open:   return "Open";
    default: return "None";
    }
}

struct lessonStruct {
    uint16_t id = 0;
    int num;
    string subjectName;
    lessonTypesEnum lessonType; //structure that stores info about each record of lessons
    int classroom;
};

struct onlineLessonStruct : lessonStruct {
    onlinePlatformEnum platform;
    string link;
};

struct openLessonStruct : onlineLessonStruct {
    int studentsNum;
    string teacherName;
};

#endif // LESSONTYPEDEFS_H
