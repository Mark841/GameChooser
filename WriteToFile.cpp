#include "WriteToFile.h"

WriteToFile::WriteToFile(const std::string fileName) : FileManager(fileName, 2)
{
}
WriteToFile::~WriteToFile()
{
}

//TODO
void WriteToFile::AddToFile(const std::string value)
{
	dataFile.clear();
	dataFile.seekg(0, std::ios::end);
	dataFile << value << "\n";
}

void WriteToFile::SaveLocalDataToFile()
{
	dataFile.open(dataFileFilename, std::ios::out | std::ios::trunc);

	if (!dataFile.is_open())
	{
		std::cout << "PLEASE CLOSE THE " << dataFileFilename << " FILE" << std::endl;
	}

	dataFile.clear();
	dataFile.seekg(0, std::ios::end);

	BackEndAlgorithms* algorithms = BackEndAlgorithms::GetInstance();
	StoresFile* localFileData = algorithms->GetLocalData();

	dataFile << localFileData->storeAmount << "?\n";
	dataFile << localFileData->amountOfDrives << "?\n";
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
	dataFile << localFileData->lastPlayed << "?\n";
	dataFile.close();
}
