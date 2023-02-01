#include "WriteToFile.h"

WriteToFile::WriteToFile(const std::string fileName) : FileManager(fileName, 2)
{
}
WriteToFile::~WriteToFile()
{
}

//TODO
void WriteToFile::AddToFile(const std::string value)
{
	dataFile.clear();
	dataFile.seekg(0, std::ios::end);
	dataFile << value << "\n";
}