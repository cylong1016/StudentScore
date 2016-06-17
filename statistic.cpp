/* 2016-6-17 */
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;
#define BUF_SIZE 1024

// 分割字符串
void splitString(const std::string& s, std::vector<std::string>& v, const std::string& c) {
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(std::string::npos != pos2) {
        string substr = s.substr(pos1, pos2-pos1);

        // 此 if 是为了防止分割出来的子字符串是空串
        if(substr.length() != 0) {
            v.push_back(substr);
        } // if end

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}

// 读取数据文件
vector<string>* readScore(const char* filename) {
    ifstream infile(filename);
    char buffer[BUF_SIZE];
    vector<string>* scoreList = new vector<string>();

    while(!infile.eof()) {
        infile.getline(buffer, BUF_SIZE, '\n');
        scoreList->push_back(buffer);
    }

    scoreList->pop_back();  // 移除最后的空行
    infile.close();
    return scoreList;
}

void avg(const vector<string>* scoreList, const char* outfilename) {
    string scoreArr[11][6];
    ofstream out;
    // ios::trunc表示在打开文件前将文件清空,由于是写入,文件不存在则
    out.open(outfilename, ios::trunc);

    string courseNameStr = scoreList->at(0);
    vector<string> courseName;
    splitString(courseNameStr, courseName, " ");
    for(int i = 0; i < courseName.size(); i++) {
        scoreArr[0][i] = courseName.at(i);
        cout << courseName.at(i) << endl;
    }

    out << "学生平均分:" << endl;
    for(int i = 1; i < scoreList->size(); i++) {
        string scoreStr = scoreList->at(i);
        vector<string> stuScore;
        splitString(scoreStr, stuScore, " ");
        string stuName = stuScore.at(0);
        double avg = 0.0;
        for (int j = 1; j < stuScore.size(); j++) {
            string score_s = stuScore.at(j);
            double score_d = atof(score_s.c_str());
            avg = (avg * (j - 1) + score_d) / j;
        }
        out << "学生:" << stuName << " " << "平均分:" << avg << endl;
    }

    cout << "成功导出到 avg.txt" << endl;
}

int main(int argc, char* argv[]) {
    vector<string>* scoreList = readScore("x.txt");
    avg(scoreList, "avg.txt");
    // cout << scoreList->size() << endl;
    // for (auto line : *scoreList) {
        // cout << line << endl;
    // }
}
