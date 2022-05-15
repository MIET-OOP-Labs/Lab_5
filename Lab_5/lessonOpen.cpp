#include "lessonOpen.h"

lessonOpen::lessonOpen() {
}

//bool lessonOpen::saveLessonInFile(string filePath) {
//    char buff[64] = "";
//    sprintf(buff, "%d;%d;%s;%s;%s;%d;%s\n", lessonParams.id, lessonParams.num, lessonParams.subjectName.c_str(), getLessonStr(lessonParams.lessonType).c_str(), lessonParams.link.c_str(), lessonParams.studentsNum, lessonParams.teacherName.c_str());
//    return writeNewRecordInFile(buff, filePath);
//}

openLessonStruct lessonOpen::getLessonParams() const {
    return lessonParams;
}

void lessonOpen::setLessonParams(openLessonStruct newRecord) {
    lessonParams = newRecord;
}

int lessonOpen::getParamNum() {
    return param_num;
}
