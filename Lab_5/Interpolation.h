#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <cmath>


using ValueAndAnswer = std::pair<double, double>;

class Interpolation {
private:
	double g(int currentIndex);
public:
	std::vector<ValueAndAnswer> storageOfData;
	double value;
	double _answer;
public:
	Interpolation(std::string fileName) {
		std::ifstream input(fileName);
		unsigned short size;
		input >> size;
		storageOfData.resize(size);
		for (int i(0); i < size; i++) {
			input >> storageOfData[i].first;
		}
		for (int i(0); i < size; i++) {
			input >> storageOfData[i].second;
		}

	}
	Interpolation(std::string fileName, double val) {
		std::ifstream input(fileName);
		unsigned short size;
		input >> size;
		storageOfData.resize(size);
		for (int i(0); i < size; i++) {
			input >> storageOfData[i].first;
		}
		for (int i(0); i < size; i++) {
			input >> storageOfData[i].second;
		}
		value = val;
		
	}
	void SetNewValue(double val) {
		value = val;
	}

	void OutputData();
	void OutputDataValue();

	void P();


};

class Aitken_Interpolation : public Interpolation {
public:
	Aitken_Interpolation(std::string fileName, double val) : Interpolation(fileName, val) {}
	void FindAnswer();
};

class deltaY {
	std::vector<double> v;
	
public:
	int len;
	deltaY(std::vector<ValueAndAnswer> startValue) {
		len = startValue.size();
		v.resize(startValue.size()*startValue.size()/2+round((double)startValue.size()/2));
		for (int i = 0; i < startValue.size(); i++)
			v[i] = startValue[i].second;

		for (int i(1), l(startValue.size()), l1(0); i < startValue.size();l += startValue.size() - i, i++) {
			for (int j(0); j < startValue.size() - i; j++) {
				v[l + j] = v[j + 1 + l1] - v[j + l1];
				//std::cout << v[l + j] << " ";
			}
			//std::cout << "\n";
			l1 = l;
		}
		for (auto& ptr : v) {
			//std::cout << ptr << " ";
		}
	}
	double operator () (int x, int y) {
		double ans;
		if (y == 0)
			return v[x];
		ans = x + y*len - (y - 1) * (y - 1) / 2 + round((double)(y - 1) / 2);
		return v[ans];
	}
};

class Newton : Interpolation {
	deltaY masY;
	double gValue;
public:
	Newton(std::string filename, double val) : Interpolation(filename, val), masY(storageOfData) {
		gValue = (val - storageOfData[0].first) / (storageOfData[1].first - storageOfData[0].first);
		
	}
	void NewtonAnswer(bool isTwo) {
		int fact(1);
		double answer = masY(0, 0), dotG = gValue;

		for (int i(0); i < masY.len; i++) {
			fact *= i + 1;
			answer += (masY(i, 1) * dotG) / fact;
			dotG *= gValue - i - 1;
		}
		_answer = answer;
		std::cout << answer;
	}
};