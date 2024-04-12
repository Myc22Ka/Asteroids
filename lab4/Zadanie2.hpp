#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

// Wyœwietliæ poprawione temperatury z wektora
// - usun¹æ niedodatnie z koñca
// - pomno¿yæ pozosta³e temperatury * 2
// - odfiltrowaæ nieskrajne temperatury (zostawiæ >= 20 lub <=-10)
// - wyœwietliæ w oryginalnej kolejnoœci (ujemne temperatury z przodu)
// - wyœwietliæ od tego indeksu, który poda u¿ytkownik funkcji *
// - wyœwietliæ maksymalnie tyle liczb ile poda u¿ytkownik do argumentu *

void printCorrectedTemp(const std::vector<int>& temperatures, int since, int n_displayed)
{
	auto multiply_view = std::views::transform([](int i) {return i << 1; });
	auto filtered_view = std::views::filter([](int i) {return i >= 20 || i <= -10; });

	for (auto& i : temperatures)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;

	for (auto i : temperatures
		| std::views::reverse
		| multiply_view
		| std::views::drop_while([](int i) {return i < 0; })
		| filtered_view
		| std::views::reverse)
		{

		}
}

void zadanie_2()
{
	std::cout << "\n\n=== ZADANIE 2 ===\n";
	std::vector<int> data{ -10, -6, -1, -2, -3, 2, 3, 10, 7, 13, 15, 8, 19, 10, 7, 2, 0, -1, -5, -10, -20, -25 };
	printCorrectedTemp(data, 1, 10);
}