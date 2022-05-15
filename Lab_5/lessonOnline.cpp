#include "lessonOnline.h"

lessonOnline::lessonOnline() {
}

//bool lessonOnline::saveLessonInFile(string filePath) {
//    char buff[64] = "";
//    sprintf(buff, "%d;%d;%s;%s;%s;%s\n", lessonParams.id, lessonParams.num, lessonParams.subjectName.c_str(), getLessonStr(lessonParams.lessonType).c_str(), lessonParams.platform, lessonParams.link.c_str());
//    return writeNewRecordInFile(buff, filePath);
//}

onlineLessonStruct lessonOnline::getLessonParams() const {
    return lessonParams;
}

void lessonOnline::setLessonParams(onlineLessonStruct newRecord) {
    lessonParams = newRecord;
}

int lessonOnline::getParamNum() {
    return param_num;
}
