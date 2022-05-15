#ifndef JSON_READER_H
#define JSON_READER_H

#include "abstractReader.h"
#include <fstream>
#include <json.hpp>

class JSON_Reader: public AbstractReader {
    ifstream fin;
public:
    JSON_Reader(const string filename);

    vector<vector<string>> read();
    bool is_open() {return fin.is_open();};

    ~JSON_Reader();
};

#endif // JSON_READER_H
