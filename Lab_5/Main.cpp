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
	f.OutputData();
	for (double i(0); i <= 4.2; i += 0.1) {
		f.SetNewValue(i);
		f.P();
		f.OutputDataValue();
	}
#endif

#ifdef AITKEN
	Aitken_Interpolation f("StorageOfData.txt", 2.56);
	f.OutputData();
	f.FindAnswer();
#endif

#ifdef NEWTON
	Newton f("StorageOfData.txt", 1.69);
	f.OutputData();
	f.NewtonAnswer(true);
#endif
	

	
}