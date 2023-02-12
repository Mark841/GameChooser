#include "AppendToFile.h"

AppendToFile::AppendToFile(const std::string fileName) : FileManager(fileName, 1)
{
	LoadDataFromFile();
}
AppendToFile::~AppendToFile()
{
}

//TODO - Clauses for if file is empty then fill it
void AppendToFile::ReadFromFile()
{
	std::string next_line;
	dataFile.clear();
	dataFile.seekg(0, std::ios::beg);

	while (getline(dataFile, next_line))
		std::cout << next_line << std::endl;

	//BackEndAlgorithms::GetInstance()->SetLocalData();
}
//TODO - Clauses for if file is empty then fill it
void AppendToFile::LoadDataFromFile()
{
}

//TODO - Clauses for if file is empty then fill it
std::vector<std::string> AppendToFile::GetValues()
{
	std::vector<std::string> values;
	std::string next_line;

	dataFile.clear();
	dataFile.seekg(0, std::ios::beg);

	int count = 0;
	while (getline(dataFile, next_line))
		values.push_back(next_line);
	return values;
}

//TODO
void AppendToFile::AddToFile(const std::string value)
{
	dataFile.clear();
	dataFile.seekg(0, std::ios::end);
	dataFile << value << "\n";
}
//TODO
void AppendToFile::SaveLocalDataToFile()
{
	dataFile.clear();
	dataFile.seekg(0, std::ios::end);

	BackEndAlgorithms* algorithms = BackEndAlgorithms::GetInstance();
	StoresFile* localFileData = algorithms->GetLocalData();

	dataFile << localFileData->storeAmount << "\n";
	dataFile << localFileData->amountOfDrives << "\n";
	dataFile << algorithms->GetDriveNamesString() << "\n";

	std::vector<std::vector<std::string>> groupLocations;
	groupLocations.push_back(algorithms->GetFolderLocationsStrings());
	groupLocations.push_back(algorithms->GetStoreLocationsStrings());
	groupLocations.push_back(algorithms->GetIsFolderOnDriveStrings());
	groupLocations.push_back(algorithms->GetIsStoreOnDriveStrings());
	// Between each group of data eg folders and stores will be a ? and between each folder will be a | 
	for (std::vector<std::string> locations : groupLocations)
	{
		for (std::string drive : locations)
		{
			dataFile << drive << "\n";
		}
	}
	dataFile << algorithms->GetNoOfFoldersOnDriveString() << "\n";
	dataFile << algorithms->GetNoOfStoresOnDriveString() << "\n";
	dataFile << localFileData->lastPlayed << "\n";
	//dataFile.close();
}
//TODO
void AppendToFile::AddToFile(const std::string value1, const std::string value2)
{
	dataFile.clear();
	dataFile.seekg(0, std::ios::end);
	dataFile << value1 << " " << value2 << "\n";
}