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
		backEndAlgorithms = BackEndAlgorithms::GetInstance();

		if (!backEndAlgorithms->GetLocalData()->exists)
		{
			backEndAlgorithms->InitLocalDataSizes();
			backEndAlgorithms->ScanAllDrivesInitial();
			fileHandler->WriteLocalDataToFileOverwrite();
			askToRescanOnStartup = false;
		}
		backEndAlgorithms->GetAllGamesFromFolders();
	}
	~BackEndManager() {
		delete fileHandler;
		delete backEndAlgorithms;
	}

	void ScanDrive(char driveName) {
		backEndAlgorithms->ScanDrive(driveName);
		fileHandler->WriteLocalDataToFileOverwrite();
		backEndAlgorithms->GetAllGamesFromFolders();
	}
	void ScanAllDrives() {
		backEndAlgorithms->ScanAllDrives();
		fileHandler->WriteLocalDataToFileOverwrite();
		backEndAlgorithms->GetAllGamesFromFolders();
	}

	void SetLastPlayedGame(const GameData& game)
	{
		*(backEndAlgorithms->GetLastPlayedGameData()) = game;
		fileHandler->WriteLastPlayedGameToFileOverwrite(game);
	}

	inline FileManager* GetFileManagerHandler() { return fileHandler; }
	inline BackEndAlgorithms* GetAlgorithmsHandler() { return backEndAlgorithms; }
	inline bool GetAskToRescanOnStartup() { return askToRescanOnStartup; }

protected:
	bool askToRescanOnStartup = true;
	FileManager* fileHandler = nullptr;
	BackEndAlgorithms* backEndAlgorithms = nullptr;
};

#endif BACKEND_MANAGER_HPP