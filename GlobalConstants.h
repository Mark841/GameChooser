#ifndef GLOBAL_CONSTANTS_HPP
#define GLOBAL_CONSTANTS_HPP

#pragma once
#include "StorageStructures.h"

const std::vector<std::string> STORE_NAMES = { "Steam", "EA", "Ubisoft", "Epic", "Rockstar", "Blizzard"};
const std::vector<std::string> STORE_NAMES_UPPER = { "STEAM", "EA", "UBISOFT", "EPIC", "ROCKSTAR", "BLIZZARD"};
const std::vector<Stores> STORE_ENUMS = { Stores::STEAM, Stores::EA, Stores::UBISOFT, Stores::EPIC, Stores::ROCKSTAR, Stores::BLIZZARD };
const std::string LOCAL_DATA_FILE_FILENAME = "GameStores.txt";
const std::string WHITELIST_FILE_FILENAME = "Whitelists.txt";
const std::string CUSTOM_DIRECTORY_FILE_FILENAME = "CustomDirectories.txt";
const std::string LAST_PLAYED_GAME_FILE_FILENAME = "LastPlayedGameData.txt";
const std::string STEAMAPPS_COMMON = "\\steamapps\\common";

const std::string STEAM_SEARCH_URL = "https://store.steampowered.com/search/?term=";
//const std::string ORIGIN_SEARCH_URL = "https://www.origin.com/gbr/en-us/search?searchString=";
const std::string UBISOFT_SEARCH_URL_BEGIN = "https://store.ubi.com/uk/search?q=";
const std::string UBISOFT_SEARCH_URL_END = "&prefn1=productTypeRefinementString&prefv1=games";
const std::string EPIC_SEARCH_URL_BEGIN = "https://store.epicgames.com/en-US/browse?q=";
const std::string EPIC_SEARCH_URL_END = "&sortBy=relevancy&sortDir=DESC&count=40";

constexpr int NUMBER_OF_STORES = 4;
constexpr int MAX_DIRECTORY_DEPTH = 6;
constexpr int MAX_GAME_DIRECTORY_DEPTH = 8;

const int STEAM_INDEX = 0;
const int EA_INDEX = 1;
const int UBISOFT_INDEX = 2;
const int EPIC_INDEX = 3;


#endif GLOBAL_CONSTANTS_HPP