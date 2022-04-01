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
		std::cout << "¬нешн€€ итераци€ " << counter << ", ";
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

