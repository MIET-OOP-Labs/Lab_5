#ifndef CSV_WRITER_H
#define CSV_WRITER_H

#include <fstream>

using namespace::std;

class CSV_Writer
{
public:
    CSV_Writer();
    bool writeNewRecordInFile(string newRecord, string filePath);
    bool clearFile(string filePath);
};

#endif // CSV_WRITER_H
