#pragma once
#include "GUIInterface.h"

class ConsoleGUI : GUIInterface
{
public:
	ConsoleGUI();
	~ConsoleGUI();

	void DisplayMainMenu();
	int DisplayScanByDrive();
	int DisplayFolderIdentifier();
	int DisplayAllGames();
	int DisplayStores();
	int DisplayStoresWithSearch();
};