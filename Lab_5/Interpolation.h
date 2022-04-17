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
	double startInterval;
	double endInterval;

	double virtual  FuncForInterp(double x) {
		double value;
		//value = sqrt(x);
		//value =pow(x, -1);
		value = pow(x, 2);
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

	Interpolation(std::string fileName, double startInterval, double endInterval, bool IsStrange) : 
		startInterval(startInterval),
		endInterval(endInterval) 
	{
		std::ifstream input(fileName);
		unsigned short size;
		input >> size;

		if (IsStrange) {
			storageOfData.resize(size);
			for (int i(0); i < size; i++) {
				input >> storageOfData[i].first;
			}
			for (int i(0); i < size; i++) {
				input >> storageOfData[i].second;
			}
		}
		else {
			storageOfData.resize(size);
			for (int i(0); i < size; i++) {
				input >> storageOfData[i].first;
			}
			for (int i(0); i < size; i++) {
				storageOfData[i].second = FuncForInterp(storageOfData[i].first);
			}
		}

	}

	virtual void  SetNewValue(double val) {
		value = val;
	}

	void OutputData();
	void OutputDataValue();
	void OutputDataValue(double x, double y);

	virtual void FindAnswer();

	virtual void CreateGraph(double startInterval, double endInterval, double step) {
		OutputData();

		OutputDataValue((endInterval - startInterval)/step, 0);
		for (auto i(startInterval); i + step * 0.1 < endInterval; i += step) {
			value = i;
			FindAnswer();
			OutputDataValue();
		}

		OutputDataValue((endInterval - startInterval)/step, 0);
		for (double i(startInterval);  i + step * 0.1 < endInterval; i += step) {
			OutputDataValue(i, FuncForInterp(i));
		}
	}


};

class Aitken_Interpolation : public Interpolation {
public:
	Aitken_Interpolation(std::string fileName, double startInterval, double endInterval) : Interpolation(fileName, startInterval, endInterval, false) {

	}
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
	double offset;

public:
	Newton(std::string filename, double startInterval, double endInterval) : Interpolation(filename, startInterval, endInterval, false), masY(storageOfData) {
		try {
			offset = storageOfData[1].first - storageOfData[0].first;
			value = startInterval;
			for (short i(0); i < storageOfData.size() - 1; i++)
			{
				if (offset != storageOfData[i + 1].first - storageOfData[i].first) throw std::string("ќшибка: необходимы точки с одинаковым шагом");
			}
			SetGValue();
		}
		catch (std::string str) {
			std::cout << "\n\n" << str;
			exit(1);
		}
	}
	void SetGValue() {
		gValue = (value - storageOfData[0].first) / (offset);
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

	virtual void CreateGraph(double startInterval, double endInterval, double step, bool IsTwo) {
		OutputData();

		OutputDataValue((endInterval - startInterval)/step, 0);
		for (auto i(startInterval); i + step*0.1 < endInterval; i += step) {
			value = i;
			SetGValue();
			NewtonAnswer(IsTwo);
			OutputDataValue();
		}

		OutputDataValue((endInterval - startInterval)/step, 0);
		for (double i(startInterval); i + step * 0.1 < endInterval; i += step) {
			OutputDataValue(i, FuncForInterp(i));
		}
	}
};

class Cubic_Spline : public Interpolation {
	double** mtrx;
	std::vector<std::pair<float, double>> massH_M;
	void FindAnswer(double x);

public:

	Cubic_Spline(std::string filename, double startInterval, double endInterval) : Interpolation(filename, startInterval, endInterval, true) {
		value = startInterval;
		if (value > storageOfData[storageOfData.size() - 1].first or value < storageOfData[0].first)
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

		FindAnswer();


	}

	virtual void CreateGraph(double startInterval, double endInterval, double step) {
		try {
			OutputData();

			OutputDataValue((endInterval - startInterval) / step, 0);
			for (auto i(startInterval); i + step * 0.1 < endInterval; i += step) {
				SetNewValue(i);
				FindAnswer(value);
				OutputDataValue();
			}
		}
		catch (std::string str) {
			std::cout << "\n\n" << str << "\n";
		}
		

		//OutputDataValue((endInterval - startInterval), 0);
		//for (double i(startInterval); i < endInterval; i += step) {
		//	OutputDataValue(i, FuncForInterp(i));
		//}
	}

	virtual void  SetNewValue(double val) {
		if (val > storageOfData[storageOfData.size() - 1].first or val < storageOfData[0].first)
			throw std::string("ќшибка: »нтерпол€ци€ возможна только внутри своих интервалов " + std::to_string(storageOfData[storageOfData.size() - 1].first) + " > " +
				std::to_string(val + 0.000001)+ " > "+std::to_string(storageOfData[0].first));

		_answer = 1; // index between two coordinates
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

	void operator /=(int a) {
		real /= a;
		im /= a;
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
	Trigonometric_interpolation(std::string filename, double startInterval, double endInterval) : 
		Interpolation(filename, startInterval, endInterval, false), 
		sum(0, 0) 
	{
		offset = storageOfData[1].first - storageOfData[0].first;
		for (short i(0); i < storageOfData.size() - 1; i++)
		{
			if (offset != storageOfData[i + 1].first - storageOfData[i].first) throw "ќшибка: необходимы точки с одинаковым шагом";
		}
	}
	virtual void FindAnswer();

	virtual void CreateGraph(double startInterval, double endInterval, double step) {
		OutputData();

		OutputDataValue((endInterval - startInterval)/step, 0);
		for (auto i(startInterval); i + step * 0.1 < endInterval; i += step) {
			value = i;
			FindAnswer();
			OutputDataValue();
		}

		OutputDataValue((endInterval - startInterval) / step, 0);
		for (auto i(startInterval); i + step * 0.1 < endInterval; i += step) {
			value = i;
			FindAnswer();
			std::fstream myfile("../example.csv", std::ios::app);
			myfile << value << "; " << sum.im << "\n";
		}

		OutputDataValue((endInterval - startInterval) / step, 0);
		for (double i(startInterval); i + step * 0.1 < endInterval; i += step) {
			OutputDataValue(i, FuncForInterp(i));
		}
	}




};