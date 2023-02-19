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

	void ScanDrive(char driveName, std::vector<std::string> customSteam, std::vector<std::string> customOrigin, std::vector<std::string> customUbisoft, std::vector<std::string> customEpic) {
		algorithms->ScanDrive(driveName, customSteam, customOrigin, customUbisoft, customEpic);
		fileHandler->WriteLocalDataToFileOverwrite();
	}
	void ScanAllDrives(std::vector<std::string> customSteam, std::vector<std::string> customOrigin, std::vector<std::string> customUbisoft, std::vector<std::string> customEpic) {
		algorithms->ScanAllDrives(customSteam, customOrigin, customUbisoft, customEpic);
		fileHandler->WriteLocalDataToFileOverwrite();
	}

	FileManager* GetFileManagerHandler() { return fileHandler; }
	BackEndAlgorithms* GetAlgorithmsHandler() { return algorithms; }

protected:
	FileManager* fileHandler = nullptr;
	BackEndAlgorithms* algorithms = nullptr;
};