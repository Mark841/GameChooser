#pragma once
#include "GUIInterface.h"

class GUI : GUIInterface
{
public:
	GUI();
	~GUI();

	void NewStoresInstalledSinceLastRun();

	void DisplayMainMenu();
	int DisplayScanByDrive();
	int DisplayFolderIdentifier();
	int DisplayAllGames();
	int DisplayStores();
	int DisplayStoresWithSearch();
};