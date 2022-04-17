//L A N CS TI

#define TI

#include "Interpolation.h"
#include <Windows.h>

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

#ifdef L
	Interpolation f("StorageOfData0.txt", 0, 12, false);
#endif

#ifdef A
	Aitken_Interpolation f("StorageOfData1.txt", 0, 12);
#define L
#endif

#ifdef N
	Newton f("StorageOfData2.txt", 0, 12);
	f.CreateGraph(f.startInterval, f.endInterval, 0.1, true);
#endif

#ifdef CS
		Cubic_Spline f("StorageOfData4.txt", 1.1, 9);
#define L
#endif

#ifdef TI
		Trigonometric_interpolation f("StorageOfData4.txt", 0, 7);
		f.CreateGraph(f.startInterval, f.endInterval, 0.1);
		//f.SetNewValue(1.5);
		//f.FindAnswer();
#endif

#ifdef L
		f.CreateGraph(f.startInterval, f.endInterval, 0.1);
#endif


}





