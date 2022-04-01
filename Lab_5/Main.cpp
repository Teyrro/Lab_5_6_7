//#define LAGRANGE
//#define AITKEN
#define NEWTON


#include "Interpolation.h"
#include <Windows.h>

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
#ifdef LAGRANGE
	Interpolation f("StorageOfData.txt", 1.69);
	f.P();
	
#endif

#ifdef AITKEN
	Aitken_Interpolation f("StorageOfData.txt", 1.69);
	f.FindAnswer();

#endif

#ifdef NEWTON
	Newton f("StorageOfData.txt", 1.69);
	f.NewtonAnswer(true);
#endif
	f.OutputData();
	for (double i(0); i <= f.storageOfData[f.storageOfData.size() - 1].first; i += 0.1) {
		f.SetNewValue(i);
		f.P();
		f.OutputDataValue();
	}
	
}