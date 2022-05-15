#ifndef ABSTRACTREADER_H
#define ABSTRACTREADER_H

#include <vector>
#include <string>
using namespace std;

class AbstractReader {
public:
    AbstractReader();

    virtual vector<vector<string>> read() {vector<vector<string>> foo; return foo;}
    virtual bool is_open() {return false;}

    virtual ~AbstractReader();
};

#endif // ABSTRACTREADER_H
