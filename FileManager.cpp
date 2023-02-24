#include "FileManager.h"

FileManager::FileManager(const std::string filename)
{
	ReadLocalDataFromFile();
	ReadWhitelistDataFromFile();
	ReadCustomDirectoriesDataFromFile();
}
FileManager::~FileManager()
{
}

void FileManager::WriteLocalDataToFileAppend()
{
	std::fstream file(LOCAL_DATA_FILE_FILENAME);
	file.open(LOCAL_DATA_FILE_FILENAME, std::ios::app);

	if (!file.is_open())
	{
		std::cout << "PLEASE CLOSE THE " << LOCAL_DATA_FILE_FILENAME << " FILE" << std::endl;
	}

	file.clear();
	file.seekg(0, std::ios::end);

	BackEndAlgorithms* algorithms = BackEndAlgorithms::GetInstance();
	StoresFile* localFileData = algorithms->GetLocalData();

	file << localFileData->storeAmount << "\n";
	file << localFileData->amountOfDrives << "\n";
	file << algorithms->GetDriveNamesString() << "\n";

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
			file << drive << "\n";
		}
	}
	file << algorithms->GetNoOfFoldersOnDriveString() << "\n";
	file << algorithms->GetNoOfStoresOnDriveString() << "\n";
	file << localFileData->lastPlayed << "\n";
	file.close();
}
void FileManager::WriteLocalDataToFileOverwrite()
{
	std::ofstream file(LOCAL_DATA_FILE_FILENAME);
	file.open(LOCAL_DATA_FILE_FILENAME, std::ios::out);

	if (!file.is_open())
	{
		std::cout << "PLEASE CLOSE THE " << LOCAL_DATA_FILE_FILENAME << " FILE" << std::endl;
	}

	file.clear();

	BackEndAlgorithms* algorithms = BackEndAlgorithms::GetInstance();
	StoresFile* localFileData = algorithms->GetLocalData();

	file << localFileData->storeAmount << "\n";
	file << localFileData->amountOfDrives << "\n";
	file << algorithms->GetDriveNamesString() << "\n";

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
			file << drive << "\n";
		}
	}
	file << algorithms->GetNoOfFoldersOnDriveString() << "\n";
	file << algorithms->GetNoOfStoresOnDriveString() << "\n";
	file << localFileData->lastPlayed << "\n";
	file.close();
}

//TODO - make somewhere where it calls this
void FileManager::WriteWhitelistsToFileAppend()
{
	BackEndAlgorithms* algorithms = BackEndAlgorithms::GetInstance();
	std::vector<std::string> whitelists = algorithms->GetWhitelistData()->directoryNames;

	std::fstream file(WHITELIST_FILE_FILENAME);
	file.open(WHITELIST_FILE_FILENAME, std::ios::app);

	if (!file.is_open())
	{
		std::cout << "FILE NOT FOUND, CREATING A NEW FILE CALLED " << WHITELIST_FILE_FILENAME << " OR PLEASE CLOSE THE " << WHITELIST_FILE_FILENAME << " FILE" << std::endl;
		WriteDefaultWhitelistsToFile(&file);
	}

	WriteToFile(&file, whitelists);

	file.close();
}
void FileManager::WriteCustomDirectoriesToFileOverwrite()
{
	BackEndAlgorithms* algorithms = BackEndAlgorithms::GetInstance();
	CustomDirectoryData* customDirectories = algorithms->GetCustomDirectoryData();
	std::vector<std::vector<std::string>> allStores{
	customDirectories->steamDirectories,
	customDirectories->originDirectories,
	customDirectories->ubisoftDirectories,
	customDirectories->epicDirectories };

	std::ofstream file(CUSTOM_DIRECTORY_FILE_FILENAME);
	file.open(CUSTOM_DIRECTORY_FILE_FILENAME, std::ios::out);

	if (!file.is_open())
	{
		std::cout << "FILE NOT FOUND, CREATING A NEW FILE CALLED " << CUSTOM_DIRECTORY_FILE_FILENAME << " OR PLEASE CLOSE THE " << CUSTOM_DIRECTORY_FILE_FILENAME << " FILE" << std::endl;
	}

	WriteToFile(&file, allStores);

	file.close();
}

