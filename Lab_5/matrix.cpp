#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>

int matrixSize(int& W, int& H)
{
	std::ifstream file("matrix.txt");
	file >> W >> H;

	if (H >= W) {
		return 0;
	}

	return 1;
}

void readMatrix(double** mtrx, int W, int H)
{
	std::ifstream file("matrix.txt");

	//skip Width and Height
	int tmp;
	file >> tmp >> tmp;

	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
		{
			file >> mtrx[i][j];
		}
}

void printMatrix(double** mtrx, int W, int H) {

	std::cout << std::fixed;
	
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			std::cout << std::setprecision(3) << mtrx[i][j] << '\t';
		}
		std::cout << '\n';
	}
	std::cout << '\n';

	std::cout << std::fixed;
}

void swapLine(double** mtrx, int index1, int index2, int W) {
	for (int i = 0; i < W; i++) {
		std::swap(mtrx[index1][i], mtrx[index2][i]);
	}
}

void findUnknown(double** mtrx, int W, int H, std::vector<std::pair<float, double>>& out) {
	std::vector <double> unknowns(H);

	for (int i = H - 1; i >= 0; i--) {
		int j = W - 1;
		mtrx[i][j] *= -1;
		for (j; j != i; j--) {
			unknowns[i] += mtrx[i][j];

		}
		if (mtrx[i][j] == 0) {
			throw "Singular matrix";

		}
		unknowns[i] /= -mtrx[i][j];

		for (int f = j; f >= 0; f--) {
			mtrx[f][j] *= unknowns[i];
		}
	}

	for (int i = 0; i < unknowns.size(); i++) {
		std::cout << "X_" << i + 1 << " = " << unknowns[i] << "\n";
		out[i + 1].second = unknowns[i];
	}
}

void lineArithmetic(double** mtrx, int lineIndex1, int columnIndex, int W) {
	if (!mtrx[columnIndex][columnIndex])
		throw "Divide by zero";

	double coefficient = mtrx[lineIndex1][columnIndex] / mtrx[columnIndex][columnIndex];

	std::cout << "(" << lineIndex1 + 1 << ") ";
	std::cout.setf(std::ios::showpos);
	std::cout << coefficient;
	std::cout.unsetf(std::ios::showpos);
	std::cout << " * (" << columnIndex + 1 << ")\n";

	for (int i = 0; i < W; i++) {
		mtrx[lineIndex1][i] -= (coefficient * mtrx[columnIndex][i]);
	}
}

void lineNulling(double** mtrx, int W, int H) {
	for (int i = 0; i < W-2; i++) {
		int j = i + 1;
		for (j; j < H; j++) {
			lineArithmetic(mtrx, j, i, W);
		}
		std::cout << '\n';
		printMatrix(mtrx, W, H);
	}
}

void gaussMethod(double** mtrx, int W, int H, std::vector<std::pair<float, double>>& out) {
	try {
		lineNulling(mtrx, W, H);
		findUnknown(mtrx, W, H, out);
	}
	catch (const char* f) {
		std::cout << "Error: " << f << "\n";
	}
	catch (...) {
		std::cout << "Error: Undefind" << "\n";
	}
}

void findMaxValue(double** mtrx, int W, int H, int columnIndex) {
	int max = columnIndex;
	for (int i = columnIndex + 1; i < H; i++) {
		if (abs(mtrx[i][columnIndex]) > abs(mtrx[max][columnIndex])) {
			swapLine(mtrx, i, max, W);
			std::cout << "(" << i+1 << ") <-> (" << max+1 << ")\n";
		}
	}
}

void lineNullingMax(double** mtrx, int W, int H) {
	for (int i = 0; i < W - 2; i++) {
		int j = i + 1;
		findMaxValue(mtrx, W, H, i);
		for (j; j < H; j++) {
			lineArithmetic(mtrx, j, i, W);
		}
		std::cout << '\n';
		printMatrix(mtrx, W, H);
	}
}

void modifiedGaussMethod(double** mtrx, int W, int H, std::vector<std::pair<float, double>>& out) {
	try {
		lineNullingMax(mtrx, W, H);
		findUnknown(mtrx, W, H, out);
	}
	catch (const char* f) {
		std::cout << "Error: " << f << "\n";
	}
	catch (...) {
		std::cout << "Error: Undefind" << "\n";
	}
}