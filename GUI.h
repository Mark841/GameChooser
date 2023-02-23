#ifndef GUI_HPP
#define	GUI_HPP

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

#endif GUI_HPP