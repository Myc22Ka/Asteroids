#include <iostream>
#include <filesystem>
#include <string>
#include <regex>

namespace fs = std::filesystem;

void zadanie_1(){
    fs::path p{ "/rodzic/dziecko/plik.txt" };

    std::cout << p.root_name() << std::endl; // ""
    std::cout << p.root_directory() << std::endl; // "/"
    std::cout << p.root_path() << std::endl; // "/"
    std::cout << p.relative_path() << std::endl; // "rodzic/dziecko/plik.txt"
    std::cout << p.parent_path() << std::endl; // "/rodzic/dziecko"
    std::cout << p.stem() << std::endl; // "plik"
    std::cout << p.extension() << std::endl; // ".txt"
    std::cout << p.is_absolute() << std::endl; // 0
}

void zadanie_2() {
    std::string path;
    std::cout << "Podaj sciezke do pliku: ";
    std::cin >> path;

    if (!fs::is_directory(path)) {
        std::cout << "\nPodany plik nie jest katalogiem.\n";
        return;
    }
    if (!fs::exists(path)) { 
        std::cout << "\nPodany plik nie istnieje.\n";
        return;
    }

    for (const auto& entry : fs::directory_iterator(path))
    {
        std::cout << entry << std::endl;
    }
}

void zadanie_3() {
    std::string path = "D:/pksem4/Asteroids++";
    std::string path2 = "../createdDir";

    if (!fs::is_directory(path)) {
        std::cout << "\nPodany plik nie jest katalogiem.\n";
        return;
    }
    if (!fs::exists(path)) {
        std::cout << "\nPodany plik nie istnieje.\n";
        return;
    }

    if (fs::exists(path2)) fs::remove_all("D:/pksem4/lab3/createdDir");

    std::cout << "Folder zostal utworzony pomyslnie...\n";
    fs::create_directory(path2);

    for (const auto& entry : fs::directory_iterator(path))
    {
        std::regex reg(".*\.cpp");

        if (std::regex_match(entry.path().string(), reg)) {
            fs::copy(entry, path2);
        }
    }

}

int main()
{
    //zadanie_1();
    //zadanie_2();
    zadanie_3();
}
