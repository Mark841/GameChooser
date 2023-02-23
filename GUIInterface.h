#ifndef GUI_INTERFACE_HPP
#define GUI_INTERFACE_HPP

#pragma once
#include "GlobalConstants.h"
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

	virtual void NewStoresInstalledSinceLastRun() = 0;

	virtual void DisplayMainMenu() = 0;
	virtual int DisplayScanByDrive() = 0;
	virtual int DisplayFolderIdentifier() = 0;
	virtual int DisplayAllGames() = 0;
	virtual int DisplayStores() = 0;
	virtual int DisplayStoresWithSearch() = 0;

protected:
	BackEndManager* manager;
};

#endif GUI_INTERFACE_HPP