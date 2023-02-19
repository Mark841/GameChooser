#pragma once
#include "BackEndManager.h"

class GUIInterface abstract
{
public:
	GUIInterface() {
		manager = new BackEndManager();
	}
	~GUIInterface() {
		delete manager;
	}

	virtual void DisplayMainMenu() = 0;
	virtual int DisplayScanByDrive() = 0;
	virtual int DisplayFolderIdentifier() = 0;
	virtual int DisplayAllGames() = 0;
	virtual int DisplayStores() = 0;
	virtual int DisplayStoresWithSearch() = 0;

protected:
	BackEndManager* manager;
};