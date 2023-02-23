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
			algorithms->FindStoresOnAllDrives();
			fileHandler->WriteLocalDataToFileOverwrite();
		}
	}
	~BackEndManager() {
		delete fileHandler;
		delete algorithms;
	}

	//TODO - remove all custom vectors and make the method use the customData struct
	void ScanDrive(char driveName, std::vector<std::string> customSteam, std::vector<std::string> customOrigin, std::vector<std::string> customUbisoft, std::vector<std::string> customEpic) {
		algorithms->ScanDrive(driveName, customSteam, customOrigin, customUbisoft, customEpic);
		fileHandler->WriteLocalDataToFileOverwrite();
	}
	//TODO - remove all custom vectors and make the method use the customData struct
	void ScanAllDrives(std::vector<std::string> customSteam, std::vector<std::string> customOrigin, std::vector<std::string> customUbisoft, std::vector<std::string> customEpic) {
		algorithms->ScanAllDrives(customSteam, customOrigin, customUbisoft, customEpic);
		fileHandler->WriteLocalDataToFileOverwrite();
	}

	inline FileManager* GetFileManagerHandler() { return fileHandler; }
	inline BackEndAlgorithms* GetAlgorithmsHandler() { return algorithms; }

protected:
	FileManager* fileHandler = nullptr;
	BackEndAlgorithms* algorithms = nullptr;
};

#endif BACKEND_MANAGER_HPP