#include "pch.h"
#include "Conveyer.h"

void Conveyer::calculate(vector<int> first, vector<int> second) {
	this->first = first;
	this->second = second;
	
	printVectors();

	timer = 0;
	tact = 0;
	int sizeOfVectors = first.size();

	for (int i = 0; i < sizeOfVectors; i++) {
		checkVectors(i);
	}
	outputVec.resize(sizeOfVectors, make_pair(0, 0));
	
	while (tact < sizeOfVectors + min_digit_index + 1) {
		vector<thread> threads;
		timer++;
		cout << "\nTact - " << tact + 1 << endl;

		int index = tact;
		for (int digit = min_digit_index; digit >= 0; digit--) {
			if (index >= 0 && index < sizeOfVectors) {
				threads.emplace_back(&Conveyer::addToResult, this, digit, index);
			}
			index--;
		}

		for (thread& i : threads) {
			i.join();
		}

		tact++;
	}
	printResult();
}

void Conveyer::checkVectors(int index) {
	bool isInVector = index >= 0 && index < first.size();
	if (isInVector) {

		bool isCorrectFirst = first[index] >= min_num && first[index] < max_num;
		bool isCorrectSecond = second[index] >= min_num && second[index] < max_num;

		if (!isCorrectFirst) {
			first[index] = min_num;
		}
		if (!isCorrectSecond) {
			second[index] = min_num;
		}
	}
}

void Conveyer::addToResult(int digit, int index) {
	bool balance = false;
	int result = outputVec[index].first;
	int secondP = second[index];
	int firstP = first[index];

	if (firstP & (1 << digit)) {
		for (int i = 0; i <= max_digit_index; i++) {
			bool ifOne = result & (1 << i);								//Check is 1 in Ith digit of result
			bool oneOne = secondP & (1 << i) && result & (1 << i);		//1 and 1 ?
			bool oneZero = secondP & (1 << i) || result & (1 << i);		// 1-0 or 0-1 ?
			bool zeroZero = true;										//is 0-0 ?
			
			if (oneOne) {
				if (!balance) {
					balance = true;
					result = result ^ (1 << i);
				}
			}
			else if (oneZero) {
				if (balance) {
					if (ifOne)
						result = result ^ (1 << i);
				}
				else {
					if (!ifOne)
						result = result ^ (1 << i);
				}
			}
			else if (zeroZero) {
				if (balance) {
					result = result ^ (1 << i);
					balance = false;
				}
			}
		}
	}

	if (digit != 0) {
		result = result << 1;
	}
	outputVec[index].first = result;
	outputVec[index].second = timer;
	corPrint.lock();
	printTact(digit, index);
	corPrint.unlock();
}

void Conveyer::printBinary(int numInTen) {
	for (int i = max_digit_index; i >= 0; i--) {
		if (numInTen & (1 << i)) {
			cout << "1";
		}
		else cout << "0";
		if (i % 4 == 0)cout << "-";
	}
	cout << endl;
}

void Conveyer::printTact(int digit, int index) {
	cout << "========================================\n";
	cout << "Calculations at digit <" << digit << ">" << " at index" << index << "\n";
	first[index] & (1 << digit) ? printBinary(second[index]) : printBinary(0);
	printBinary(outputVec[index].first);
	cout << "========================================\n";
}

void Conveyer::printVectors() {
	cout << "Vectors\n";
	for (int i = 0; i < first.size(); i++) {
		cout << "[" << i << "] " << first[i] << " " << second[i] << endl;
	}
}

void Conveyer::printResult() {
	cout << "\nOutput result\n";
	for (int i = 0; i < first.size(); i++) {
		cout << "[" << i << "] " << outputVec[i].first
			<< " Tacts - " << outputVec[i].second << endl;
	}
}

