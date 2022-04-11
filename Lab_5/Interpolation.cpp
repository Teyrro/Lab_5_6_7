#include "Interpolation.h"


double Interpolation::g(int currentIndex) {
	double dividend(1), divider(1);
	int i(0);
	int ptr = currentIndex;
	while (i < storageOfData.size()) {
		for (i; i < ptr; i++) {
			dividend *= value - storageOfData[i].first;
			divider *= storageOfData[currentIndex].first - storageOfData[i].first;
		}
		if (dividend == 0)
			return 0;
		ptr = storageOfData.size();
		i++;
	}
	return dividend / divider;
}

void Interpolation::P() {
	double sum(0);
	for (int i(0); i < storageOfData.size(); i++) {
		sum += storageOfData[i].second * g(i);
	}
	_answer = sum;
	//std::cout << sum << " ";
	//auto it = storageOfData.begin();
	//for (int i(0); i < storageOfData.size();) {
	//	if (value > storageOfData[i].first)
	//		i++;
	//	else if (value == storageOfData[i].first) break;
	//	else {
	//		storageOfData.insert(it + i, std::make_pair(value, sum));
	//		break;
	//	}

	//	
	//}
}

void Interpolation::OutputDataValue() {
	std::fstream myfile("../example.csv", std::ios::app);
	myfile << value << "; " << _answer << "\n";
}

void Interpolation::OutputData() {
	std::ofstream myfile("../example.csv");
	
	myfile << storageOfData.size() + 2 << "; \n";
	myfile << -100;
	myfile << "; ";
	myfile << getYbyX(storageOfData[0], storageOfData[1],-100);
	myfile << "\n";

	for (auto& ptr : storageOfData) {
		myfile << ptr.first;
		myfile << "; ";
		myfile << ptr.second;
		myfile << "\n";
	}

	myfile << 100;
	myfile << "; ";
	myfile << getYbyX(storageOfData[storageOfData.size()-2], storageOfData[storageOfData.size() - 1], 100);
	myfile << "\n";
	myfile.close();
}

void Aitken_Interpolation::FindAnswer() {

	short counter(storageOfData.size());
	std::vector<double> answer(storageOfData.size());
	for (int i(0); i < storageOfData.size(); i++) {
		answer[i] = storageOfData[i].second;
	}

	while (1 < counter--) {
		std::cout << "Âíåøíÿÿ èòåðàöèÿ " << counter << ", ";
		int l(0), r(storageOfData.size() - counter);
		std::cout << "l - " << l << " r - " << r << " ";
		for (l; l < counter; l++, r++) {
			answer[l] = (answer[l] * (value - storageOfData[r].first) - answer[l + 1] * (value - storageOfData[l].first));
			answer[l] /= (storageOfData[l].first - storageOfData[r].first);
			std::cout << "P" << l << r << " " << answer[l] << " ";
		}
		std::cout << "\n";
	}
	std::cout << answer[0];
	_answer = answer[0];
	//auto it = storageOfData.begin();
	//for (int i(0); i < storageOfData.size();) {
	//	if (value > storageOfData[i].first)
	//		i++;
	//	else {
	//		storageOfData.insert(it + i, std::make_pair(value, answer[0]));
	//		break;
	//	}
	//}
}

double Interpolation::getYbyX(ValueAndAnswer firstPoint, ValueAndAnswer secondPoint, double xValue) {
	double k = (secondPoint.second - firstPoint.second) / (secondPoint.first - firstPoint.first);
	double b = firstPoint.second - k * firstPoint.first;
	return k * xValue + b;
}

void Cubic_Spline::FindAnswer(double x) {
	int index = _answer;
	_answer = massH_M[index - 1].second * pow(storageOfData[index].first - value, 3) / (6 * massH_M[index].first);
	_answer += massH_M[index].second * pow(value - storageOfData[index - 1].first, 3) / (6 * massH_M[index].first);
	_answer += (storageOfData[index - 1].second - (massH_M[index - 1].second * pow(massH_M[index].first, 2)) / 6) * (storageOfData[index].first - value) / massH_M[index].first;
	_answer += (storageOfData[index].second - (massH_M[index].second * pow(massH_M[index].first, 2)) / 6) * (value - storageOfData[index - 1].first) / massH_M[index].first;

	std::cout << _answer;
}



void Cubic_Spline::Ñalculation() {
	for (auto row(0); row < massH_M.size() - 2; row++) {
		for (auto column(0); column < massH_M.size() - 1; column++) {
			if (row == column) {
				mtrx[row][column] = (massH_M[row].first + massH_M[row + 1].first) / 3;
			}
			else if (column == row + 1) {
				mtrx[row][column] = massH_M[row + 1].first / 6;
			}
			else if (column == row - 1) {
				mtrx[row][column] = massH_M[row + 1].first / 6;
			}
			else {
				mtrx[row][column] = 0;
			}
		
		}
		
	}

	printMatrix(mtrx, massH_M.size() - 1, massH_M.size() - 2);

	std::vector<double> d(massH_M.size() - 2);
	for (auto i(1); i < massH_M.size() - 1; i++) {
		d[i - 1] = (storageOfData[i + 1].second - storageOfData[i].second) / massH_M[i].first;
		d[i - 1] -= (storageOfData[i].second - storageOfData[i - 1].second) / massH_M[i - 1].first;
		mtrx[i - 1][massH_M.size() - 2] = d[i - 1];
		std::cout << d[i - 1] << " ";
	}
	std::cout << "\n";
	printMatrix(mtrx, massH_M.size() - 1, massH_M.size() - 2);


	gaussMethod(mtrx, massH_M.size() - 1, massH_M.size() - 2, massH_M);

	FindAnswer(value);
	}