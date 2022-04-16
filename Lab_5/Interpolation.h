#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include "matrix.h"
#include <cmath>
#include <functional>

using ValueAndAnswer = std::pair<double, double>;

class Interpolation {
private:
	double g(int currentIndex);
public:
	std::vector<ValueAndAnswer> storageOfData;
	double getYbyX(ValueAndAnswer firstPoint, ValueAndAnswer secondPoint, double xValue);
	double value;
	double _answer;
public:
	double virtual  FuncForInterp(double x) {
		double value;
		value = pow(x, 2);
		//value =pow(x, -1);
		return value;
	}

	Interpolation(std::string fileName) {
		std::ifstream input(fileName);
		unsigned short size;
		input >> size;
		storageOfData.resize(size);
		for (int i(0); i < size; i++) {
			input >> storageOfData[i].first;
		}
		for (int i(0); i < size; i++) {
			storageOfData[i].second = FuncForInterp(storageOfData[i].first);
		}

	}

	Interpolation(std::string fileName, double val, bool IsStrange) {
		std::ifstream input(fileName);
		unsigned short size;
		input >> size;

		if (IsStrange) {
			storageOfData.resize(size);
			for (int i(0); i < size; i++) {
				input >> storageOfData[i].first;
			}
			for (int i(0); i < size; i++) {
				storageOfData[i].second = FuncForInterp(storageOfData[i].first);
			}
		}
		else {
			storageOfData.resize(size);
			for (int i(0); i < size; i++) {
				input >> storageOfData[i].first;
			}
			for (int i(0); i < size; i++) {
				input >> storageOfData[i].second;
			}
		}
		value = val;
		
	}

	virtual void  SetNewValue(double val) {
		value = val;
	}

	void OutputData();
	void OutputDataValue();
	void OutputDataValue(double x, double y);

	virtual void FindAnswer();


};

class Aitken_Interpolation : public Interpolation {
public:


	Aitken_Interpolation(std::string fileName, double val) : Interpolation(fileName, val, false) {}
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
		//for (auto& ptr : v) {
			//std::cout << ptr << " ";
		//}
	}
	double operator () (int x, int y) {

		double ans = y + x * len;
		try {
			if (y > len - x - 1)
				throw std::string("Durachek");
			if (x != 0)
				ans -=(x - 1) * (x - 1) / 2 + round((double)(x - 1) / 2);
		}
		catch (std::string errMes) {
			std::cout<<"\n\nError: "<<errMes;
			exit(1);
		}
		
		return v[ans];
	}
};

class Newton : public Interpolation {
	deltaY masY;
	double gValue;
public:
	Newton(std::string filename, double val) : Interpolation(filename, val, false), masY(storageOfData) {
		gValue = (val - storageOfData[0].first) / (storageOfData[1].first - storageOfData[0].first);
		
	}


	void NewtonAnswer(bool isTwo) {
		int fact(1), iter;
		iter = isTwo ? 1 : -1;
		if (isTwo)gValue = (value - storageOfData[storageOfData.size() - 1].first) / (storageOfData[1].first - storageOfData[0].first);
		double answer, dotG = gValue, delY;
		answer = isTwo ? masY(0, masY.len - 1) : masY(0, 0);
		std::cout << answer << " ";
		for (int i(1); i < masY.len; i++) {
			fact *= i;
			delY = isTwo ? masY(i, masY.len - i - 1) : masY(i, 0);
			if (delY >= 0)
				std::cout << "+ ";
			std::cout << delY << " * " << dotG << " / " << fact << " ";
			answer += (delY * dotG) / fact;
			dotG *= gValue + iter;
			iter += iter/abs(iter);
		}
		std::cout << "= ";
		_answer = answer;
		std::cout << answer;
	}
};

class Cubic_Spline : public Interpolation {
	double** mtrx;
	std::vector<std::pair<float, double>> massH_M;
	void FindAnswer(double x);

public:

