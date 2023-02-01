#include "AppendToFile.h"

AppendToFile::AppendToFile(const std::string fileName) : FileManager(fileName, 1)
{
	LoadDataFromFile();
}
AppendToFile::~AppendToFile()
{
}

//TODO - Clauses for if file is empty then fill it
void AppendToFile::ReadFromFile()
{
	std::string next_line;
	dataFile.clear();
	dataFile.seekg(0, std::ios::beg);

	while (getline(dataFile, next_line))
		std::cout << next_line << std::endl;

	//BackEndAlgorithms::GetInstance()->SetLocalData();
}
//TODO - Clauses for if file is empty then fill it
void AppendToFile::LoadDataFromFile()
{
}

//TODO - Clauses for if file is empty then fill it
std::vector<std::string> AppendToFile::GetValues()
{
	std::vector<std::string> values;
	std::string next_line;

	dataFile.clear();
	dataFile.seekg(0, std::ios::beg);

	int count = 0;
	while (getline(dataFile, next_line))
		values.push_back(next_line);
	return values;
}

//TODO
void AppendToFile::AddToFile(const std::string value)
{
	dataFile.clear();
	dataFile.seekg(0, std::ios::end);
	dataFile << value << "\n";
}
//TODO
void AppendToFile::AddToFile(const std::string value1, const std::string value2)
{
	dataFile.clear();
	dataFile.seekg(0, std::ios::end);
	dataFile << value1 << " " << value2 << "\n";
}