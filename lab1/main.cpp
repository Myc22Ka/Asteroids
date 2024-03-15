#include "iostream";
#include <vector>;

import BasicPlane.Figures;
import Tablica.xd;

int main() {
	Circle circle{ {1,8}, {11,3} };

	std::cout << "area: " << area(circle) << std::endl;
	std::cout << "radius: " << radius(circle) << std::endl;

	std::vector<int> tablica = { 1,20,13,6,5,16 };

	displayTab(tablica);

	return 0;
}