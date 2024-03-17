#include <regex>
#include <string>
#include <iostream>

void PrintMatches(std::string str, std::regex reg) {
    std::smatch matches;
    while (std::regex_search(str, matches, reg)) {
        std::cout << std::boolalpha;
        std::cout << "Is there a match: " << matches.ready() << "\n";
        std::cout << "Is there a no matches: " << matches.empty() << "\n";
        std::cout << "Number of matches: " << matches.size() << "\n";
        std::cout << matches.str(1) << "\n";
        str = matches.suffix().str();
        std::cout << "\n";
    }
}

void PrintMatches2(std::string str, std::regex reg) {
    std::sregex_iterator currentMatch(str.begin(), str.end(), reg);
    std::sregex_iterator lastMatch;
    while (currentMatch != lastMatch) {
        std::smatch match = *currentMatch;
        std::cout << match.str() << "\n";
        currentMatch++;
    }
}

int main()
{
    std::string str = "The ape was at the apex";
    std::regex reg("(ape[^ ]?)");

    PrintMatches(str, reg);


    std::string str2 = "I picked the pickle";
    std::regex reg2("(pick([^ ]+)?)");

    PrintMatches2(str2, reg2);

    std::string str3 = "Cat rat mat fat pat";
    std::regex reg3("([rf]at)"); // explore on your own

    std::string repalcement = std::regex_replace(str2, std::regex("\\w*ed"), "fucked"); // replace and find by end of the string
    std::cout << repalcement << std::endl;

    PrintMatches2(str3, reg3);

    std::string str4 = "have";
    std::regex reg4("have");
    bool exist = std::regex_match(str4, reg4); // exact check 

    std::cout << exist << std::endl;
}
