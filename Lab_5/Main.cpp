//LAG A N CS TI

#define LAG

#include "Interpolation.h"
#include <Windows.h>

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

#ifdef LAG
	Interpolation f("StorageOfData0.txt", 0, 12, false);
#endif

#ifdef A
	Aitken_Interpolation f("StorageOfData1.txt", 1, 12);
#define LAG
#endif

#ifdef N
	Newton f("StorageOfData2.txt", 0, 12);
	f.CreateGraph(f.startInterval, f.endInterval, 0.1, true);
#endif

#ifdef CS
		Cubic_Spline f("StorageOfData3.txt", 1.1, 9);
#define LAG
#endif

#ifdef TI
		Trigonometric_interpolation f("StorageOfData4.txt", 0, 10);
		f.CreateGraph(f.startInterval, f.endInterval, 0.1);
#endif

#ifdef LAG
		f.CreateGraph(f.startInterval, f.endInterval, 0.1);
#endif


}





