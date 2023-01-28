#pragma once
#include "AppendToFile.h"
#include "WriteToFile.h"

class GUIInterface abstract
{
public:
	GUIInterface() { fileHandler = new AppendToFile("GameStores.txt"); }
	~GUIInterface() { delete fileHandler; }

	void SwapFileHandlerModeToAppend() { delete fileHandler;  fileHandler = new AppendToFile("GameStores.txt"); }
	void SwapFileHandlerModeToWrite() { delete fileHandler;  fileHandler = new WriteToFile("GameStores.txt"); }

	virtual void DisplayMainMenu() = 0;
	virtual int DisplayScanByDrive() = 0;
	virtual int DisplayFolderIdentifier() = 0;
	virtual int DisplayAllGames() = 0;
	virtual int DisplayStores() = 0;
	virtual int DisplayStoresWithSearch() = 0;

private:
	FileManager* fileHandler;
};