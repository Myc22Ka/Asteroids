#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <ranges>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string_view>

struct Pracownik
{
	int id = -1;
	std::string imie;
	std::string nazwisko;
	int wiek = -1;
	int wyplata = -1;
};

std::vector<Pracownik> z1_0_wczytywanie(std::string_view path)
{
	std::ifstream plik(path.data());

	if (!plik)
	{
		std::cerr << "Nie udalo sie otworzyc pliku\n";
		return {};
	}

	std::vector<Pracownik> pracownicy;
	std::string linia;

	std::getline(plik, linia); // Pomijamy naglowek
	while (std::getline(plik, linia))
	{
		std::istringstream iss(linia);

		Pracownik p;
		iss >> p.id >> p.imie >> p.nazwisko >> p.wiek >> p.wyplata;

		pracownicy.push_back(p);
	}

	return pracownicy;
}

void z1_1_sortowanie(std::vector<Pracownik>& pracownicy)
{
	std::ranges::sort(pracownicy, std::less(), &Pracownik::nazwisko);
}

void z1_2_prog(std::vector<Pracownik>& const pracownicy, int prog)
{
	auto count = std::ranges::count_if(pracownicy, [prog](Pracownik i) { return i.wyplata > prog; });

	std::cout << "Ilosc pracownikow o wiekszej wyplacie od progu: " << count;
}

void z1_3_nazwisko(std::vector<Pracownik> const& pracownicy, std::string const& nazwisko)
{
	auto found = std::ranges::find(pracownicy, nazwisko, &Pracownik::nazwisko);

	if (found == pracownicy.end()) {
		std::cout << "Nie znaleziono pracownika!";
	}

	std::cout << "Imie: " << found->imie << std::endl;
	std::cout << "Nazwisko: " << found->nazwisko << std::endl;
	std::cout << "Wiek: " << found->wiek << std::endl;
	std::cout << "Wyplata: " << found->wyplata << std::endl;
}

void zadanie_1()
{
	std::cout << "=== ZADANIE 1 ===\n";

	std::vector<Pracownik> pracownicy = z1_0_wczytywanie("pracownicy.txt");

	z1_1_sortowanie(pracownicy);

	std::cout << "Podaj prog wyplaty: ";
	int prog;
	std::cin >> prog;

	z1_2_prog(pracownicy, prog);


	std::cout << '\n' << "Podaj nazwisko pracownika : ";
	std::string nazwisko;
	std::cin >> nazwisko;

	z1_3_nazwisko(pracownicy, nazwisko);
}