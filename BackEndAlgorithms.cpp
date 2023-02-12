#include "BackEndAlgorithms.h"

BackEndAlgorithms* BackEndAlgorithms::GetInstance()
{
    if (algorithms == NULL || algorithms == nullptr)
    {
        algorithms = new BackEndAlgorithms();
        algorithms->InitLocalDataSizes();
        return algorithms;
    }
    else
    {
        return algorithms;
    }
}

//TODO
void BackEndAlgorithms::ScanDrive(char driveName, std::vector<std::string> customSteam, std::vector<std::string> customOrigin, std::vector<std::string> customUbisoft, std::vector<std::string> customEpic)
{
    StoresFile* localData = GetLocalData();
    std::vector<char> allDrives = BackEndAlgorithms::GetDriveNames();
    int drivesIndex = 0;
    for (char drive : allDrives)
    {
        if (localData->driveNames[drivesIndex].find(drive) != std::string_view::npos)
        {
            FindStoresOnDrive(localData, drivesIndex, customSteam, customOrigin, customUbisoft, customEpic);
        }
        drivesIndex++;
    }
    // Save Data to local storage struct here

    // Save to file elsewhere

}

void BackEndAlgorithms::ScanAllDrives(std::vector<std::string> customSteam, std::vector<std::string> customOrigin, std::vector<std::string> customUbisoft, std::vector<std::string> customEpic)
{
    std::vector<char> allDrives = BackEndAlgorithms::GetDriveNames();
    for (char drive : allDrives)
    {
        ScanDrive(drive);
    }
}

std::vector<char> BackEndAlgorithms::GetDriveNames()
{
    const char* driveNames[] = { "A:","B:","C:","D:","E:","F:","G:","H:","I:","J:","K:","L:", "M:","N:","O:","P:","Q:","R:", "S:","T:","U:","V:","W:","X:","Y:", "Z:" };
    std::vector<char> pcDrives;
    DWORD drivesBitmask = GetLogicalDrives();

    for (DWORD i = 0; i < 26; i++)
    {
        // Shift 1 to a multiple of 2. 1 << 0 = 1 (0000 0001), 1 << 1 = 2 etc.
        DWORD maskIndex = 1 << i;
        if ((drivesBitmask & maskIndex) != 0)
        {
            // Drive is on pc
            std::string driveName = (std::string)driveNames[i];
            pcDrives.push_back(driveName.front());
        }
    }

	return pcDrives;
}

std::string BackEndAlgorithms::GetDriveNamesString()
{
    return GetStringFromStringArray(localFileData->driveNames);
}
std::vector<std::string> BackEndAlgorithms::GetFolderLocationsStrings()
{
    return GetStringsFrom2DStringArray(localFileData->folderLocationsOnDrive);
}
std::vector<std::string> BackEndAlgorithms::GetStoreLocationsStrings()
{
    return GetStringsFrom2DStringArray(localFileData->storeLocationsOnDrive);
}
std::vector<std::string> BackEndAlgorithms::GetIsFolderOnDriveStrings()
{
    return GetStringsFrom2DBoolArray(localFileData->isFolderOnDrive);
}
std::vector<std::string> BackEndAlgorithms::GetIsStoreOnDriveStrings()
{
    return GetStringsFrom2DBoolArray(localFileData->isStoreOnDrive);
}
std::string BackEndAlgorithms::GetNoOfFoldersOnDriveString()
{
    return GetStringFromIntArray(localFileData->numberOfFoldersOnDrive);
}
std::string BackEndAlgorithms::GetNoOfStoresOnDriveString()
{
    return GetStringFromIntArray(localFileData->numberOfStoresOnDrive);
}

//TODO MakeGeneric
std::string BackEndAlgorithms::GetStringFromIntArray(std::vector<int> intArray)
{
    std::string fileEntryLine = "";
    for (unsigned i = 0; i < intArray.size(); i++)
    {
        fileEntryLine += std::to_string(intArray[i]);
        if (i != intArray.size() - 1) {
            fileEntryLine += ",";
        }
    }
    return fileEntryLine;
}
std::string BackEndAlgorithms::GetStringFromStringArray(std::vector<std::string> stringArray)
{
    std::string fileEntryLine = "";
    for (unsigned int i = 0; i < stringArray.size(); i++)
    {
        fileEntryLine += stringArray[i];
        if (i != stringArray.size() - 1) {
            fileEntryLine += ",";
        }
    }
    return fileEntryLine;
}
std::vector<std::string> BackEndAlgorithms::GetStringsFrom2DStringArray(std::vector<std::vector<std::string>> stringArray)
{
    std::vector<std::string> fileEntries;
    std::string fileEntryLine = "";
    for(std::vector<std::string> driveString : stringArray)
    {
        fileEntryLine = "";
        for (unsigned int i = 0; i < driveString.size(); i++)
        {
            fileEntryLine += driveString[i];
            if (i != driveString.size() - 1) {
                fileEntryLine += "|";
            }
            if (i == driveString.size() - 1) {
                fileEntryLine += "?";
            }
        }
        fileEntries.push_back(fileEntryLine);
    }
    return fileEntries;
}
std::vector<std::string> BackEndAlgorithms::GetStringsFrom2DBoolArray(std::vector<std::vector<bool>> boolArray)
{
    std::vector<std::string> fileEntries;
    std::string fileEntryLine = "";
    for (std::vector<bool> driveString : boolArray)
    {
        fileEntryLine = "";
        for (unsigned int i = 0; i < driveString.size(); i++)
        {
            fileEntryLine += std::to_string(driveString[i]);
            if (i != driveString.size() - 1) {
                fileEntryLine += "|";
            }
            if (i == driveString.size() - 1) {
                fileEntryLine += "?";
            }
        }
        fileEntries.push_back(fileEntryLine);
    }
    return fileEntries;
}

