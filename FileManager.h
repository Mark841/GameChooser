#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#pragma once
#include "GlobalConstants.h"
#include "BackEndAlgorithms.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

class FileManager
{
public:
	FileManager(const std::string fileName);
	~FileManager();
	void WriteLocalDataToFileOverwrite();
	void WriteLocalDataToFileAppend();
	void WriteWhitelistsToFileAppend();
	void WriteWhitelistsToFileOverwrite();
	void WriteCustomDirectoriesToFileOverwrite();
	void WriteLastPlayedGameToFileOverwrite(GameData game);

	void ReadLocalDataFromFile();
	void ReadWhitelistDataFromFile();
	void ReadCustomDirectoriesDataFromFile();
	void ReadLastPlayedGameFromFile();

private:
	int ProcessFileLineInt(std::string value);
	std::vector<std::string> ProcessFileLineStringVector(std::string value);
	std::vector<int> ProcessFileLineIntVector(std::string value);
	std::vector<bool> ProcessFileLineBoolVector(std::string value);

	void WriteToFile(std::fstream* file, std::vector<std::string> lines);
	void WriteToFile(std::fstream* file, std::vector<std::vector<std::string>> lines);
	void WriteToFile(std::ofstream* file, std::vector<std::string> lines);
	void WriteToFile(std::ofstream* file, std::vector<std::vector<std::string>> lines);
	std::vector<std::string> ReadLinesFromFile(std::fstream* file);

	void WriteDefaultWhitelistsToFile(std::fstream* file);
	void WriteDefaultWhitelistsToFile(std::ofstream* file);
	void WriteDefaultDirectoriesToFile(std::fstream* file);
};

#endif FILE_MANAGER_HPP