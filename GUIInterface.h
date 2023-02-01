#pragma once
#include "AppendToFile.h"
#include "WriteToFile.h"
#include "BackEndAlgorithms.h"

enum class handlerType
{
	APPEND,
	WRITE
};

class GUIInterface abstract
{
public:
	GUIInterface() {
		fileHandler = new AppendToFile("GameStores.txt");
		fileHandlerAppend = static_cast<AppendToFile*>(fileHandler);
		fileHandlerAppend->LoadDataFromFile();
		algorithms = BackEndAlgorithms::GetInstance();
		if (!algorithms->GetLocalData()->exists) algorithms->FindStoresOnAllDrivesNoLocalData();
	}
	~GUIInterface() {
		delete fileHandler;
		delete algorithms;
	}

	void SwapFileHandlerModeToAppend() { delete fileHandler;  fileHandler = new AppendToFile("GameStores.txt"); }
	void SwapFileHandlerModeToWrite() { delete fileHandler;  fileHandler = new WriteToFile("GameStores.txt"); }

	virtual void DisplayMainMenu() = 0;
	virtual int DisplayScanByDrive() = 0;
	virtual int DisplayFolderIdentifier() = 0;
	virtual int DisplayAllGames() = 0;
	virtual int DisplayStores() = 0;
	virtual int DisplayStoresWithSearch() = 0;

	handlerType currentFileHandlerMode = handlerType::APPEND;

protected:
	FileManager* fileHandler = nullptr;
	AppendToFile* fileHandlerAppend = nullptr;
	WriteToFile* fileHandlerWriter = nullptr;
	BackEndAlgorithms* algorithms = nullptr;
};