#pragma once
#include "windows.h"
#include "fileapi.h"
#include "FileManager.h"
#include <filesystem>
#include <string>
#include <vector>

struct StoresFile
{
	bool exists = false;
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

class BackEndAlgorithms
{
public:
	BackEndAlgorithms(const BackEndAlgorithms& obj);
	static BackEndAlgorithms* GetInstance();

	void ScanDrive(char driveName);
	void ScanAllDrives();
	std::vector<char> GetDriveNames();

	void SetLocalData(int amountOfDrives, int storeAmount, std::vector<std::string> driveNames, std::vector<std::vector<std::string>> folderLocationsOnDrive,
		std::vector<std::vector<std::string>> storeLocationsOnDrive, std::vector<std::vector<bool>> isFolderOnDrive, std::vector<std::vector<bool>> isStoreOnDrive,
		std::vector<int> numberOfFoldersOnDrive, std::vector<int> numberOfStoresOnDrive, std::string lastPlayed) 
	{
		localFileData->exists = true;
		localFileData->amountOfDrives = amountOfDrives;
		localFileData->storeAmount = storeAmount;
		localFileData->driveNames = driveNames;
		localFileData->folderLocationsOnDrive = folderLocationsOnDrive;
		localFileData->storeLocationsOnDrive = storeLocationsOnDrive;
		localFileData->isFolderOnDrive = isFolderOnDrive;
		localFileData->isStoreOnDrive = isStoreOnDrive;
		localFileData->numberOfFoldersOnDrive = numberOfFoldersOnDrive;
		localFileData->numberOfStoresOnDrive = numberOfStoresOnDrive;
		localFileData->lastPlayed = lastPlayed;
	}
	StoresFile* GetLocalData() { return localFileData; }

	void FindStoresOnAllDrivesNoLocalData();

private:
	BackEndAlgorithms() { localFileData = new StoresFile(); }

	void FindStoresOnAllDrives();
	void FindStoresOnDrive(StoresFile* localData, int driveIndex);
	bool FindStore(std::string store, std::string* location, bool found = false);

	bool IsPathWhitelisted(const std::string path);
	bool IsSubpath(const std::filesystem::path& path, const std::filesystem::path& base);
	bool IsSubpath(const std::string path, const std::string subpath);
	bool IsSubDirectoryName(const std::string directory, const std::string subdirectory);

	void SteamStore(StoresFile* localData, int driveIndex, int* noOfStores, int* noOfFolders);
	void OriginStore(StoresFile* localData, int driveIndex, int* noOfStores, int* noOfFolders);
	void UbisoftStore(StoresFile* localData, int driveIndex, int* noOfStores, int* noOfFolders);
	void EpicStore(StoresFile* localData, int driveIndex, int* noOfStores, int* noOfFolders);
	//void BlizzardStore(StoresFile* localData, int driveIndex, int* noOfStores, int* noOfFolders);

    inline static BackEndAlgorithms* algorithms = nullptr;
	StoresFile* localFileData;
};