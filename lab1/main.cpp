#include "iostream";
#include <vector>;

import BasicPlane.Figures;
import BasicArray;

int main() {
	Circle circle{ {1,8}, {11,3} };

	std::cout << "area: " << area(circle) << std::endl;
	std::cout << "radius: " << radius(circle) << std::endl;

	std::vector<int> array = { 1,2,3,13, 57, 12, 6, 2, 11, 90 };

	display(array);
	sortVector(array);
	display(array);

	return 0;
}