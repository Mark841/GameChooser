#pragma once
#include "FileManager.h"

class AppendToFile : public FileManager
{
public:
	AppendToFile(const std::string fileName);
	~AppendToFile();

	void AddToFile(const std::string value);
	void AddToFile(const std::string value1, const std::string value2);
	void SaveLocalDataToFile();

	void LoadDataFromFile();

private:
	int ProcessFileLineInt(std::string value);
	std::vector<std::string> ProcessFileLineStringVector(std::string value);
	std::vector<bool> ProcessFileLineBoolVector(std::string value);
};
