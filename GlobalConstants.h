#ifndef GLOBAL_CONSTANTS_HPP
#define GLOBAL_CONSTANTS_HPP

#pragma once
#include <string>
#include <vector>

enum class Stores
{
	STEAM,
	EA,
	UBISOFT,
	EPIC,
	ROCKSTAR,
	BLIZZARD
};

const std::vector<std::string> STORE_NAMES = { "Steam", "EA", "Ubisoft", "Epic", "Rockstar", "Blizzard"};
const std::vector<Stores> STORE_ENUMS = { Stores::STEAM, Stores::EA, Stores::UBISOFT, Stores::EPIC, Stores::ROCKSTAR, Stores::BLIZZARD };
const std::string LOCAL_DATA_FILE_FILENAME = "GameStores.txt";
const std::string WHITELIST_FILE_FILENAME = "Whitelists.txt";
const std::string CUSTOM_DIRECTORY_FILE_FILENAME = "CustomDirectories.txt";
const std::string STEAMAPPS_COMMON = "\\steamapps\\common";
constexpr int NUMBER_OF_STORES = 4;
constexpr int MAX_DIRECTORY_DEPTH = 6;

struct StoresFile
{
	bool exists = false;
	int storeAmount = 0;
	int amountOfDrives = 0;
	std::vector<std::string> driveNames;
	// Layout of 2d arrays
	// [C, D, E, F, G] - drives
	// [[STEAM],[EA],[UBISOFT],[EPIC],[ROCKSTAR],[BLIZZARD]] - in each drive is each directory for each store
	std::vector<std::vector<std::string>> directoryLocationsOnDrive;
	std::vector<std::vector<std::string>> storeLocationsOnDrive;
	std::vector<std::vector<bool>> isDirectoryOnDrive;
	std::vector<std::vector<bool>> isStoreOnDrive;
	std::vector<int> numberOfDirectoriesOnDrive;
	std::vector<int> numberOfStoresOnDrive;
	std::string lastPlayed = "null";
};
struct WhitelistData
{
	std::vector<std::string> directoryNames = {};
};
struct CustomDirectoryData
{
	std::vector<std::string> steamDirectories = {};
	std::vector<std::string> eaDirectories = {};
	std::vector<std::string> ubisoftDirectories = {};
	std::vector<std::string> epicDirectories = {};
};
struct GameData
{
	std::string gameName;
	std::string gameDirectory;
	std::string gameExe;
	Stores store;
	char drive;
};

static std::string StoreToString(Stores store)
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

#endif GLOBAL_CONSTANTS_HPP