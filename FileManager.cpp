#include "FileManager.h"

FileManager::FileManager(const std::string filename)
{
	LoadDataFromFile();
}
FileManager::~FileManager()
{
	dataFile.close();
}

void FileManager::SaveLocalDataToFileAppend()
{
	dataFile.open(dataFileFilename, std::ios::app);

	if (!dataFile.is_open())
	{
		std::cout << "PLEASE CLOSE THE " << dataFileFilename << " FILE" << std::endl;
	}

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
	dataFile.close();
}
void FileManager::SaveLocalDataToFileOverwrite()
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

//TODO - Clauses for if file is empty then fill it
void FileManager::LoadDataFromFile()
{
	std::ifstream file(dataFileFilename);
	BackEndAlgorithms* algorithms = BackEndAlgorithms::GetInstance();
	StoresFile* localFileData = algorithms->GetLocalData();

	file.open(dataFileFilename, std::ios::out | std::ios::in);

	if (!file.is_open())
	{
		std::cout << "PLEASE CLOSE THE " << dataFileFilename << " FILE" << std::endl;
	}

	file.clear();
	file.seekg(0, std::ios::beg);

	std::vector<std::string> values;
	int i = 0;
	for (std::string line; std::getline(file, line);)
	{
		values.push_back(line);
		std::cout << line << std::endl;
		localFileData->exists = true;
		if (i == 0) { localFileData->storeAmount = ProcessFileLineInt(line); }
		else if (i == 1) { localFileData->amountOfDrives = ProcessFileLineInt(line); }
		// Drive names
		else if (i == 2) { localFileData->driveNames = ProcessFileLineStringVector(line); }
		// Folder locations
		else if (i == 3 || i == 4 || i == 5 || i == 6 || i == 7) { localFileData->folderLocationsOnDrive.push_back(ProcessFileLineStringVector(line)); }
		// Store locations
		else if (i == 8 || i == 9 || i == 10 || i == 11 || i == 12) { localFileData->storeLocationsOnDrive.push_back(ProcessFileLineStringVector(line)); }
		// Is folder on drive
		else if (i == 13 || i == 14 || i == 15 || i == 16 || i == 17) { localFileData->isFolderOnDrive.push_back(ProcessFileLineBoolVector(line)); }
		// Is store on drive
		else if (i == 18 || i == 19 || i == 20 || i == 21 || i == 22) { localFileData->isStoreOnDrive.push_back(ProcessFileLineBoolVector(line)); }
		// num of folders on drive
		else if (i == 23) { localFileData->numberOfFoldersOnDrive = ProcessFileLineIntVector(line); }
		// num of stores on drive
		else if (i == 24) { localFileData->numberOfStoresOnDrive = ProcessFileLineIntVector(line); }
		else if (i == 25)
		{
			localFileData->lastPlayed = line;
			localFileData->exists = true;
		}
		i++;
	}
	file.close();
}

int FileManager::ProcessFileLineInt(std::string value)
{
	return stoi(value);
}
std::vector<std::string> FileManager::ProcessFileLineStringVector(std::string value)
{
	std::stringstream test(value);
	std::string segment;
	std::vector<std::string> seglist;

	while (std::getline(test, segment, '|'))
	{
		seglist.push_back(segment);
	}

	return seglist;
}
std::vector<int> FileManager::ProcessFileLineIntVector(std::string value)
{
	std::stringstream test(value);
	std::string segment;
	std::vector<std::string> seglist;
	while (std::getline(test, segment, '|'))
	{
		seglist.push_back(segment);
	}

	std::vector<int> returnVector;
	for (std::string segments : seglist)
	{
		returnVector.push_back(std::stoi(segments.c_str()));
	}

	return returnVector;
}
std::vector<bool> FileManager::ProcessFileLineBoolVector(std::string value)
{
	std::stringstream test(value);
	std::string segment;
	std::vector<std::string> seglist;
	while (std::getline(test, segment, '|'))
	{
		seglist.push_back(segment);
	}

	std::vector<bool> returnVector;
	for (std::string segments : seglist)
	{
		returnVector.push_back(std::stoi(segments.c_str()));
	}

	return returnVector;
}