	Cubic_Spline(std::string filename, double val) : Interpolation(filename, val, true) {

		if (value > storageOfData[storageOfData.size() - 1].first)
			throw "ќшибка: »нтерпол€ци€ возможна только внутри своих узлов";

		massH_M.resize(storageOfData.size());
		_answer = 1; // index between two coordinates
		for (auto i(0); i < massH_M.size() - 1; i++) {
			massH_M[i].first = storageOfData[i + 1].first - storageOfData[i].first;
			massH_M[i].second = 0;
			if (storageOfData[i + 1].first < value) _answer++;
		}
		

		mtrx = new double* [massH_M.size() - 2];

		for (auto i(0); i < massH_M.size() - 2; i++) {
			mtrx[i] = new double [massH_M.size() - 1];
		}
	}
	virtual void  SetNewValue(double val) {
		_answer = 1;
		value = val;
		for (auto i(0); i < massH_M.size() - 1; i++) {
			if (storageOfData[i + 1].first < value) _answer++;
		}
	}

	virtual void FindAnswer();

	~Cubic_Spline() {

		for (auto i(0); i < massH_M.size() - 2; i++) {
			delete[] mtrx[i];
			
		}
		delete[] mtrx;
	}
};


struct ComplexValue {
	double real;
	double im;
	ComplexValue(double real1, double im1) : real(real1), im(im1) {}

	void operator +=(ComplexValue a) {
		real += a.real;
		im += a.im;
	}
};

class Trigonometric_interpolation : public Interpolation {
	const double pi = 3.14159265358979323846;
	short offset;
	ComplexValue sum;

	double EquationA(double index);
	double EquationB(double index);
	
	ComplexValue Equation_Aj(double index);
public:
	Trigonometric_interpolation(std::string filename, double val) : Interpolation(filename, val, false), sum(0, 0) {
		offset = storageOfData[1].first - storageOfData[0].first;
		for (short i(0); i < storageOfData.size() - 1; i++)
		{
			if (offset != storageOfData[i + 1].first - storageOfData[i].first) throw "ќшибка: необходимы точки с одинаковым шагом";
		}
	}



	virtual void FindAnswer() {
		//double b(EquationB(0));
		//for (double step((- storageOfData.size() / 2) + 1); step <= storageOfData.size() / 2; step++) {
		//	//std::cout << " (" << EquationB(step) << ")(cos(" << 2 << "*"
		//	b += EquationB(step) * cos(2 * pi * (step) * (value - storageOfData[0].first) / (storageOfData.size() * offset));
		//	b += EquationA(step) * sin(2 * pi * (step) * (value - storageOfData[0].first) / (storageOfData.size() * offset));
		//}

		for (double step((-(int)storageOfData.size() / 2) + 1); step <= storageOfData.size() / 2; step++) {
			ComplexValue a(0, 0);
			a += Equation_Aj(step);
			if (step == 0) {
				sum += a;
				std::cout << a.real << " " << a.im << " \n";
				continue;
			}
			std::cout << a.real << " " << a.im << " ";
			ComplexValue tmp = a;
			
			a.real = tmp.real * cos(2 * pi * step * ((value - storageOfData[0].first) / (storageOfData.size() * offset))) - tmp.im * sin(2 * pi * step * ((value - storageOfData[0].first) / (storageOfData.size() * offset)));
			a.im = tmp.real * cos(2 * pi * step * ((value - storageOfData[0].first) / (storageOfData.size() * offset))) - tmp.im * sin(2 * pi * step * ((value - storageOfData[0].first) / (storageOfData.size() * offset)));
			std::cout << a.real << " ";
			std::cout << a.im << "  " << " cos(2 * pi * " << step << " (" << value << " - " << storageOfData[0].first << ") / " << storageOfData.size() << " * " << offset << ") - " << (2 * pi * step * ((value - storageOfData[0].first) / (storageOfData.size() * offset))) << "\n";
			

			//a.real = a.real / storageOfData.size();
			//a.im = a.im / storageOfData.size();
			sum += a;
		}
		sum.real = sum.real / storageOfData.size();
		sum.im = sum.im / storageOfData.size();

		std::cout << sum.real << " " << sum.im << "\n";
		_answer = sum.real;
		//std::cout << _answer;
	}


};