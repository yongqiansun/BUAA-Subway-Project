// Subway.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include<algorithm>

using namespace std;

const int stationNum = 200;
const int nextStationNum = 10;
//定义结构体 station
struct station {
	int node = 0;
	string name;
	vector<int> nextNode;
	vector<string> line;
	int tansfer = 0;
	int origin = 0;
} Station[stationNum] = {};

int DistanceMatrix[stationNum][stationNum] = {};
int AdjacencyMatrix[stationNum][stationNum] = {};
vector<station> vectorStation;

vector<string> split(const string &s, const string &seperator){
    vector<string> result;
    typedef string::size_type string_size;
    string_size i = 0;
     
    while(i != s.size()){
        //找到字符串中首个不等于分隔符的字母；
        int flag = 0;
        while(i != s.size() && flag == 0){
            flag = 1;
            for(string_size x = 0; x < seperator.size(); ++x)
                if(s[i] == seperator[x]){
                    ++i;
                    flag = 0;
                    break;
                    }
        }
         
        //找到又一个分隔符，将两个分隔符之间的字符串取出；
        flag = 0;
        string_size j = i;
        while(j != s.size() && flag == 0){
            for(string_size x = 0; x < seperator.size(); ++x)
                if(s[j] == seperator[x]){
                    flag = 1;
                    break;
                    }
            if(flag == 0)
                ++j;
        }
        if(i != j){
            result.push_back(s.substr(i, j-i));
            i = j;
        }
    }
    return result;
}

//读取地铁文件，并赋值给Station[stationNum] -map
int READIN(string filePath){
	string filePathTemp = filePath;

	string line, l1, l2, l3, l4, l5, l6;
	int tn, tne, tt, ts;
	char tnn[100] = {}, tl[100] = {};
	ifstream srcFile;
	srcFile.open(filePathTemp, ios::in);
	if (!srcFile.is_open()) { //打开失败
		cout << "Error opening source file." << endl;
		return 0;
	}
	int lineNumTemp = 0;
	srcFile >> l1 >> l2 >> l3 >> l4 >> l5 >> l6;
	vector<string> v;
	while (!srcFile.eof()) {

		srcFile >> l1 >> l2 >> l3 >> l4 >> l5 >> l6;
		cout << l1 << ' ' << l2 << ' ' << l3 << ' ' << l4 << ' ' << l5 << ' ' << l6 << ' ' << endl;
		Station[lineNumTemp].node = stoi(l1);//string to int.
		Station[lineNumTemp].name = l2;
		v = split(l3, ",");
		for (int i = 0; i < v.size(); ++i) {
			Station[lineNumTemp].nextNode.push_back(stoi(v[i]));
		}
		Station[lineNumTemp].line = l4;
		Station[lineNumTemp].tansfer = stoi(l5);
		Station[lineNumTemp].origin = stoi(l6);

		//cout << Station[lineNumTemp].node << ' '<< Station[lineNumTemp].name << ' ' 
		//	<< Station[lineNumTemp].nextNode[0] 
		//	<< ' ' << Station[lineNumTemp].line << ' ' << Station[lineNumTemp].tansfer << ' ' << Station[lineNumTemp].origin << endl;
		lineNumTemp += 1;
	}

	srcFile.close();

}

/*void copyStation(struct station temp1, struct station temp2){
	station t1=temp1, t2=temp2;
	t1.node = t2.node;
	t1.name = t2.name;
	vector<int> nextNode;
	t1.line = t2.line;
	t1.tansfer = t2.tansfer;
	t1.origin = t2.origin;
}*/

