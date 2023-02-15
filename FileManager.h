#pragma once
#include "GlobalConstants.h"
#include "BackEndAlgorithms.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

class FileManager
{
public:
	FileManager(const std::string fileName);
	~FileManager();
	void SaveLocalDataToFileOverwrite();
	void SaveLocalDataToFileAppend();

	void LoadDataFromFile();


protected:
	std::fstream dataFile;

private:
	int ProcessFileLineInt(std::string value);
	std::vector<std::string> ProcessFileLineStringVector(std::string value);
	std::vector<int> ProcessFileLineIntVector(std::string value);
	std::vector<bool> ProcessFileLineBoolVector(std::string value);
};