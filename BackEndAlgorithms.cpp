#include "BackEndAlgorithms.h"

BackEndAlgorithms* BackEndAlgorithms::GetInstance()
{
    if (algorithms == NULL || algorithms == nullptr)
    {
        algorithms = new BackEndAlgorithms();
        return algorithms;
    }
    else
    {
        return algorithms;
    }
}

//TODO
void BackEndAlgorithms::ScanDrive(char driveName)
{
    StoresFile* localData = GetLocalData();
    std::vector<char> allDrives = BackEndAlgorithms::GetDriveNames();
    int drivesIndex = 0;
    for (char drive : allDrives)
    {
        if (localData->driveNames[drivesIndex].find(drive) != std::string_view::npos)
        {
            FindStoresOnDrive(localData, drivesIndex);
        }
        drivesIndex++;
    }
    // Save Data to local storage struct here

    // Save to file elsewhere

}

void BackEndAlgorithms::ScanAllDrives()
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

void BackEndAlgorithms::FindStoresOnAllDrivesNoLocalData()
{
    std::vector<char> drives = GetDriveNames();

    localFileData->amountOfDrives = drives.size();
    localFileData->driveNames.resize(drives.size());
    localFileData->numberOfStoresOnDrive.resize(drives.size());
    localFileData->numberOfFoldersOnDrive.resize(drives.size());
    localFileData->folderLocationsOnDrive.resize(drives.size());
    localFileData->storeLocationsOnDrive.resize(drives.size());
    localFileData->isFolderOnDrive.resize(drives.size());
    localFileData->isStoreOnDrive.resize(drives.size());

    for (int drivesIndex = 0; drivesIndex < drives.size(); drivesIndex++)
    {
        localFileData->driveNames[drivesIndex] = drives[drivesIndex];
        FindStoresOnDrive(localFileData, drivesIndex);
    }

    localFileData->exists = true;
}

//TODO - Is it needed
void BackEndAlgorithms::FindStoresOnAllDrives()
{
    StoresFile* localData = GetLocalData();

    for (int drivesIndex = 0; drivesIndex < localData->amountOfDrives; drivesIndex++) 
    {
        FindStoresOnDrive(localData, drivesIndex);
    }
}
void BackEndAlgorithms::FindStoresOnDrive(StoresFile* localData, int driveIndex)
{
    int* noOfStores = new int;
    *noOfStores = 0;
    int* noOfFolders = new int;
    *noOfFolders = 0;

    SteamStore(localData, driveIndex, noOfStores, noOfFolders);
    OriginStore(localData, driveIndex, noOfStores, noOfFolders);
    UbisoftStore(localData, driveIndex, noOfStores, noOfFolders);
    EpicStore(localData, driveIndex, noOfStores, noOfFolders);
    //TODO
    //BlizzardStore(localData, drivesIndex, noOfStores, noOfFolders);
    //RockstarStore(localData, drivesIndex, noOfStores, noOfFolders);

    localData->numberOfStoresOnDrive[driveIndex] = *noOfStores;
    localData->numberOfFoldersOnDrive[driveIndex] = *noOfFolders;
}

//TODO
void BackEndAlgorithms::FindStore(std::string store, std::string* location)
{
    if (!std::filesystem::is_directory(*location))
    {
        return;
    }

    // Creates a list to hold all sub folders
    std::vector<std::filesystem::path> subFolders;
    std::filesystem::path folder = std::filesystem::path(*location);

    //std::cout << *location << std::endl;
    try
    {
        for (const auto& entry : std::filesystem::directory_iterator(*location))
        {
            if (IsPathWhitelisted(entry.path().string()))
            {
                continue;
            }

            // -----------------------------------------------------------------------------------
            std::cout << entry.path() << std::endl;
            // -----------------------------------------------------------------------------------

            if (std::filesystem::is_directory(entry))
            {
                subFolders.push_back(entry.path());
            }
            // checks if the store was found and 'else if' because don't want to say it's found if it was a subfolder
            // -----------------------------------------------------------------------------------
            // NEED A METHOD TO GET THE ACTUAL FILE NAME FROM entry.path()
            else if (entry.path().string().find(store) != std::string_view::npos) // Need to cehck if the filename CONTAINS store and not is directly equal to because it will have the extension at the end
            {
                *location += "\\" + entry.path().string();
                return;
            }
            // -----------------------------------------------------------------------------------
        }

        // for each sub folder
        for (std::filesystem::path sf : subFolders) {
            // call the function again
            std::string subFolder = sf.string();
            FindStore(store, &subFolder);
        }
        return;
    }
    catch (std::filesystem::filesystem_error ex)
    {
        return;
    }
}