//根据-a 参数“如 -a 1号线” 输出 线路站点 到 -o 指定文件，并赋值给Station[stationNum]
int LINE(string linePara, vector<int> lineNTemp) {
	string lineNumTemp = linePara;
	vector<int> lineNodeTemp = lineNTemp;
	int TempNum = 0;

	//遍历Station 找到lineNumTemp的起点
	for (int i = 0; i < stationNum; i++) {

		if (Station[i].line == lineNumTemp && Station[i].origin == 1) { // aaa错误
			lineNodeTemp[0] = Station[i].node;
			TempNum++;
		}
		if (Station[i].name.empty()) {
			return 0;
			break;
		}
	}
	//aaa .line改成vector了，这里错了 全局需要改

	//从起点 找 nextStation，且在同一条线上，且不重复，直到头
	station stationTemp;
	stationTemp = Station[lineNodeTemp[0]];
	while (stationTemp.nextNode.size>1) {
		vector<int> nextNodeTemp = stationTemp.nextNode;
		
		for (int j = 0; j < nextNodeTemp.size(); j++) {
			if (Station[nextNodeTemp[j]].node notin linNodeTemp) {// aaa伪代码
				if (Station[nextNodeTemp[j]].line == lineNumTemp) {// aaa错误
					lineNodeTemp.push_back(Station[nextNodeTemp[j]].node);
					stationTemp = Station[nextNodeTemp[j]];
				}
			}
		}
	}
}

//根据 -o 参数 “如 -o station.txt”输出文件
int OUTPUT(string ofPath, vector<int> lineNTemp) {
	string ofilePath = ofPath;
	vector<int> lineNodeTemp = linNtemp;
	for (int i = 0; i < lineNodeTemp.size(); i++) {
		cout << Station[i].name << endl;
		//aaa 写进文档
		if (Station[i].name.empty()) {
			return 0;
			break;
		}
	}
}

//-b 两个站点 求最短路：遍历所有路径 求出最短
int SHORT(string b1, string b2) {
	string name1 = b1, name2 = b2;

	//aaa 遍历找到name1

	//aaa 从name1 遍历它的nextstation，去重，vector 路径
	//定义map<int i,vector<station>> ,i是路径数目，vector是路径，定义vector dist,记录路径i的距离

	//遍历vector 找出最小dist的序号，输出 map<i,vector> 其中station的line只要跟前面的一样就不输出 否则 输出line
}
//int main(int argc, char* argv[])
int main()
{
	string infilePath, outfilePath, lineNum, startStation, endStation;
    cout << "Begin!\n";

	// 最后要注释掉start
	//-map [path]
	string a2 = "c:\\Users\\sunyo\\Desktop\\peixun\\projects\\BUAA-Subway-Project\\subway-7702\\subway.txt";
	char m1[1000] = "c:\\Users\\sunyo\\Desktop\\peixun\\projects\\BUAA-Subway-Project\\subway-7702\\subway.txt";
	infilePath = m1;
	READIN(infilePath);

	//-a 1号线 
	lineNum = "1号线";
	vector<int> lineNTemp;
	LINE(lineNum, lineNTemp);

	//-o 输出
	char o1[1000] = "station.txt";
	OUTPUT(o1, lineNTemp);
	// 最后要注释掉end */

	// get input para
	/*for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			switch (argv[i][1]) {
			case 'm':
			{
				infilePath = argv[i + 1];
				cout << "infilePath:" << infilePath << endl;
				READIN(infilePath);
			}
				break;
			case 'o':
			{
				outfilePath = argv[i + 1];
				cout << "outfilePath:" << outfilePath << endl;
			}
				break;
			case 'a':
			{
				lineNum = argv[i + 1];
				cout << "lineNum:" << lineNum << endl;
			}
				break;
			case 'b':
			{
				startStation = argv[i + 1];
				endStation = argv[i + 2];
				cout << "startStation:" << startStation << "; endStation:" << endStation << endl;
			}
				break;
			default:
				cout << "参数输入错误！" << endl;
				break;
			}
		}
	}
	*/

	
	//filePath = a1;
	//READIN(filePath);
	//filePath = "c:\\Users\\sunyo\\Desktop\\peixun\\projects\\BUAA-Subway-Project\\subway-7702\\subway.txt";
	//读取地铁文件，并赋值给Station[stationNum]
	cout << "End!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