void BackEndAlgorithms::InitLocalDataSizes()
{
    std::vector<char> drives = GetDriveNames();

    localFileData->storeAmount = 4;
    localFileData->amountOfDrives = drives.size();

    localFileData->driveNames.resize(localFileData->amountOfDrives);
    localFileData->numberOfStoresOnDrive.resize(localFileData->amountOfDrives);
    localFileData->numberOfFoldersOnDrive.resize(localFileData->amountOfDrives);
    localFileData->folderLocationsOnDrive.resize(localFileData->amountOfDrives);
    localFileData->storeLocationsOnDrive.resize(localFileData->amountOfDrives);
    localFileData->isFolderOnDrive.resize(localFileData->amountOfDrives);
    localFileData->isStoreOnDrive.resize(localFileData->amountOfDrives);

    for (int i = 0; i < localFileData->amountOfDrives; i++)
    {
        (localFileData->folderLocationsOnDrive[i]).resize(localFileData->storeAmount);
        (localFileData->storeLocationsOnDrive[i]).resize(localFileData->storeAmount);
        (localFileData->isFolderOnDrive[i]).resize(localFileData->storeAmount);
        (localFileData->isStoreOnDrive[i]).resize(localFileData->storeAmount);
    }
}

void BackEndAlgorithms::FindStoresOnDrive(int driveIndex, const std::vector<std::string> customSteam, const std::vector<std::string> customOrigin, const std::vector<std::string> customUbisoft, const std::vector<std::string> customEpic)
{
    return FindStoresOnDrive(localFileData, driveIndex, customSteam, customOrigin, customUbisoft, customEpic);
}
void BackEndAlgorithms::FindStoresOnDrive(StoresFile* localData, int driveIndex, std::vector<std::string> customSteam, std::vector<std::string> customOrigin, std::vector<std::string> customUbisoft, std::vector<std::string> customEpic)
{
    int* noOfStores = new int;
    *noOfStores = 0;
    int* noOfFolders = new int;
    *noOfFolders = 0;

    AllStores(localData, driveIndex, noOfStores, noOfFolders, customSteam, customOrigin, customUbisoft, customEpic);

    localData->numberOfStoresOnDrive[driveIndex] = *noOfStores;
    localData->numberOfFoldersOnDrive[driveIndex] = *noOfFolders;
}
void BackEndAlgorithms::FindStoresOnAllDrives(std::vector<std::string> customSteam, std::vector<std::string> customOrigin, std::vector<std::string> customUbisoft, std::vector<std::string> customEpic)
{
    std::vector<char> drives = GetDriveNames();

    for (int drivesIndex = 0; drivesIndex < drives.size(); drivesIndex++)
    {
        std::cout << "Scanning drive: " << drivesIndex << std::endl;
        localFileData->driveNames[drivesIndex] = drives[drivesIndex];
        FindStoresOnDrive(localFileData, drivesIndex, customSteam, customOrigin, customUbisoft, customEpic);
        std::cout << "Scanned drive: " << drivesIndex + 1 << "\n\tDrives percentage complete: " << ((drivesIndex + 1) * 100) / localFileData->amountOfDrives << std::endl;
    }

    localFileData->exists = true;
}

