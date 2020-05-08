#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

class Conveyer {
public:
	void calculate(vector<int> first, vector<int> second);

	static void printBinary(int numInTen);
private:
	//Maximum number of digits in binary numbers that can be in that programm
	static const int min_digit_index = 3;
	static const int max_digit_index = 7;
	//Border of calculation to this conveyer
	static const int max_num = 16;
	static const int min_num = 0;

	int timer;
	int tact;

	vector<int> first;
	vector<int> second;
	vector<pair<int, int>> outputVec;

	mutex corPrint;

	void checkVectors(int index);

	void addToResult(int digit, int index);
	void printTact(int digit, int index);

	void printResult();
	void printVectors();
};

