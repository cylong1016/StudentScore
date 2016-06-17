#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;
#define BUF_SIZE 1024

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

void avg(vector<string>* scoreList, const char* outfilename) {
    ofstream outfile;
    // ios::trunc表示在打开文件前将文件清空,由于是写入,文件不存在则
    outfile.open(outfilename, ios::trunc);
    
}

int main(int argc, char* argv[]) {
    vector<string>* scoreList = readScore("x.txt");
    cout << scoreList->size() << endl;
    for (auto line : *scoreList) {
        cout << line << endl;
    }
}