bool BackEndAlgorithms::SearchForStores(std::vector<std::string> steamDirectoryName, std::vector<std::string> originDirectoryName, std::vector<std::string> ubisoftDirectoryName, std::vector<std::string> epicDirectoryName, std::string* currentSearchDirectoryPath, std::string* foundSteamLocationPath, std::string* foundOriginLocationPath, std::string* foundUbisoftLocationPath, std::string* foundEpicLocationPath)
{
    if (!std::filesystem::is_directory(*currentSearchDirectoryPath))
    {
        return false;
    }

    // Creates a list to hold all sub folders
    std::vector<std::filesystem::path> subFolders;
    std::filesystem::path folder = std::filesystem::path(*currentSearchDirectoryPath);

    try
    {
        for (std::string steamName : steamDirectoryName)
        {
            if (std::filesystem::is_directory(folder) && IsSubDirectoryName(*currentSearchDirectoryPath, steamName)) // Need to check if the directory name CONTAINS store and not is directly equal to because it will have the extension at the end
            {
                *foundSteamLocationPath = std::string(folder.string());
            }
        }
        for (std::string originName : originDirectoryName)
        {
            if (std::filesystem::is_directory(folder) && IsSubDirectoryName(*currentSearchDirectoryPath, originName)) // Need to check if the directory name CONTAINS store and not is directly equal to because it will have the extension at the end
            {
                *foundOriginLocationPath = std::string(folder.string());
            }
        }
        for (std::string ubisoftName : ubisoftDirectoryName)
        {
            if (std::filesystem::is_directory(folder) && IsSubDirectoryName(*currentSearchDirectoryPath, ubisoftName)) // Need to check if the directory name CONTAINS store and not is directly equal to because it will have the extension at the end
            {
                *foundUbisoftLocationPath = std::string(folder.string());
            }
        }
        for (std::string epicName : epicDirectoryName)
        {
            if (std::filesystem::is_directory(folder) && IsSubDirectoryName(*currentSearchDirectoryPath, epicName)) // Need to check if the directory name CONTAINS store and not is directly equal to because it will have the extension at the end
            {
                *foundEpicLocationPath = std::string(folder.string());
            }
        }
        if (*foundSteamLocationPath != ""
            && *foundOriginLocationPath != ""
            && *foundUbisoftLocationPath != ""
            && *foundEpicLocationPath != "")
        {
            return true;
        }

        for (const auto& entry : std::filesystem::directory_iterator(*currentSearchDirectoryPath))
        {
            if (IsPathWhitelisted(entry.path().string()))
            {
                continue;
            }

            if (std::filesystem::is_directory(entry))
            {
                subFolders.push_back(entry.path());
            }
        }
    }

    catch (std::filesystem::filesystem_error ex)
    {
        return false;
    }

    // for each sub folder call the function again
    for (std::filesystem::path sf : subFolders)
    {
        if ((std::filesystem::status(sf).permissions() | std::filesystem::perms::others_read) == std::filesystem::status(sf).permissions())
        {
            std::string subFolder = sf.string();
            if (SearchForStores(steamDirectoryName, originDirectoryName, ubisoftDirectoryName, epicDirectoryName, &subFolder, foundSteamLocationPath, foundOriginLocationPath, foundUbisoftLocationPath, foundEpicLocationPath))
            {
                return true;
            }
        }
    }
    return false;
}

bool BackEndAlgorithms::IsPathWhitelisted(const std::string path)
{
    if (//entry.path().string() == "C://hiberfil.sys"
        // || entry.path().string() == "C://swapfile.sys"
        IsSubpath(path, "hiberfil")
        || IsSubpath(path, "swapfile")
        || IsSubpath(path, "pagefile")
        || IsSubpath(path, "DumpStack")
        || IsSubpath(path, "Adobe")
        || IsSubpath(path, "Android")
        || IsSubpath(path, "Apple")
        || IsSubpath(path, "Audio")
        //|| IsSubpath(path, "lang")
        //|| IsSubpath(path, "Languages")
        || IsSubpath(path, "MinGW")
        || IsSubpath(path, "Microsoft")
        || IsSubpath(path, "Music")
        || IsSubpath(path, "Phone")
        || IsSubpath(path, "Photos")
        || IsSubpath(path, "ProgramData")
        || IsSubpath(path, "RivaTuner")
        || IsSubpath(path, "steamapps")
        || IsSubpath(path, "temp")
        || IsSubpath(path, "Users")
        || IsSubpath(path, "Videos")
        || IsSubpath(path, "Windows")
        || IsSubpath(path, "WinREAgent")
        || IsSubpath(path, "$Recycle.Bin"))
    {
        return true;
    }
    return false;
}

// Code gotten from - https://stackoverflow.com/questions/62503197/check-if-path-contains-another-in-c
bool BackEndAlgorithms::IsSubpath(const std::filesystem::path& path, const std::filesystem::path& base) {
    const auto mismatch_pair = std::mismatch(path.begin(), path.end(), base.begin(), base.end());
    return mismatch_pair.second == base.end();
}
bool BackEndAlgorithms::IsSubpath(const std::string path, const std::string subpath)
{
    return path.find(subpath) != std::string_view::npos;
}
bool BackEndAlgorithms::IsSubDirectoryName(const std::string directory, const std::string subdirectory)
{
    int index = directory.length() - (subdirectory.length() + 1);
    if (index < 0)
    {
        return false;
    }

    return directory.substr(index)._Equal("\\" + subdirectory);
}

