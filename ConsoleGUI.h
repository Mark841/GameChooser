#ifndef CONSOLE_GUI_HPP
#define CONSOLE_GUI_HPP

#pragma once
#include "GUIInterface.h"
#include <iostream>

class ConsoleGUI : GUIInterface
{
public:
	ConsoleGUI();
	~ConsoleGUI();
	
	void NewStoresInstalledSinceLastRun();

	void DisplayMainMenu();
	int DisplayScanByDrive();
	int DisplayFolderIdentifier();
	int DisplayRandomGame();
	int DisplayAllGames();
	int DisplayStores();
	int DisplayStoresWithSearch();

private:
	std::vector<std::string> GetVectorOfStringsFromUser(const std::string purpose) const;
	std::string GetStringFromUser() const;
	std::vector<std::string> GetCustomDirectoryNames(const Stores store) const;
	bool GetYesOrNoFromUser(const std::string aboutValue) const;
};

#endif CONSOLE_GUI_HPP