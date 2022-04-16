//#define LAGRANGE
//#define AITKEN
//#define NEWTON
#define CS
//#define TI


#include "Interpolation.h"
#include <Windows.h>

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

#ifdef LAGRANGE
	Interpolation f("StorageOfData0.txt", 1.69, false);
#endif

#ifdef AITKEN
	Aitken_Interpolation f("StorageOfData1.txt", 1.69);

#endif

#ifdef NEWTON
	Newton f("StorageOfData2.txt", 1.69);
#endif

#ifdef CS
		Cubic_Spline f("StorageOfData3.txt", 7);
#endif

#ifdef TI
		Trigonometric_interpolation f("StorageOfData3.txt", 7);
#endif

		f.OutputData();
		for (double i(f.storageOfData[0].first  - 1); i < f.storageOfData[f.storageOfData.size() - 1].first ; i += 0.1) {
			f.OutputDataValue(i, f.FuncForInterp(i));
		}
}





