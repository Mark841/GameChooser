#pragma once
#include "BackEndAlgorithms.h"
#include "FileManager.h"

class GUIInterface abstract
{
public:
	GUIInterface() {
		fileHandler = new FileManager("GameStores.txt");
		algorithms = BackEndAlgorithms::GetInstance();

		if (!algorithms->GetLocalData()->exists)
		{
			algorithms->InitLocalDataSizes();
			algorithms->FindStoresOnAllDrives();
			fileHandler->WriteLocalDataToFileOverwrite();
		}
	}
	~GUIInterface() {
		delete fileHandler;
		delete algorithms;
	}

	virtual void DisplayMainMenu() = 0;
	virtual int DisplayScanByDrive() = 0;
	virtual int DisplayFolderIdentifier() = 0;
	virtual int DisplayAllGames() = 0;
	virtual int DisplayStores() = 0;
	virtual int DisplayStoresWithSearch() = 0;

protected:
	FileManager* fileHandler = nullptr;
	BackEndAlgorithms* algorithms = nullptr;
};