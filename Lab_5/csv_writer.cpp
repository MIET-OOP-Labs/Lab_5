#include "csv_writer.h"

CSV_Writer::CSV_Writer() {
}

bool CSV_Writer::clearFile(string filePath){
    ofstream clearFile;
    clearFile.open(filePath, ofstream::out | ofstream::trunc);
    clearFile.close();
}

bool CSV_Writer::writeNewRecordInFile(string newRecord, string filePath){
    ofstream writeFile;
    writeFile.open(filePath, fstream::app);
    if (!writeFile.is_open()) {
        return false;
    }
    writeFile  << newRecord;       // Write to the file

    writeFile.close();
    return true;
}
