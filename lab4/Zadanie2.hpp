#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

// Wy�wietli� poprawione temperatury z wektora
// - usun�� niedodatnie z ko�ca
// - pomno�y� pozosta�e temperatury * 2
// - odfiltrowa� nieskrajne temperatury (zostawi� >= 20 lub <=-10)
// - wy�wietli� w oryginalnej kolejno�ci (ujemne temperatury z przodu)
// - wy�wietli� od tego indeksu, kt�ry poda u�ytkownik funkcji *
// - wy�wietli� maksymalnie tyle liczb ile poda u�ytkownik do argumentu *

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