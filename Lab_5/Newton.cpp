#include "Interpolation.h"

void Newton::NewtonAnswer(bool isTwo) {
	int fact(1);
	double answer = masY(0, 0), dotG = gValue;

	for (int i(0); i < masY.len; i++) {
		fact *= i + 1;
		dotG *= gValue - i;
		answer += (masY(i, 1) * dotG) / fact;
	}
	_answer = answer;
	std::cout << answer;
}