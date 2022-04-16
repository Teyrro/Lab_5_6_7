//#define LAGRANGE
//#define AITKEN
//#define NEWTON
//#define CS
#define TI


#include "Interpolation.h"
#include <Windows.h>

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

#ifdef LAGRANGE
	Interpolation f("StorageOfData0.txt", 0, 12, false);
#endif

#ifdef AITKEN
	Aitken_Interpolation f("StorageOfData1.txt", 0, 12);
#define LAGRANGE
#endif

#ifdef NEWTON
	Newton f("StorageOfData2.txt", 0, 12);
	f.CreateGraph(f.startInterval, f.endInterval + f.endInterval, 0.1, true);
#endif

#ifdef CS
		Cubic_Spline f("StorageOfData3.txt", 1.1, 8.9);
#define LAGRANGE
#endif

#ifdef TI
		Trigonometric_interpolation f("StorageOfData3.txt", 0, 10);
#define LAGRANGE
#endif

#ifdef LAGRANGE
		f.CreateGraph(f.startInterval, f.endInterval, 0.1);
#endif


}





