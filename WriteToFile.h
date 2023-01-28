#pragma once
#include "FileManager.h"

class WriteToFile : public FileManager
{
public:
	WriteToFile(const string fileName);
	~WriteToFile();

	void AddToFile(const string value);
};

