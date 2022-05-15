#ifndef LESSONSHANDLER_H
#define LESSONSHANDLER_H

#include "lesson.h"
#include "lessonOnline.h"
#include "lessonOpen.h"
#include "csv_writer.h"
#include "csv_reader.h"
#include "json_reader.h"
#include <time.h>
#include <algorithm>

#define CMN_LESSON_FILE_NAME "lessons_common.csv"
#define CMN_LESSON_PARAM_NUM 5

class lessonsHandler: protected CSV_Reader, protected CSV_Writer {

    vector <lesson> & cmnLessonArr_ref;
    vector <lessonOnline> & onlineLessonArr_ref;
    vector <lessonOpen> & openLessonArr_ref;

    vector <int> getID_arr(const vector <lesson> & lessons);
    vector <int> getID_arr(const vector <lessonOnline> & lessonsOnline);
    vector <int> getID_arr(const vector <lessonOpen> & lessonsOpen);

    bool getCmnRecord(vector<string> str, lessonStruct &record);

    bool parseRowsIntoLessons(vector<vector<string>> rows, string fileToSaveName);

    string currFilePath;

    const string onlineLessonFileName = "lessons_online.csv";
    const string openLessonFileName = "lessons_open.csv";

    bool saveLessonInFile(lessonStruct lessonParams, string filePath);
    bool saveLessonInFile(onlineLessonStruct lessonParams, string filePath);
    bool saveLessonInFile(openLessonStruct lessonParams, string filePath);

public:

    lessonsHandler(vector <lesson> & lessons, vector <lessonOnline> & lessonsOnline, vector <lessonOpen> & lessonsOpen);
    bool readNewCmnLessonsArrFromFile(const string filePath);
    bool readNewCmnLessonsArrFrom_JSON(const string filePath);
    bool writeNewCmnLessonInFile(lesson newLesson, string filePath);

    int getUniqRandID(lessonCategoryEnum cat);

    vector<lesson> getFilteredCmnRecords(lessonStruct filter);

    string getFilePath();
    void setFilePath(string newFilePath);
};

#endif // LESSONSHANDLER_H
