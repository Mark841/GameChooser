#pragma once
#include "FileManager.h"

class WriteToFile : public FileManager
{
public:
	WriteToFile(const std::string fileName);
	~WriteToFile();

	void AddToFile(const std::string value);
};

