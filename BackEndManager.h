#ifndef BACKEND_MANAGER_HPP
#define	BACKEND_MANAGER_HPP

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
			algorithms->ScanAllDrivesInitial();
			fileHandler->WriteLocalDataToFileOverwrite();
		}
		algorithms->GetAllGamesFromFolders();
	}
	~BackEndManager() {
		delete fileHandler;
		delete algorithms;
	}

	void ScanDrive(char driveName) {
		algorithms->ScanDrive(driveName);
		fileHandler->WriteLocalDataToFileOverwrite();
		algorithms->GetAllGamesFromFolders();
	}
	void ScanAllDrives() {
		algorithms->ScanAllDrives();
		fileHandler->WriteLocalDataToFileOverwrite();
		algorithms->GetAllGamesFromFolders();
	}

	inline FileManager* GetFileManagerHandler() { return fileHandler; }
	inline BackEndAlgorithms* GetAlgorithmsHandler() { return algorithms; }

protected:
	FileManager* fileHandler = nullptr;
	BackEndAlgorithms* algorithms = nullptr;
};

#endif BACKEND_MANAGER_HPP