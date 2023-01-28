#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//#include <Windows.h>
//#include <codecvt>

using namespace std;

struct StoresFile
{
	bool fileExists = false;
	int amountOfDrives = 0;
	int storeAmount = 0;
	std::vector<std::string> driveNames;
	// Layout of 2d arrays
	// [[STEAM],[ORIGIN],[UBISOFT],[EPIC],[ROCKSTAR],[BLIZZARD]]
	std::vector<std::vector<std::string>> folderLocationsOnDrive;
	std::vector<std::vector<std::string>> storeLocationsOnDrive;
	std::vector<std::vector<bool>> isFolderOnDrive;
	std::vector<std::vector<bool>> isStoreOnDrive;
	std::vector<int> numberOfFoldersOnDrive;
	std::vector<int> numberOfStoresOnDrive;
	std::string lastPlayed = "null";
};

class FileManager abstract
{
public:
	FileManager(const string fileName, int opening_mode);
	~FileManager();
	virtual void AddToFile(const string value) = 0;

protected:
	fstream dataFile;
	StoresFile localFileData;
};