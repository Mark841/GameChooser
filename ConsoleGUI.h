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
	std::vector<std::string> GetVectorOfStringsFromUser(std::string purpose);
	std::vector<std::string> GetCustomDirectoryNames(Stores store);
	bool GetYesOrNoFromUser(std::string aboutValue);
};

#endif CONSOLE_GUI_HPP