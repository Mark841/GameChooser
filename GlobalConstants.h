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

#endif GLOBAL_CONSTANTS_HPP