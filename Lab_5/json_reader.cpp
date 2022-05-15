#include "json_reader.h"

JSON_Reader::JSON_Reader(string filename) {
    fin.open(filename);
}

vector<vector<string>> JSON_Reader::read(){

    vector<vector<string>> result;
    nlohmann::json json;

    fin >> json;

    for (auto& it: json){
        vector<string> row;
        string str;
        int num;
        it.at("id").get_to(num);
        row.push_back(to_string(num));

        it.at("num").get_to(num);
        row.push_back(to_string(num));

        it.at("subjectName").get_to(str);
        row.push_back(str);

        it.at("lessonType").get_to(str);
        row.push_back(str);

        it.at("classroom").get_to(num);
        row.push_back(to_string(num));

        result.push_back(row);
    }

    return result;
}

JSON_Reader::~JSON_Reader(){
}
