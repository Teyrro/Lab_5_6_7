#pragma once

int matrixSize(int& W, int& H);
void readMatrix(double**mtrx, int W, int H);
void printMatrix(double** mtrx, int W, int H);
void lineNulling(double** mtrx, int W, int H);
void swapLine(double** mtrx, int index1, int index2, int W);
void lineArithmetic(double** mtrx, int lineIndex1, int columnIndex, int W);
void findUnknown(double** mtrx, int W, int H, std::vector<std::pair<float, double>>& out);
void gaussMethod(double** mtrx, int W, int H, std::vector<std::pair<float, double>>& out);
void modifiedGaussMethod(double** mtrx, int W, int H, std::vector<std::pair<float, double>>& out);