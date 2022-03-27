#include "Interpolation.h"
#include <Windows.h>

int main() {
	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);
	/*Interpolation f("StorageOfData.txt", 1.69);
	
	f.P();
	f.OutputData();
	for (double i(0); i <= 4.2; i += 0.1) {
		f.SetNewValue(i);
		f.P();
		f.OutputDataValue();
	}*/

	//Aitken_Interpolation f("StorageOfData.txt" , 2.56);
	//f.FindAnswer();

	Newton f("StorageOfData.txt", 1.69);
	/*for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5 - i; j++)
			std::cout << f.masY(j, i) << "\t";
		std::cout << "\n";
	}*/
	f.NewtonAnswer(true);
}