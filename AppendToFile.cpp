#include "AppendToFile.h"

AppendToFile::AppendToFile(const std::string fileName) : FileManager(fileName, 1)
{
	LoadDataFromFile();
}
AppendToFile::~AppendToFile()
{
}

//TODO - Clauses for if file is empty then fill it
void AppendToFile::LoadDataFromFile()
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
		else if (i == 23) { }
		// num of stores on drive
		else if (i == 24) { }
		else if (i == 25)
		{
			localFileData->lastPlayed = line;
			localFileData->exists = true;
		}
		i++;
	}
	file.close();
}

//TODO
void AppendToFile::AddToFile(const std::string value)
{
	dataFile.clear();
	dataFile.seekg(0, std::ios::end);
	dataFile << value << "\n";
}

void AppendToFile::SaveLocalDataToFile()
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
//TODO
void AppendToFile::AddToFile(const std::string value1, const std::string value2)
{
	dataFile.clear();
	dataFile.seekg(0, std::ios::end);
	dataFile << value1 << " " << value2 << "\n";
}


int AppendToFile::ProcessFileLineInt(std::string value)
{
	return stoi(value);
}
//TODO
std::vector<std::string> AppendToFile::ProcessFileLineStringVector(std::string value)
{
	/* Store the original string in the array, so we can loop the rest
	 * of the algorithm. */
	std::vector<std::string> tokens;
	tokens.push_back(value);

	// Store the split index in a 'size_t' (unsigned integer) type.
	size_t splitAt;
	// Store the size of what we're splicing out.
	size_t splitLen = 1;
	// Create a string for temporarily storing the fragment we're processing.
	std::string frag;
	// Loop infinitely - break is internal.
	while (true)
	{
		/* Store the last string in the vector, which is the only logical
		 * candidate for processing. */
		frag = tokens.back();
		/* The index where the split is. */
		splitAt = frag.find('|');
		// If we didn't find a new split point...
		if (splitAt == std::string::npos)
		{
			// Break the loop and (implicitly) return.
			break;
		}
		/* Put everything from the left side of the split where the string
		 * being processed used to be. */
		tokens.back() = frag.substr(0, splitAt);
		/* Push everything from the right side of the split to the next empty
		 * index in the vector. */
		tokens.push_back(frag.substr(splitAt + splitLen, frag.size() - (splitAt + splitLen)));
	}
	return tokens;
}
//TODO
std::vector<bool> AppendToFile::ProcessFileLineBoolVector(std::string value)
{
	return std::vector<bool>();
}
