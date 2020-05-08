#include "pch.h"
#include "Conveyer.h"

int main() {
	vector<int> one{ 14, 11, 7, 10, 3 };
	vector<int> two{ 7, 15, 4, 8, 13 };
	auto conveyer = new Conveyer;
	conveyer->calculate(one, two);
}
