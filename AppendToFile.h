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

	void ReadFromFile();
	void LoadDataFromFile();
	std::vector<std::string> GetValues();
};
