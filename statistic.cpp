/* 2016-6-17 */
/* 详情请看 README.md */
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

// 分割字符串
// 以 c 字符串将字符串 s 分割成 v 向量
void splitString(const string& s, vector<string>& v, const string& c) {
    string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(string::npos != pos2) {
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
vector<vector<string>>  readScore(const char* filename) {
    vector<vector<string>> scoreList;
    ifstream infile(filename);
    string buffer;

    int i = 0;
    while(!infile.eof()) {
        vector<string> stuScore;
        getline(infile, buffer);
        if(buffer.length() != 0) { // 去除最后的空行
            splitString(buffer, stuScore, " ");
            scoreList.push_back(stuScore);
        }
        i++;
    }

    infile.close();
    return scoreList;
}

// 1. 求每个学生平均分，每门课平均分，结果保存到文件 ave.txt
void avg(const vector<vector<string>> scoreList, const char* outfile) {
    ofstream out;
    // ios::trunc表示在打开文件前将文件清空,由于是写入,文件不存在则
    out.open(outfile, ios::trunc);

    out << "学生平均分:" << endl;
    for(int i = 1; i < scoreList.size(); i++) {
        vector<string> stuScore = scoreList[i];
        string stuName = stuScore[0];
        double avg = 0.0;
        for (int j = 1; j < stuScore.size(); j++) {
            string score_s = stuScore[j];
            double score_d = atof(score_s.c_str());
            avg = (avg * (j - 1) + score_d) / j;
        }
        out << "学生:" << stuName << "\t" << "平均分:" << avg << endl;
    }

    out << endl << "课程平均分:" << endl;
    for(int i = 1; i < scoreList[0].size(); i++) {
        string courseName = scoreList[0][i];
        double avg = 0.0;
        for(int j = 1; j < scoreList.size(); j++) {
            double score_d = atof(scoreList[j][i].c_str());
            avg = (avg * (j - 1) + score_d) / j;
        }

        out << "课程:" << courseName << "\t\t" << "平均分:" << avg << endl;
    }

    cout << "成功导出到: " << outfile << endl;
    out.close();
}

struct StuTotalScore {
    string name;
    double totalScore;
};

// 排序算法
void sort(vector<StuTotalScore> &nums) {
    for (int i = 1; i < nums.size(); i++) {
        for (int j = i; j > 0; j--) {
            if (nums[j].totalScore > nums[j - 1].totalScore) {
                StuTotalScore temp = nums[j];
                nums[j] = nums[j - 1];
                nums[j - 1] = temp;
            }
        }
    }
}

// 2. 按照总分排序，结果保存到文件 sort.txt
void sort(const vector<vector<string>> scoreList, const char* outfile) {
    ofstream out;
    out.open(outfile, ios::trunc);
    vector<StuTotalScore> stuTotalScores;
    for(int i = 1; i < scoreList.size(); i++) {
        vector<string> stuScore = scoreList[i];
        string name = stuScore[0];
        double totalScore = 0.0;
        for(int j = 1; j < stuScore.size(); j++) {
            totalScore += atof(stuScore[j].c_str());
        }

        struct StuTotalScore stuTotalScore = {name, totalScore};
        stuTotalScores.push_back(stuTotalScore);
    }
    sort(stuTotalScores);
    for(int i = 0; i < stuTotalScores.size(); i++) {
        out << "排名：" << i + 1 << "\t";
        out << "姓名:" << stuTotalScores[i].name << "\t";
        out << "总分:" << stuTotalScores[i].totalScore << endl;
    }
    cout << "成功导出到: " << outfile << endl;
    out.close();
}

// 3. 找不及格学生，结果保存到 fail.txt
void findFailStudent(const vector<vector<string>> scoreList, const char* outfile) {
    ofstream out;
    out.open(outfile, ios::trunc);
    out << "不及格名单:" << endl;
    for(int i = 1; i < scoreList.size(); i++) {
        vector<string> stuScore = scoreList[i];
        for(int j = 1; j < stuScore.size(); j++) {
            double score_d = atof(stuScore[j].c_str());
            if(score_d < 60) {
                out << "学生:" << stuScore[0] << "\t";
                out << "课程:" << scoreList[0][j] << "\t\t";
                out << "分数:" << stuScore[j] << endl;
            }
        }
    }

    cout << "成功导出到: " << outfile << endl;
    out.close();
}

int main(int argc, char* argv[]) {
    vector<vector<string>> scoreList = readScore("x.txt");

    while(true) {
        cout << "请输入以下序号执行功能： " << endl;
        cout << "1. 计算学生平均分、课程平均分" << endl;
        cout << "2. 学生总分排序" << endl;
        cout << "3. 找出不及格学生" << endl;
        cout << "4. 退出" << endl;
        cout << "输入(请不要尝试输入非数字字符！我懒得判断！)： ";
        int option;
        cin >> option;
        switch (option) {
            case 1:
                avg(scoreList, "avg.txt");
                break;
            case 2:
                sort(scoreList, "sort.txt");
                break;
            case 3:
                findFailStudent(scoreList, "fail.txt");
                break;
            case 4:
                cout << "程序退出成功！" << endl;
                return 0;
            default:
                cout << "无效输入，请重新输入！" << endl;
                break;
        }

        cout << endl;
    }
}
