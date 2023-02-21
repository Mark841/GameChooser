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
	int storeAmount = 0;
	int amountOfDrives = 0;
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
struct WhitelistFile
{
	std::vector<std::string> directoryNames = {};
};

class BackEndAlgorithms
{
public:
	BackEndAlgorithms(const BackEndAlgorithms& obj);
	static BackEndAlgorithms* GetInstance();

	void InitLocalDataSizes();

	void ScanDrive(const char driveName, const std::vector<std::string> customSteam = {}, const std::vector<std::string> customOrigin = {}, const std::vector<std::string> customUbisoft = {}, const std::vector<std::string> customEpic = {});
	void ScanAllDrives(const std::vector<std::string> customSteam = {}, const std::vector<std::string> customOrigin = {}, const std::vector<std::string> customUbisoft = {}, const std::vector<std::string> customEpic = {});

	std::vector<char> GetDriveNames();
	std::string GetDriveNamesString();
	std::vector<std::string> GetFolderLocationsStrings();
	std::vector<std::string> GetStoreLocationsStrings();
	std::vector<std::string> GetIsFolderOnDriveStrings();
	std::vector<std::string> GetIsStoreOnDriveStrings();
	std::string GetNoOfFoldersOnDriveString();
	std::string GetNoOfStoresOnDriveString();

	std::vector<std::string> GetGamesAlphabetically(bool descending);
	std::vector<std::vector<std::string>> GetGamesByDrive();
	std::vector<std::vector<std::string>> GetGamesByStore();

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
	WhitelistFile* GetWhitelistData() { return whitelistsData; }

	void FindStoresOnAllDrives(const std::vector<std::string> customSteam = {}, const std::vector<std::string> customOrigin = {}, const std::vector<std::string> customUbisoft = {}, const std::vector<std::string> customEpic = {});

private:
	BackEndAlgorithms() { 
		localFileData = new StoresFile(); 
		whitelistsData = new WhitelistFile(); 
	}

	void FindStoresOnDrive(StoresFile* localData, const int driveIndex, const std::vector<std::string> customSteam, const std::vector<std::string> customOrigin, const std::vector<std::string> customUbisoft, const std::vector<std::string> customEpic);
	bool SearchForStoresAndFolders(std::vector<std::string> steamDirectoryName, std::vector<std::string> originDirectoryName, std::vector<std::string> ubisoftDirectoryName, std::vector<std::string> epicDirectoryName, std::string* currentSearchDirectoryPath, std::string* foundSteamLocationPath, std::string* foundOriginLocationPath, std::string* foundUbisoftLocationPath, std::string* foundEpicLocationPath, 
		int depth = 0, bool foundSteam = false, bool foundOrigin = false, bool foundUbisoft = false, bool foundEpic = false);

	bool IsPathWhitelisted(const std::string path);
	bool IsSubpath(const std::filesystem::path& path, const std::filesystem::path& base);
	bool IsSubpath(const std::string path, const std::string subpath);
	bool IsSubpathOfAlternateStore(const std::string path, const std::string currentStoreName);
	bool IsSubDirectoryName(const std::string directory, const std::string subdirectory);

	std::string GetStringFromIntArray(const std::vector<int> intArray);
	std::string GetStringFromStringArray(const std::vector<std::string> stringArray);
	std::vector<std::string> GetStringsFrom2DStringArray(const std::vector<std::vector<std::string>> stringArray);
	std::vector<std::string> GetStringsFrom2DBoolArray(const std::vector<std::vector<bool>> boolArray);

	void AllStores(StoresFile* localData, const int driveIndex, int* noOfStores, int* noOfFolders, const std::vector<std::string> customSteam, const std::vector<std::string> customOrigin, const std::vector<std::string> customUbisoft, const std::vector<std::string> customEpic);

    inline static BackEndAlgorithms* algorithms = nullptr;
	StoresFile* localFileData;
	WhitelistFile* whitelistsData;
};