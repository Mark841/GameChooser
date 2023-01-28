#pragma once
#include <vector>
#include "FileManager.h"

class AppendToFile : public FileManager
{
public:
	AppendToFile(const string fileName);
	~AppendToFile();

	void AddToFile(const string value);
	void AddToFile(const string value1, const string value2);

	void ReadFromFile();
	void GetDataFromFile();
	vector<string> GetValues();
};
