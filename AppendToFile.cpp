#include "AppendToFile.h"

AppendToFile::AppendToFile(const string fileName) : FileManager(fileName, 1)
{
	GetDataFromFile();
}
AppendToFile::~AppendToFile()
{
}

//TODO
void AppendToFile::ReadFromFile()
{
	string next_line;
	dataFile.clear();
	dataFile.seekg(0, ios::beg);

	while (getline(dataFile, next_line))
		cout << next_line << endl;
}
//TODO
void AppendToFile::GetDataFromFile()
{
	localFileData.amountOfDrives;
	localFileData.driveNames;
	localFileData.fileExists;
	localFileData.folderLocationsOnDrive;
	localFileData.isFolderOnDrive;
	localFileData.numberOfFoldersOnDrive;
	localFileData.lastPlayed;
	localFileData.storeAmount;
	localFileData.storeLocationsOnDrive;
	localFileData.isStoreOnDrive;
	localFileData.numberOfStoresOnDrive;
}

//TODO
vector<string> AppendToFile::GetValues()
{
	vector<string> values;
	string next_line;

	dataFile.clear();
	dataFile.seekg(0, ios::beg);

	int count = 0;
	while (getline(dataFile, next_line))
		values.push_back(next_line);
	return values;
}

//TODO
void AppendToFile::AddToFile(const string value)
{
	dataFile.clear();
	dataFile.seekg(0, ios::end);
	dataFile << value << "\n";
}
//TODO
void AppendToFile::AddToFile(const string value1, const string value2)
{
	dataFile.clear();
	dataFile.seekg(0, ios::end);
	dataFile << value1 << " " << value2 << "\n";
}