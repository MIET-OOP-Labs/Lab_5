#ifndef LESSONOPEN_H
#define LESSONOPEN_H

#include "lesson.h"
#include "lessonTypedefs.h"

class lessonOpen: protected lesson  {
    openLessonStruct lessonParams;
    const int param_num = 7;
public:
    lessonOpen();

    lessonOpen(const lessonOpen &src) {lessonParams = src.lessonParams; }
    lessonOpen(lessonOpen && src) {lessonParams = src.lessonParams; }

    //bool saveLessonInFile(string filePath);
    openLessonStruct getLessonParams() const;
    void setLessonParams(openLessonStruct newRecord);
    int getParamNum();

    //
};

#endif // LESSONOPEN_H
