#pragma once
#include "GlobalConstants.h"
#include "BackEndAlgorithms.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//#include <Windows.h>
//#include <codecvt>

class FileManager abstract
{
public:
	FileManager(const std::string fileName, int opening_mode);
	~FileManager();
	virtual void AddToFile(const std::string value) = 0;
	virtual void SaveLocalDataToFile() = 0;

protected:
	std::fstream dataFile;
};