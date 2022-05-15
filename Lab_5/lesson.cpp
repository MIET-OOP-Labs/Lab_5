#include "lesson.h"

lesson::lesson() {
}

lessonStruct lesson::getLessonParams() const {
    return lessonParams;
}

void lesson::setLessonParams(lessonStruct newRecord) {
    lessonParams = newRecord;
}

int lesson::getParamNum() {
    return this->param_num;
}
