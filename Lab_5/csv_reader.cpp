#include "csv_reader.h"

CSV_Reader::CSV_Reader() {
}

vector<string> CSV_Reader::split(const string& str, char delim) {
    vector<string> tokens;
    if (!str.empty()) {
        size_t start = 0;
        size_t end = 0;
        do {
            end = str.find(delim, start);
            tokens.push_back(str.substr(start, (end - start)));
            start = end + 1;
        } while (end != string::npos);
    }

    return tokens;
}

bool CSV_Reader::openFile(string filePath){
    file.open(filePath);
    if (!file.is_open()) {
        return false;
    }
    return true;
}

vector<vector<string>> CSV_Reader::readCSV(string filePath){
    vector<vector<string>> records;

    if(!openFile(filePath)){
        return records;
    }                        //vector that stores splitted line from .csv file
    string line;
    while(getline(file, line)) {
        if(!line.length()){
            continue;
        }
        records.push_back(split(line, ';'));
    }
    file.close();
    return records;
}
