#include "iostream";
#include <vector>;
#include "BasicArray.h";

import BasicPlane.Figures;
import BasicArray;

int main() {
	Circle circle{ {1,8}, {11,3} };

	std::cout << "Zadanie 1." << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "area: " << area(circle) << std::endl;
	std::cout << "radius: " << radius(circle) << std::endl;
	std::cout << "------------------------------------------------" << std::endl;

	std::vector<int> array = { 1, 2, 3, 13, 57, 12, 6, 2, 11, 90 };

	std::cout << "\nZadanie 2." << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
	display(array);
	sortVector(array);
	display(array);

	BasicArray basicArray(array);

	std::cout << "------------------------------------------------" << std::endl;
	basicArray.displayArray();
	basicArray.sortArray();
	basicArray.displayArray();
	std::cout << "------------------------------------------------" << std::endl;

	return 0;
}