#include "WriteToFile.h"

WriteToFile::WriteToFile(const string fileName) : FileManager(fileName, 2)
{
}
WriteToFile::~WriteToFile()
{
}

//TODO
void WriteToFile::AddToFile(const string value)
{
	dataFile.clear();
	dataFile.seekg(0, ios::end);
	dataFile << value << "\n";
}