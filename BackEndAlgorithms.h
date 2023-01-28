#pragma once
#include "windows.h"
#include "fileapi.h"
#include <string>
#include <vector>

class BackEndAlgorithms
{
public:
	static void ScanDrive(char driveName);
	static void ScanAllDrives();

	static std::vector<char> GetDriveNames();
};