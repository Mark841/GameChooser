#ifndef BACKEND_ALGORITHMS_HPP
#define	BACKEND_ALGORITHMS_HPP
#define _REGEX_MAX_STACK_COUNT 1000

#pragma once
#include "windows.h"
#include "fileapi.h"
#include "FileManager.h"
#include "CurlPlusPlus.h"
#include <filesystem>
#include <string>
#include <vector>
#include <regex>
#include <thread>
#include <curl/curl.h>

class BackEndAlgorithms
{

public:
	BackEndAlgorithms(const BackEndAlgorithms& obj);
	static BackEndAlgorithms* GetInstance();

	void InitLocalDataSizes();

	void ScanDrive(const char driveName);
	void ScanDrive(const int driveIndex);
	void ScanAllDrives();
	void ScanAllDrivesInitial();

	bool IsStringNullOrWhitespace(std::string string);

	std::vector<char> GetDriveNames();
	std::string GetDriveNamesString();
	std::vector<std::string> GetFolderLocationsStrings();
	std::vector<std::string> GetStoreLocationsStrings();
	std::vector<std::string> GetIsFolderOnDriveStrings();
	std::vector<std::string> GetIsStoreOnDriveStrings();
	std::string GetNoOfFoldersOnDriveString();
	std::string GetNoOfStoresOnDriveString();

	template <typename T> std::string GetStringFromVector(const std::vector<T> vector);
	template <typename T> std::vector<std::string> GetStringsFrom2DVector(const std::vector<std::vector<T>> vector);

	void GetAllGamesFromFolders();
	void GetAllGamesFromDrive(const std::vector<std::string> directoryLocationsOnDrive, const int driveIndex);
	std::vector<GameData> GetGamesAlphabetically(bool descending);
	std::vector<std::vector<GameData>> GetGamesByDrive();
	std::vector<std::vector<GameData>> GetGamesByStore();

	void LaunchGame(const GameData& game);
	void LaunchStore(const Stores& store);
	void LaunchExe(const std::string exe);

	std::vector<SearchGameData> SearchStores(const std::string gameName);
	SearchGameData* SearchStore(const Stores& storeName, const std::string gameName);

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
	inline GameData* GetLastPlayedGameData() { return lastPlayedGame; }
	inline void AddToWhitelistData(std::vector<std::string> dataVector) 
	{
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

	template <typename T> std::string ToString(const T& t) { return std::to_string(t); }
	std::string ToString(const std::string& t) { return t; }
	std::string ToString(const Stores& store)
	{
		switch (store)
		{
		case Stores::STEAM: return "STEAM";
		case Stores::EA: return "EA";
		case Stores::UBISOFT: return "UBISOFT";
		case Stores::EPIC: return "EPIC";
		case Stores::ROCKSTAR: return "ROCKSTAR";
		case Stores::BLIZZARD: return "BLIZZARD";
		default:
			return "NOT VALID STORE";
		}
	}
	std::string ToString(const GameData& game)
	{
		std::string gameString = game.gameName + "|" + game.gameDirectory + "|" + game.gameExe + "|" + ToString(game.store) + "|" + game.drive;
	}
	std::vector<std::string> GetGameValues(GameData game)
	{
		std::vector<std::string> gameData;
		gameData.push_back(game.gameName);
		gameData.push_back(game.gameDirectory);
		gameData.push_back(game.gameExe);
		gameData.push_back(ToString(game.store));
		gameData.push_back(std::to_string(game.drive));
		return gameData;
	}
	Stores SetStoreValue(const std::string store)
	{
		if ("STEAM") return Stores::STEAM;
		if ("EA") return Stores::EA;
		if ("UBISOFT") return Stores::UBISOFT;
		if ("EPIC") return Stores::EPIC;
		if ("ROCKSTAR") return Stores::ROCKSTAR;
		if ("BLIZZARD") return Stores::BLIZZARD;
		else return Stores::NOSTORE;
	}
	GameData SetGameDataValues(const std::vector<std::string> gameValues)
	{
		GameData game;
		game.gameName = gameValues[0];
		game.gameDirectory = gameValues[1];
		game.gameExe = gameValues[2];
		game.store = SetStoreValue(gameValues[3]);
		game.drive = gameValues[4][0];
		return game;
	}

private:
	BackEndAlgorithms() 
	{
		localFileData = new StoresFile();
		whitelistsData = new WhitelistData();
		customDirectoryData = new CustomDirectoryData();
		lastPlayedGame = new GameData();
	}

	inline void ThreadScanDrive(const char drive);

	void FindStoresOnDrive(StoresFile* localData, const int driveIndex);
	bool SearchForStoresAndFolders(std::string* currentSearchDirectoryPath, std::string* foundSteamLocationPath, std::string* foundEaDirPath, std::string* foundEaStorePath, std::string* foundUbisoftLocationPath, std::string* foundEpicLocationPath, bool* foundSteam, bool* foundEa, bool* foundUbisoft, bool* foundEpic,
		int depth = 0);
	bool RecurseSearchForExe(std::string* currentSearchDirectoryPath, std::string* foundLocationPath, int depth = 0);

	bool IsPathWhitelisted(const std::string path);
	bool IsSubpath(const std::filesystem::path& path, const std::filesystem::path& base);
	bool IsSubpath(const std::string path, const std::string subpath);
	bool IsSubpathOfAlternateStore(const std::string path, const std::string currentStoreName);
	bool IsSubDirectoryName(const std::string directory, const std::string subdirectory);
	bool IsStoreACustomDir(const std::string dirName, const std::string storeName);
	bool IsGameDirWhitelisted(const std::string dirName);

	std::string SplitStringAtUpperCase(std::string origString);
	void RegexChecker(std::regex regex, std::string origString, std::smatch match, std::vector<std::string>& insertAfterLetter, std::vector<std::string>& subsequentLetterCheck);
	bool DoesDirectoryContainExe(std::filesystem::path dir);
	std::string GetExeInDirectory(std::filesystem::path dir);

	void AllStores(StoresFile* localData, const int driveIndex, int* noOfStores, int* noOfFolders);

	bool SteamSearch(const std::string gameName, SearchGameData* resultData);
	bool EASearch(const std::string gameName, SearchGameData* resultData);
	bool UbisoftSearch(const std::string gameName, SearchGameData* resultData);
	bool EpicSearch(const std::string gameName, SearchGameData* resultData);

    inline static BackEndAlgorithms* algorithms = nullptr;
	StoresFile* localFileData;
	WhitelistData* whitelistsData;
	CustomDirectoryData* customDirectoryData;
	GameData* lastPlayedGame;
	std::vector<GameData> allGames;
	std::vector<std::vector<GameData>> allGamesByDrive;
};

#endif BACKEND_ALGORITHMS_HPP