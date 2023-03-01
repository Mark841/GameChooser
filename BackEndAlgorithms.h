#ifndef BACKEND_ALGORITHMS_HPP
#define	BACKEND_ALGORITHMS_HPP
#define _REGEX_MAX_STACK_COUNT 1000

#pragma once
#include "windows.h"
#include "fileapi.h"
#include "FileManager.h"
#include <filesystem>
#include <string>
#include <vector>
#include <regex>

class BackEndAlgorithms
{
public:
	BackEndAlgorithms(const BackEndAlgorithms& obj);
	static BackEndAlgorithms* GetInstance();

	void InitLocalDataSizes();

	void ScanDrive(const char driveName);
	void ScanAllDrives();

	bool IsStringNullOrWhitespace(std::string string);

	std::vector<char> GetDriveNames();
	std::string GetDriveNamesString();
	std::vector<std::string> GetFolderLocationsStrings();
	std::vector<std::string> GetStoreLocationsStrings();
	std::vector<std::string> GetIsFolderOnDriveStrings();
	std::vector<std::string> GetIsStoreOnDriveStrings();
	std::string GetNoOfFoldersOnDriveString();
	std::string GetNoOfStoresOnDriveString();

	std::string GetStringFromIntArray(const std::vector<int> intArray);
	std::string GetStringFromStringArray(const std::vector<std::string> stringArray);
	std::vector<std::string> GetStringsFrom2DStringArray(const std::vector<std::vector<std::string>> stringArray);
	std::vector<std::string> GetStringsFrom2DBoolArray(const std::vector<std::vector<bool>> boolArray);

	void GetAllGamesFromFolders();
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
		localFileData->directoryLocationsOnDrive = folderLocationsOnDrive;
		localFileData->storeLocationsOnDrive = storeLocationsOnDrive;
		localFileData->isDirectoryOnDrive = isFolderOnDrive;
		localFileData->isStoreOnDrive = isStoreOnDrive;
		localFileData->numberOfDirectoriesOnDrive = numberOfFoldersOnDrive;
		localFileData->numberOfStoresOnDrive = numberOfStoresOnDrive;
		localFileData->lastPlayed = lastPlayed;
	}
	inline StoresFile* GetLocalData() { return localFileData; }
	inline WhitelistData* GetWhitelistData() { return whitelistsData; }
	inline CustomDirectoryData* GetCustomDirectoryData() { return customDirectoryData; }
	inline void AddToWhitelistData(std::vector<std::string> dataVector) {
		for (std::string data : dataVector) { whitelistsData->directoryNames.push_back(data); }
	}
	inline void AddToCustomDirectoryData(Stores store, std::vector<std::string> dataVector) {
		switch (store)
		{
		case Stores::STEAM:
			for (std::string data : dataVector)	{ customDirectoryData->steamDirectories.push_back(data); }
			break;
		case Stores::EA:
			for (std::string data : dataVector) { customDirectoryData->eaDirectories.push_back(data); }
			break;
		case Stores::UBISOFT:
			for (std::string data : dataVector) { customDirectoryData->ubisoftDirectories.push_back(data); }
			break;
		case Stores::EPIC:
			for (std::string data : dataVector) { customDirectoryData->epicDirectories.push_back(data); }
			break;
		default:
			break;
		}
	}

	void FindStoresOnAllDrives(const std::vector<std::string> customSteam = {}, const std::vector<std::string> customEa = {}, const std::vector<std::string> customUbisoft = {}, const std::vector<std::string> customEpic = {});

private:
	BackEndAlgorithms() { 
		localFileData = new StoresFile(); 
		whitelistsData = new WhitelistData();
		customDirectoryData = new CustomDirectoryData();
	}

	void FindStoresOnDrive(StoresFile* localData, const int driveIndex);
	bool SearchForStoresAndFolders(std::string* currentSearchDirectoryPath, std::string* foundSteamLocationPath, std::string* foundEaDirPath, std::string* foundEaStorePath, std::string* foundUbisoftLocationPath, std::string* foundEpicLocationPath, bool* foundSteam, bool* foundEa, bool* foundUbisoft, bool* foundEpic,
		int depth = 0);

	bool IsPathWhitelisted(const std::string path);
	bool IsSubpath(const std::filesystem::path& path, const std::filesystem::path& base);
	bool IsSubpath(const std::string path, const std::string subpath);
	bool IsSubpathOfAlternateStore(const std::string path, const std::string currentStoreName);
	bool IsSubDirectoryName(const std::string directory, const std::string subdirectory);

	std::string SplitStringAtUpperCase(std::string origString);
	bool DoesDirectoryContainExe(std::filesystem::path dir);
	std::string GetExeInDirectory(std::filesystem::path dir);

	void AllStores(StoresFile* localData, const int driveIndex, int* noOfStores, int* noOfFolders);


    inline static BackEndAlgorithms* algorithms = nullptr;
	StoresFile* localFileData;
	WhitelistData* whitelistsData;
	CustomDirectoryData* customDirectoryData;
	std::vector<GameData> allGames;
};

#endif BACKEND_ALGORITHMS_HPP