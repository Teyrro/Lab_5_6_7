//#define LAGRANGE
//#define AITKEN
//#define NEWTON
#define CS


#include "Interpolation.h"
#include <Windows.h>

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

#ifdef LAGRANGE
	Interpolation f("StorageOfData0.txt", 1.69);
	f.P();
	f.OutputData();
	for (double i(f.storageOfData[0].first - 1); i <= f.storageOfData[f.storageOfData.size() - 1].first + 1; i += 0.1) {
		f.OutputDataValue(i, f.FuncForInterp(i));
	}
#endif

#ifdef AITKEN
	Aitken_Interpolation f("StorageOfData1.txt", 1.69);
	f.FindAnswer();

	f.OutputData();
	for (double i(f.storageOfData[0].first - 1); i <= f.storageOfData[f.storageOfData.size() - 1].first + 1; i += 0.1) {
		//f.SetNewValue(i);
		//f.FindAnswer();
		//f.OutputDataValue();
		f.OutputDataValue(i, f.FuncForInterp(i));
	}
#endif

#ifdef NEWTON
	Newton f("StorageOfData2.txt", 1.69);
	f.NewtonAnswer(true);

	f.OutputData();
	for (double i(f.storageOfData[0].first - 1); i <= f.storageOfData[f.storageOfData.size() - 1].first + 1; i += 0.1) {
		//f.SetNewValue(i);
		//f.NewtonAnswer(1);
		//f.OutputDataValue();
		f.OutputDataValue(i, f.FuncForInterp(i));
	}
#endif
#ifdef CS
		Cubic_Spline f("StorageOfData3.txt", 7);
		f.OutputData();
		for (double i(f.storageOfData[0].first + 1); i < f.storageOfData[f.storageOfData.size() - 1].first - 1 ; i += 0.1) {
			f.SetNewValue(i);
			f.FindAnswer();
			f.OutputDataValue();
		}
#endif
	
}





