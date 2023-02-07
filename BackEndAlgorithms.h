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

	void ScanDrive(char driveName, std::vector<std::string> customSteam = {}, std::vector<std::string> customOrigin = {}, std::vector<std::string> customUbisoft = {}, std::vector<std::string> customEpic = {});
	void ScanAllDrives(std::vector<std::string> customSteam = {}, std::vector<std::string> customOrigin = {}, std::vector<std::string> customUbisoft = {}, std::vector<std::string> customEpic = {});
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

	void FindStoresOnDrive(int driveIndex, std::vector<std::string> customSteam, std::vector<std::string> customOrigin, std::vector<std::string> customUbisoft, std::vector<std::string> customEpic);
	void FindStoresOnAllDrives(std::vector<std::string> customSteam, std::vector<std::string> customOrigin, std::vector<std::string> customUbisoft, std::vector<std::string> customEpic);
	void FindStoresOnAllDrivesNoLocalData(std::vector<std::string> customSteam, std::vector<std::string> customOrigin, std::vector<std::string> customUbisoft, std::vector<std::string> customEpic);

private:
	BackEndAlgorithms() { localFileData = new StoresFile(); }

	void InitLocalDataSizes();

	void FindStoresOnDrive(StoresFile* localData, int driveIndex, std::vector<std::string> customSteam, std::vector<std::string> customOrigin, std::vector<std::string> customUbisoft, std::vector<std::string> customEpic);
	bool SearchForStores(std::vector<std::string> steamDirectoryName, std::vector<std::string> originDirectoryName, std::vector<std::string> ubisoftDirectoryName, std::vector<std::string> epicDirectoryName, std::string* currentSearchDirectoryPath, std::string* foundSteamLocationPath, std::string* foundOriginLocationPath, std::string* foundUbisoftLocationPath, std::string* foundEpicLocationPath);

	bool IsPathWhitelisted(const std::string path);
	bool IsSubpath(const std::filesystem::path& path, const std::filesystem::path& base);
	bool IsSubpath(const std::string path, const std::string subpath);
	bool IsSubDirectoryName(const std::string directory, const std::string subdirectory);

	void AllStores(StoresFile* localData, int driveIndex, int* noOfStores, int* noOfFolders, std::vector<std::string> customSteam, std::vector<std::string> customOrigin, std::vector<std::string> customUbisoft, std::vector<std::string> customEpic);

    inline static BackEndAlgorithms* algorithms = nullptr;
	StoresFile* localFileData;
};