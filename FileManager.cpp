#include "FileManager.h"

FileManager::FileManager(const string fileName, int opening_mode)
{
	if (opening_mode == 1)
		dataFile.open(fileName.c_str(), ios::out | ios::in | dataFile.app);
	else if (opening_mode == 2)
		dataFile.open(fileName.c_str(), ios::out | ios::trunc);

	if (dataFile.fail())
		throw invalid_argument("no file exists or was able to be created" + fileName);
	
	//if (dataFile.fail())
	//{
	//	TCHAR buffer[MAX_PATH] = { 0 };
	//	GetModuleFileName(NULL, buffer, MAX_PATH);
	//	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");

	//	// Convert from wstring to string
	//	using convert_type = std::codecvt_utf8<wchar_t>;
	//	std::wstring_convert<convert_type, wchar_t> converter;
	//	std::string currentDirectory = converter.to_bytes(std::wstring(buffer).substr(0, pos));
	//}
}
FileManager::~FileManager()
{
	dataFile.close();
}