bool BackEndAlgorithms::IsPathWhitelisted(const std::string path)
{
    if (//entry.path().string() == "C://hiberfil.sys"
        // || entry.path().string() == "C://swapfile.sys"
        IsSubpath(path, "hiberfil.sys")
        || IsSubpath(path, "swapfile.sys")
        || IsSubpath(path, "Adobe")
        || IsSubpath(path, "Android")
        || IsSubpath(path, "Apple")
        || IsSubpath(path, "MinGW")
        || IsSubpath(path, "Microsoft")
        || IsSubpath(path, "ProgramData")
        || IsSubpath(path, "temp")
        || IsSubpath(path, "Users")
        || IsSubpath(path, "Windows")
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

// -----------------------------------------------------------------------------------

// TODO - Add in functionality where it can get passed in a vector of strings which are user specified folder names where the file can be found at
           
// -----------------------------------------------------------------------------------

void BackEndAlgorithms::SteamStore(StoresFile* localData, int driveIndex, int* noOfStores, int* noOfFolders)
{
    std::string* drive = &(localData->driveNames[driveIndex]);
    std::string* location = new std::string(*drive + "://");

    FindStore("Steam", location);
    if (*location == "")
    {
        FindStore("SteamLibrary", location);
    }

    if (*location != "") {
        localData->folderLocationsOnDrive[driveIndex][0] = *location;
        localData->isFolderOnDrive[driveIndex][0] = true;
        (*noOfFolders)++;
    }
    if (std::filesystem::exists(*location + "\\Steam.exe")) {
        localData->storeLocationsOnDrive[driveIndex][0] = *location;
        localData->isStoreOnDrive[driveIndex][0] = true;
        (*noOfStores)++;
    }
}
void BackEndAlgorithms::OriginStore(StoresFile* localData, int driveIndex, int* noOfStores, int* noOfFolders)
{
    std::string* drive = &(localData->driveNames[driveIndex]);
    std::string* location = new std::string(*drive + "://");

    FindStore("Origin", location);
    if (std::filesystem::exists(*location + "\\Origin.exe")) {
        localData->storeLocationsOnDrive[driveIndex][1] = *location;
        localData->isStoreOnDrive[driveIndex][1] = true;
        (*noOfStores)++;
    }
    else if (*location != "") {
        localData->folderLocationsOnDrive[driveIndex][1] = *location;
        localData->isFolderOnDrive[driveIndex][1] = true;
        (*noOfFolders)++;
    }
    *location = *drive + "://";
    FindStore("Origin Games", location);
    if (*location != "") {
        localData->folderLocationsOnDrive[driveIndex][1] = *location;
        localData->isFolderOnDrive[driveIndex][1] = true;
        (*noOfFolders)++;
    }
}
void BackEndAlgorithms::UbisoftStore(StoresFile* localData, int driveIndex, int* noOfStores, int* noOfFolders)
{
    std::string* drive = &(localData->driveNames[driveIndex]);
    std::string* location = new std::string(*drive + "://");

    FindStore("Ubisoft", location);
    if (*location != "") {
        localData->folderLocationsOnDrive[driveIndex][2] = *location;
        localData->isFolderOnDrive[driveIndex][2] = true;
        (*noOfFolders)++;
    }
    if (std::filesystem::exists(*location + "\\Ubisoft Game Launcher\\UbisoftGameLauncher.exe")) {
        localData->storeLocationsOnDrive[driveIndex][3] = *location + "\\Ubisoft Game Launcher";
        localData->isStoreOnDrive[driveIndex][2] = true;
        (*noOfStores)++;
    }
    delete location;
}
void BackEndAlgorithms::EpicStore(StoresFile* localData, int driveIndex, int* noOfStores, int* noOfFolders)
{
    std::string* drive = &(localData->driveNames[driveIndex]);
    std::string* location = new std::string(*drive + "://");

    FindStore("Epic Games", location);
    if (*location != "") {
        localData->folderLocationsOnDrive[driveIndex][3] = *location;
        localData->isFolderOnDrive[driveIndex][3] = true;
        (*noOfFolders)++;
    }
    if (std::filesystem::exists(*location + "\\Launcher\\Engine\\Binaries\\Win64\\EpicGamesLauncher.exe")) {
        localData->storeLocationsOnDrive[driveIndex][3] = *location + "\\Launcher\\Engine\\Binaries\\Win64";
        localData->isStoreOnDrive[driveIndex][3] = true;
        (*noOfStores)++;
    }
    delete location;
}

//TODO
//void BackEndAlgorithms::BlizzardStore( StoresFile* localData, int driveIndex, int* noOfStores, int* noOfFolders)
//{
//}
