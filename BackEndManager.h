#pragma once
#include "BackEndAlgorithms.h"
#include "FileManager.h"

class BackEndManager
{
public:
	BackEndManager() {
		fileHandler = new FileManager("GameStores.txt");
		algorithms = BackEndAlgorithms::GetInstance();

		if (!algorithms->GetLocalData()->exists)
		{
			algorithms->InitLocalDataSizes();
			algorithms->FindStoresOnAllDrives();
			fileHandler->WriteLocalDataToFileOverwrite();
		}
	}
	~BackEndManager() {
		delete fileHandler;
		delete algorithms;
	}

	FileManager* GetFileManagerHandler() { return fileHandler; }
	BackEndAlgorithms* GetAlgorithmsHandler() { return algorithms; }

protected:
	FileManager* fileHandler = nullptr;
	BackEndAlgorithms* algorithms = nullptr;
};