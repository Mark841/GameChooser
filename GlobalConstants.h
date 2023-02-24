#ifndef GLOBAL_CONSTANTS_HPP
#define GLOBAL_CONSTANTS_HPP

#pragma once
#include <string>
#include <vector>

const std::vector<std::string> STORE_NAMES = { "Steam", "Origin", "Ubisoft", "Epic" };
const std::string LOCAL_DATA_FILE_FILENAME = "GameStores.txt";
const std::string WHITELIST_FILE_FILENAME = "Whitelists.txt";
const std::string CUSTOM_DIRECTORY_FILE_FILENAME = "CustomDirectories.txt";
const std::string STEAMAPPS_COMMON = "\\steamapps\\common";
constexpr int NUMBER_OF_STORES = 4;
constexpr int MAX_DIRECTORY_DEPTH = 6;

enum class Stores
{
	STEAM,
	ORIGIN,
	UBISOFT,
	EPIC
};
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
struct WhitelistData
{
	std::vector<std::string> directoryNames = {};
};
struct CustomDirectoryData
{
	std::vector<std::string> steamDirectories = {};
	std::vector<std::string> originDirectories = {};
	std::vector<std::string> ubisoftDirectories = {};
	std::vector<std::string> epicDirectories = {};
};

static std::string StoreToString(Stores store)
{
	switch (store)
	{
	case Stores::STEAM: return "STEAM";
	case Stores::ORIGIN: return "ORIGIN";
	case Stores::UBISOFT: return "UBISOFT";
	case Stores::EPIC: return "EPIC";
	default:
		return "NOT VALID STORE";
	}
}

#endif GLOBAL_CONSTANTS_HPP