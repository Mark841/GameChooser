#include "FileManager.h"

FileManager::FileManager(const std::string filename, int opening_mode)
{
}
FileManager::~FileManager()
{
	dataFile.close();
}