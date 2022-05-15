#include "lessonsHandler.h"

lessonsHandler::lessonsHandler(vector <lesson> & lessons, vector <lessonOnline> & lessonsOnline, vector <lessonOpen> & lessonsOpen):
    cmnLessonArr_ref{lessons},
    onlineLessonArr_ref {lessonsOnline},
    openLessonArr_ref {lessonsOpen} {}

vector <int> lessonsHandler::getID_arr(const vector <lesson> & lessons) {
    vector <int> ID_arr;
    for (int it = 0; it < lessons.size(); it++) {
        ID_arr.push_back(lessons[it].getLessonParams().id);
    }
    sort(ID_arr.begin(), ID_arr.end());
    ID_arr.erase(unique(ID_arr.begin(), ID_arr.end()), ID_arr.end());
    return ID_arr;
}

vector <int> lessonsHandler::getID_arr(const vector <lessonOnline> & lessonsOnline) {
    vector <int> ID_arr;
    for (int it = 0; it < lessonsOnline.size(); it++) {
        ID_arr.push_back(lessonsOnline[it].getLessonParams().id);
    }
    sort(ID_arr.begin(), ID_arr.end());
    ID_arr.erase(unique(ID_arr.begin(), ID_arr.end()), ID_arr.end());
    return ID_arr;
}


vector <int> lessonsHandler::getID_arr(const vector <lessonOpen> & lessonsOpen) {
    vector <int> ID_arr;
    for (int it = 0; it < lessonsOpen.size(); it++) {
        ID_arr.push_back(lessonsOpen[it].getLessonParams().id);
    }
    sort(ID_arr.begin(), ID_arr.end());
    ID_arr.erase(unique(ID_arr.begin(), ID_arr.end()), ID_arr.end());
    return ID_arr;
}


int lessonsHandler::getUniqRandID(lessonCategoryEnum cat) {
    srand (time(NULL));
    vector <int> ID_sortedArr;
    switch (cat) {
        case Lesson:{
            ID_sortedArr = getID_arr(cmnLessonArr_ref);
            break;
        }
        case Online:{
            ID_sortedArr = getID_arr(onlineLessonArr_ref);
            break;
        }
        case Open:{
            ID_sortedArr = getID_arr(openLessonArr_ref);
            break;
        }
        default:
            break;
    }
    int randNum = 0;
    do {
        randNum = rand() % 100 + 1;
    } while (find(ID_sortedArr.begin(), ID_sortedArr.end(), randNum) != ID_sortedArr.end());

    return randNum;
}

bool lessonsHandler::getCmnRecord(vector<string> str, lessonStruct &record) {
    if (str.size() != CMN_LESSON_PARAM_NUM) {
        return false;
    }
    record.id = stoi(str[0]);
    record.num = stoi(str[1]);
    record.subjectName = str[2];
    record.lessonType = getLessonEnum(str[3]);                 //function for filling record struct from string-line, taken from .csv file
    record.classroom = stoi(str[4]);
    return true;
}

bool lessonsHandler::parseRowsIntoLessons(vector<vector<string>> rows, string fileToSaveName) {
    if (!rows.size()) {
        return 0;
    }

    for (int it = 0; it < rows.size(); it++) {
        lessonStruct currRecord;
        lesson currLesson;
        if (!getCmnRecord(rows[it], currRecord)) {
            return 0;
        }
        currLesson.setLessonParams(currRecord);
        cmnLessonArr_ref.push_back(currLesson);
        saveLessonInFile(currRecord, fileToSaveName);
    }
    return 1;
}

bool lessonsHandler::readNewCmnLessonsArrFromFile(const string filePath) {

    setFilePath(filePath);

    cmnLessonArr_ref.clear();
    string updatedFileName = currFilePath.substr(0,currFilePath.find_last_of('/')+1).append(CMN_LESSON_FILE_NAME);
    if (updatedFileName.compare(filePath)) {
        clearFile(updatedFileName);
    }
    vector<vector<string>> CSV_rows = readCSV(currFilePath);

    if (!parseRowsIntoLessons(CSV_rows, updatedFileName)) {
        return 0;
    }

    return 1;
}

bool lessonsHandler::readNewCmnLessonsArrFrom_JSON(const string filePath) {

    string updatedFileName = currFilePath.substr(0,currFilePath.find_last_of('/')+1).append(CMN_LESSON_FILE_NAME);

    AbstractReader * pAbstactReader = new JSON_Reader(filePath);

    //json_reader myJSON_reader(filePath);
    if (!pAbstactReader->is_open()) {
        return 0;
    }
    vector<vector<string>> JSON_rows = pAbstactReader->read();
    delete pAbstactReader;
    if (!parseRowsIntoLessons(JSON_rows, updatedFileName)) {
        return 0;
    }

    return 1;
}

bool lessonsHandler::writeNewCmnLessonInFile(lesson newLesson, string filePath) {
    string updatedFileName = currFilePath.substr(0,currFilePath.find_last_of('/')+1).append(CMN_LESSON_FILE_NAME);

    if(!saveLessonInFile(newLesson.getLessonParams(), updatedFileName)){
        return 0;
    }
    return 1;
}

vector<lesson> lessonsHandler::getFilteredCmnRecords(lessonStruct filter) {   //filter all records by filter struct. It will be also checked, if some parametr in filter isn't used
    vector<lesson> returnVec;
    for (lesson it : cmnLessonArr_ref) {
        bool subjectEqual = (!it.getLessonParams().subjectName.compare(filter.subjectName)) || (!filter.subjectName.compare(" ")); //check if subjects are equal or subject name in filter is empty, which means this parametr isn't used
        bool lessonTypeEqual = (it.getLessonParams().lessonType == filter.lessonType) || (!filter.lessonType);                //check if lesson types are equal or lesson type in filter is none (none in lessonTypesEnum = 0)
        bool classroomEqual = (it.getLessonParams().classroom == filter.classroom) || (!filter.classroom);                    //check if classrooms are equal or classroom in filter is null
        if (subjectEqual && lessonTypeEqual && classroomEqual) {
            returnVec.push_back(it);
        }
    }
    return returnVec;
}

string lessonsHandler::getFilePath() {
    return currFilePath;
}

void lessonsHandler::setFilePath(string newFilePath) {
    currFilePath = newFilePath;
}

bool lessonsHandler::saveLessonInFile(lessonStruct lessonParams, string filePath) {
    char buff[64] = "";
    sprintf(buff, "%d;%d;%s;%s;%d\n", lessonParams.id, lessonParams.num, lessonParams.subjectName.c_str(), getLessonStr(lessonParams.lessonType).c_str(), lessonParams.classroom);
    return writeNewRecordInFile(buff, filePath);
}

bool lessonsHandler::saveLessonInFile(onlineLessonStruct lessonParams, string filePath) {
    char buff[64] = "";
    sprintf(buff, "%d;%d;%s;%s;%s;%s\n", lessonParams.id, lessonParams.num, lessonParams.subjectName.c_str(), getLessonStr(lessonParams.lessonType).c_str(), lessonParams.platform, lessonParams.link.c_str());
    return writeNewRecordInFile(buff, filePath);
}

bool lessonsHandler::saveLessonInFile(openLessonStruct lessonParams, string filePath) {
    char buff[64] = "";
    sprintf(buff, "%d;%d;%s;%s;%s;%d;%s\n", lessonParams.id, lessonParams.num, lessonParams.subjectName.c_str(), getLessonStr(lessonParams.lessonType).c_str(), lessonParams.link.c_str(), lessonParams.studentsNum, lessonParams.teacherName.c_str());
    return writeNewRecordInFile(buff, filePath);
}


