#include "FileMenager.h"

FileMenager::FileMenager() : fileName(nullptr) {}

FileMenager::~FileMenager()
{
	delete[] fileName;
}

void FileMenager::setFileName(const char* name)
{
	delete[] fileName;

	size_t length = strlen(name);
	fileName = new char[length + 1];
	strcpy_s(fileName, length + 1, name);
}

const char* FileMenager::getFileName() const
{
	return fileName;
}

void FileMenager::setDataFromFile() {
	std::ifstream file(fileName);
	std::vector<std::pair<std::string, double>> data;
	std::string line;

	if (!file.is_open()) {
		std::cerr << "Error: Could not open file: " << fileName << std::endl;
		return;
	}

	const std::regex reg("([a-zA-Z_]+):\\s*(-?\\d*\\.?\\d+)");

	while (std::getline(file, line)) {
		std::smatch matches;

		if (std::regex_search(line, matches, reg)) {
			std::string variable = matches[1].str();
			double value = std::stod(matches[2].str());
			data.emplace_back(variable, value);
		}
	}

	FileMenager::dataFromFile = data;

	return;
}

const std::vector<std::pair<std::string, double>>& FileMenager::getDataFromFile() const {
	return dataFromFile;
}

const double& FileMenager::getPropertyValue(const std::string& prop) const {
	for (const auto& pair : dataFromFile) 
		if (pair.first == prop) return pair.second;
	std::cout << "Error: Could not find property: " << prop << std::endl;
	return NAN;
}