void BackEndAlgorithms::AllStores(StoresFile* localData, int driveIndex, int* noOfStores, int* noOfFolders, const std::vector<std::string> customSteam, const std::vector<std::string> customOrigin, const std::vector<std::string> customUbisoft, const std::vector<std::string> customEpic)
{
    std::string* drive = &(localData->driveNames[driveIndex]);
    std::vector<std::string> steamFolders;
    steamFolders.push_back("Steam");
    steamFolders.push_back("SteamLibrary");
    steamFolders.insert(steamFolders.end(), customSteam.begin(), customSteam.end());
    std::vector<std::string> originFolders;
    originFolders.push_back("Origin");
    originFolders.push_back("Origin Games");
    originFolders.insert(originFolders.end(), customOrigin.begin(), customOrigin.end());
    std::vector<std::string> ubisoftFolders;
    ubisoftFolders.push_back("Ubisoft");
    ubisoftFolders.insert(ubisoftFolders.end(), customUbisoft.begin(), customUbisoft.end());
    std::vector<std::string> epicFolders;
    epicFolders.push_back("Epic Games");
    epicFolders.push_back("Epic");
    epicFolders.insert(epicFolders.end(), customEpic.begin(), customEpic.end());
    std::string* currentSearchDirectoryPath = new std::string(*drive + ":\\");
    std::string* steamFoundLocation = new std::string("");
    std::string* originFoundLocation = new std::string("");
    std::string* ubisoftFoundLocation = new std::string("");
    std::string* epicFoundLocation = new std::string("");

    SearchForStores(steamFolders, originFolders, ubisoftFolders, epicFolders, currentSearchDirectoryPath, steamFoundLocation, originFoundLocation, ubisoftFoundLocation, epicFoundLocation);

    // Steam -------------------------------------------------------------------------------------------------
    if (*steamFoundLocation != "") {
        localData->folderLocationsOnDrive[driveIndex][0] = *steamFoundLocation;
        localData->isFolderOnDrive[driveIndex][0] = true;
        (*noOfFolders)++;
    }
    if (std::filesystem::exists(*steamFoundLocation + "\\Steam.exe")) {
        localData->storeLocationsOnDrive[driveIndex][0] = *steamFoundLocation;
        localData->isStoreOnDrive[driveIndex][0] = true;
        (*noOfStores)++;
    }
    // Origin ------------------------------------------------------------------------------------------------
    if (*originFoundLocation != "") {
        localData->folderLocationsOnDrive[driveIndex][1] = *originFoundLocation;
        localData->isFolderOnDrive[driveIndex][1] = true;
        (*noOfFolders)++;
    }
    if (std::filesystem::exists(*originFoundLocation + "\\Origin.exe")) {
        localData->storeLocationsOnDrive[driveIndex][1] = *originFoundLocation;
        localData->isStoreOnDrive[driveIndex][1] = true;
        (*noOfStores)++;
    }
    // Ubisoft -----------------------------------------------------------------------------------------------
    if (*ubisoftFoundLocation != "") {
        localData->folderLocationsOnDrive[driveIndex][2] = *ubisoftFoundLocation;
        localData->isFolderOnDrive[driveIndex][2] = true;
        (*noOfFolders)++;
    }
    if (std::filesystem::exists(*ubisoftFoundLocation + "\\Ubisoft Game Launcher\\UbisoftGameLauncher.exe")) {
        localData->storeLocationsOnDrive[driveIndex][3] = *ubisoftFoundLocation + "\\Ubisoft Game Launcher";
        localData->isStoreOnDrive[driveIndex][2] = true;
        (*noOfStores)++;
    }
    // Epic --------------------------------------------------------------------------------------------------
    if (*epicFoundLocation != "") {
        localData->folderLocationsOnDrive[driveIndex][3] = *epicFoundLocation;
        localData->isFolderOnDrive[driveIndex][3] = true;
        (*noOfFolders)++;
    }
    //if (std::filesystem::exists(*epicFoundLocation + "\\Launcher\\Engine\\Binaries\\Win64\\EpicGamesLauncher.exe")) {
    if (std::filesystem::exists(*epicFoundLocation + "\\Launcher\\Portal\\Binaries\\Win64\\EpicGamesLauncher.exe")) {
        localData->storeLocationsOnDrive[driveIndex][3] = *epicFoundLocation + "\\Launcher\\Engine\\Binaries\\Win64";
        localData->isStoreOnDrive[driveIndex][3] = true;
        (*noOfStores)++;
    }

    delete currentSearchDirectoryPath;
    delete steamFoundLocation;
    delete originFoundLocation;
    delete ubisoftFoundLocation;
    delete epicFoundLocation;
}