//TODO - Clauses for if file is empty then fill it - Why am i not using localDataFile here and instead creating a new file, keep one and get rid of the other
void FileManager::ReadLocalDataFromFile()
{
	std::fstream file(LOCAL_DATA_FILE_FILENAME);
	BackEndAlgorithms* algorithms = BackEndAlgorithms::GetInstance();
	StoresFile* localFileData = algorithms->GetLocalData();

	file.open(LOCAL_DATA_FILE_FILENAME, std::fstream::in | std::fstream::out | std::fstream::trunc);

	if (!file.is_open())
	{
		std::cout << "ISSUE WITH THE " << LOCAL_DATA_FILE_FILENAME << " FILE" << std::endl;
	}

	file.clear();
	file.seekg(0, std::ios::beg);

	int i = 0;
	for (std::string line; std::getline(file, line);)
	{
		//std::cout << "LocalData value:\t" << line << std::endl; //REMOVE
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
void FileManager::ReadWhitelistDataFromFile()
{
	std::fstream file(WHITELIST_FILE_FILENAME);
	BackEndAlgorithms* algorithms = BackEndAlgorithms::GetInstance();
	WhitelistData* whitelistData = algorithms->GetWhitelistData();

	file.open(WHITELIST_FILE_FILENAME, std::fstream::in | std::fstream::out | std::fstream::trunc);
	if (!file.is_open())
	{
		std::cout << "ISSUE WITH THE " << WHITELIST_FILE_FILENAME << " FILE" << std::endl;
	}

	file.clear();
	file.seekg(0, std::ios::beg);

	int numLines = 0;
	std::string unused;
	while (std::getline(file, unused))
	{
		++numLines;
	}

	if (numLines == 0)
	{
		WriteDefaultWhitelistsToFile(&file);
	}

	whitelistData->directoryNames = ReadLinesFromFile(&file);

	file.close();
}
void FileManager::ReadCustomDirectoriesDataFromFile()
{
	std::fstream file(CUSTOM_DIRECTORY_FILE_FILENAME);
	BackEndAlgorithms* algorithms = BackEndAlgorithms::GetInstance();
	CustomDirectoryData* customDirectoryData = algorithms->GetCustomDirectoryData();

	file.open(CUSTOM_DIRECTORY_FILE_FILENAME, std::fstream::in | std::fstream::out | std::fstream::trunc);
	if (!file.is_open())
	{
		std::cout << "ISSUE WITH THE " << CUSTOM_DIRECTORY_FILE_FILENAME << " FILE" << std::endl;
	}

	std::vector<std::string> lines = ReadLinesFromFile(&file);

	for (unsigned int i = 0; i < lines.size(); i++)
	{
		if (i == 0) { customDirectoryData->steamDirectories = ProcessFileLineStringVector(lines[i]); }
		if (i == 1) { customDirectoryData->originDirectories = ProcessFileLineStringVector(lines[i]); }
		if (i == 2) { customDirectoryData->ubisoftDirectories = ProcessFileLineStringVector(lines[i]); }
		if (i == 3) { customDirectoryData->epicDirectories = ProcessFileLineStringVector(lines[i]); }
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

void FileManager::WriteToFile(std::fstream* file, std::vector<std::string> lines)
{
	file->clear();
	file->seekg(0, std::ios::end);
	for (std::string line : lines)
	{
		*file << line << "\n";
	}
}
void FileManager::WriteToFile(std::fstream* file, std::vector<std::vector<std::string>> lines)
{
	std::vector<std::string> toWrite = BackEndAlgorithms::GetInstance()->GetStringsFrom2DStringArray(lines);
	WriteToFile(file, toWrite);
}
void FileManager::WriteToFile(std::ofstream* file, std::vector<std::string> lines)
{
	file->clear();
	for (std::string line : lines)
	{
		*file << line << "\n";
	}
}
void FileManager::WriteToFile(std::ofstream* file, std::vector<std::vector<std::string>> lines)
{
	std::vector<std::string> toWrite = BackEndAlgorithms::GetInstance()->GetStringsFrom2DStringArray(lines);
	WriteToFile(file, toWrite);
}

std::vector<std::string>  FileManager::ReadLinesFromFile(std::fstream* file)
{
	std::vector<std::string> fileLines;

	file->clear();
	file->seekg(0, std::ios::beg);
	for (std::string line; std::getline(*file, line);)
	{
		fileLines.push_back(line);
	}
	return fileLines;
}

void FileManager::WriteDefaultWhitelistsToFile(std::fstream* file)
{
	file->clear();
	file->seekg(0, std::ios::end);
	
	*file << "hiberfil" << "\n";
	*file << "swapfile" << "\n";
	*file << "pagefile" << "\n";
	*file << "DumpStack" << "\n";
	*file << "Audio" << "\n";		
	*file << "lang" << "\n";		
	*file << "Languages" << "\n";		
	*file << "MinGW" << "\n";		
	*file << "Microsoft" << "\n";		
	*file << "Music" << "\n";		
	*file << "Phone" << "\n";		
	*file << "Photos" << "\n";		
	*file << "ProgramData" << "\n";		
	*file << "RivaTuner" << "\n";		
	*file << "steamapps" << "\n";		
	*file << "temp" << "\n";		
	*file << "Users" << "\n";		
	*file << "Videos" << "\n";		
	*file << "Windows" << "\n";		
	*file << "WinREAgent" << "\n";		
	*file << "$Recycle.Bin" << "\n";		
}