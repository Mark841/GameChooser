#include "BackEndAlgorithms.h"

// --------------------------- Public ---------------------------------------------------------------------------------------------------------------------------------------

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

void BackEndAlgorithms::InitLocalDataSizes()
{
    std::vector<char> drives = GetDriveNames();

    localFileData->storeAmount = NUMBER_OF_STORES;
    localFileData->amountOfDrives = drives.size();

    localFileData->driveNames.resize(localFileData->amountOfDrives);
    localFileData->numberOfStoresOnDrive.resize(localFileData->amountOfDrives);
    localFileData->numberOfDirectoriesOnDrive.resize(localFileData->amountOfDrives);
    localFileData->directoryLocationsOnDrive.resize(localFileData->amountOfDrives);
    localFileData->storeLocationsOnDrive.resize(localFileData->amountOfDrives);
    localFileData->isDirectoryOnDrive.resize(localFileData->amountOfDrives);
    localFileData->isStoreOnDrive.resize(localFileData->amountOfDrives);

    for (int i = 0; i < localFileData->amountOfDrives; i++)
    {
        (localFileData->directoryLocationsOnDrive[i]).resize(localFileData->storeAmount);
        (localFileData->storeLocationsOnDrive[i]).resize(localFileData->storeAmount);
        (localFileData->isDirectoryOnDrive[i]).resize(localFileData->storeAmount);
        (localFileData->isStoreOnDrive[i]).resize(localFileData->storeAmount);
    }
}

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
}
void BackEndAlgorithms::ScanAllDrives()
{
    std::vector<char> allDrives = BackEndAlgorithms::GetDriveNames();
    int driveIndex = 0;
    for (char drive : allDrives)
    {
        driveIndex++;
        std::cout << "Scanning drive: " << driveIndex << std::endl;
        ScanDrive(drive);
        std::cout << "Scanned drive: " << driveIndex << "\n\tDrives percentage complete: " << (driveIndex * 100) / localFileData->amountOfDrives << std::endl;
    }

    localFileData->exists = true;
}

bool BackEndAlgorithms::IsStringNullOrWhitespace(std::string string)
{
    if (string == "" || string == "null" || string == "NULL")
    {
        return true;
    }
    return false;
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
    return GetStringsFrom2DStringArray(localFileData->directoryLocationsOnDrive);
}
std::vector<std::string> BackEndAlgorithms::GetStoreLocationsStrings()
{
    return GetStringsFrom2DStringArray(localFileData->storeLocationsOnDrive);
}
std::vector<std::string> BackEndAlgorithms::GetIsFolderOnDriveStrings()
{
    return GetStringsFrom2DBoolArray(localFileData->isDirectoryOnDrive);
}
std::vector<std::string> BackEndAlgorithms::GetIsStoreOnDriveStrings()
{
    return GetStringsFrom2DBoolArray(localFileData->isStoreOnDrive);
}
std::string BackEndAlgorithms::GetNoOfFoldersOnDriveString()
{
    return GetStringFromIntArray(localFileData->numberOfDirectoriesOnDrive);
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
            fileEntryLine += "|";
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
            fileEntryLine += "|";
        }
    }
    return fileEntryLine;
}
std::vector<std::string> BackEndAlgorithms::GetStringsFrom2DStringArray(std::vector<std::vector<std::string>> stringArray)
{
    std::vector<std::string> fileEntries;
    std::string fileEntryLine = "";
    for (std::vector<std::string> driveString : stringArray)
    {
        fileEntryLine = "";
        for (unsigned int i = 0; i < driveString.size(); i++)
        {
            fileEntryLine += driveString[i];
            if (i != driveString.size() - 1) {
                fileEntryLine += "|";
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
        }
        fileEntries.push_back(fileEntryLine);
    }
    return fileEntries;
}

//TODO - Can optimise by making a seperate method for each drive
void BackEndAlgorithms::GetAllGamesFromFolders()
{
    int driveIndex = 0;
    int storeIndex = 0;
    for (std::vector<std::string> drive : localFileData->directoryLocationsOnDrive)
    {
        std::string driveName = localFileData->driveNames[driveIndex];
        for (std::string store : drive)
        {
            std::vector<std::filesystem::path> subDirectories;
            if (!IsStringNullOrWhitespace(store))
            {
                for (const auto& entry : std::filesystem::directory_iterator(store))
                {
                    if (std::filesystem::is_directory(entry))
                    {
                        subDirectories.push_back(entry.path());
                    }
                }
            }
            // For each game in storeFolder
            for (std::filesystem::path sf : subDirectories)
            {
                std::string gameDirectory = sf.string();
                // If its trying to search something that isn't a directory AND if that directory has an exe in it - THEN assume its a game dir
                if (std::filesystem::is_directory(gameDirectory) && DoesDirectoryContainExe(sf)
                    && !IsSubpath(gameDirectory, "Ubisoft Game Launcher")
                    && !IsSubpath(gameDirectory, "Epic Online Services"))
                {
                    GameData gameData;
                    gameData.gameName = SplitStringAtUpperCase(sf.filename().string());
                    gameData.gameDirectory = gameDirectory;
                    gameData.gameExe = GetExeInDirectory(sf);
                    gameData.store = STORE_ENUMS[storeIndex];
                    gameData.drive = driveName[0]; // Use index 0 as want the first character which is drive letter
                    allGames.push_back(gameData);
                }
            }
            storeIndex++;
        }
        storeIndex = 0;
        driveIndex++;
    }
}
//TODO
std::vector<std::string> BackEndAlgorithms::GetGamesAlphabetically(bool descending)
{
    std::vector<std::string> games;
    for (std::vector<std::string> drive : localFileData->directoryLocationsOnDrive)
    {
        for (std::string folder : drive)
        {

        }
    }
    return games;
}
//TODO
std::vector<std::vector<std::string>> BackEndAlgorithms::GetGamesByDrive()
{
    return std::vector<std::vector<std::string>>();
}
//TODO
std::vector<std::vector<std::string>> BackEndAlgorithms::GetGamesByStore()
{
    return std::vector<std::vector<std::string>>();
}

void BackEndAlgorithms::FindStoresOnAllDrives(const std::vector<std::string> customSteam, const std::vector<std::string> customOrigin, const std::vector<std::string> customUbisoft, const std::vector<std::string> customEpic)
{
    std::vector<char> drives = GetDriveNames();

    for (unsigned int drivesIndex = 0; drivesIndex < drives.size(); drivesIndex++)
    {
        std::cout << "Scanning drive: " << drivesIndex << std::endl;
        localFileData->driveNames[drivesIndex] = drives[drivesIndex];
        FindStoresOnDrive(localFileData, drivesIndex);
        std::cout << "Scanned drive: " << drivesIndex + 1 << "\n\tDrives percentage complete: " << ((drivesIndex + 1) * 100) / localFileData->amountOfDrives << std::endl;
    }

    localFileData->exists = true;
}

// --------------------------- Private ---------------------------------------------------------------------------------------------------------------------------------------

void BackEndAlgorithms::FindStoresOnDrive(StoresFile* localData, const int driveIndex)
{
    int* noOfStores = new int;
    *noOfStores = 0;
    int* noOfFolders = new int;
    *noOfFolders = 0;

    AllStores(localData, driveIndex, noOfStores, noOfFolders);

    localData->numberOfStoresOnDrive[driveIndex] = *noOfStores;
    localData->numberOfDirectoriesOnDrive[driveIndex] = *noOfFolders;
}
bool BackEndAlgorithms::SearchForStoresAndFolders(std::string* currentSearchDirectoryPath, std::string* foundSteamLocationPath, std::string* foundOriginLocationPath, std::string* foundUbisoftLocationPath, std::string* foundEpicLocationPath, 
    int depth, bool foundSteam, bool foundOrigin, bool foundUbisoft, bool foundEpic)
{
    // If its trying to search something that isn't a directory OR if it is over the maximum directory search depth
    if (!std::filesystem::is_directory(*currentSearchDirectoryPath) || depth > MAX_DIRECTORY_DEPTH)
    {
        return false;
    }

    // Creates a list to hold all sub folders
    std::vector<std::filesystem::path> subFolders;
    std::filesystem::path folder = std::filesystem::path(*currentSearchDirectoryPath);

    try
    {
        for (std::string steamName : customDirectoryData->steamDirectories)
        {
            if (!foundSteam && std::filesystem::is_directory(folder) && IsSubDirectoryName(*currentSearchDirectoryPath, steamName) && !IsSubpathOfAlternateStore(*currentSearchDirectoryPath, steamName)) // Need to check if the directory name CONTAINS store and not is directly equal to because it will have the extension at the end
            {
                *foundSteamLocationPath = std::string(folder.string());
                foundSteam = true;
            }
        }
        for (std::string originName : customDirectoryData->originDirectories)
        {
            if (!foundOrigin && std::filesystem::is_directory(folder) && IsSubDirectoryName(*currentSearchDirectoryPath, originName) && !IsSubpathOfAlternateStore(*currentSearchDirectoryPath, originName)) // Need to check if the directory name CONTAINS store and not is directly equal to because it will have the extension at the end
            {
                *foundOriginLocationPath = std::string(folder.string());
                foundOrigin = true;
            }
        }
        for (std::string ubisoftName : customDirectoryData->ubisoftDirectories)
        {
            if (!foundUbisoft && std::filesystem::is_directory(folder) && IsSubDirectoryName(*currentSearchDirectoryPath, ubisoftName) && !IsSubpathOfAlternateStore(*currentSearchDirectoryPath, ubisoftName)) // Need to check if the directory name CONTAINS store and not is directly equal to because it will have the extension at the end
            {
                *foundUbisoftLocationPath = std::string(folder.string());
                foundUbisoft = true;
            }
        }
        for (std::string epicName : customDirectoryData->epicDirectories)
        {
            if (!foundEpic && std::filesystem::is_directory(folder) && IsSubDirectoryName(*currentSearchDirectoryPath, epicName) && !IsSubpathOfAlternateStore(*currentSearchDirectoryPath, epicName)) // Need to check if the directory name CONTAINS store and not is directly equal to because it will have the extension at the end
            {
                *foundEpicLocationPath = std::string(folder.string());
                foundEpic = true;
            }
        }
        // Can't use the bools for foundSteam etc, as they aren't persistent across recursion
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
            if (SearchForStoresAndFolders(&subFolder, foundSteamLocationPath, foundOriginLocationPath, foundUbisoftLocationPath, foundEpicLocationPath, depth + 1, foundSteam, foundOrigin, foundUbisoft, foundEpic))
            {
                return true;
            }
        }
    }
    return false;
}

bool BackEndAlgorithms::IsPathWhitelisted(const std::string path)
{
    for (std::string whitelist : whitelistsData->directoryNames)
    {
        if (IsSubpath(path, whitelist))
        {
            return true;
        }
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
/* Checks if the directory path is a sub directory of another store */
bool BackEndAlgorithms::IsSubpathOfAlternateStore(const std::string path, const std::string currentStoreName)
{
    for (std::string storeName : STORE_NAMES)
    {
        if (!(currentStoreName == storeName || currentStoreName == storeName + " Games") && (path.find(storeName) != std::string_view::npos))
        {
            return true;
        }
    }
    return false;
}
/* Check if subpath is the final directory name in directory */
bool BackEndAlgorithms::IsSubDirectoryName(const std::string directory, const std::string subdirectory)
{
    int index = directory.length() - (subdirectory.length() + 1);
    if (index < 0)
    {
        return false;
    }

    return directory.substr(index)._Equal("\\" + subdirectory);
}

//TODO - Alternatively could do check if ASCII is below 91 or whatever lowercase a is and then insert space before
//TODO - make method for while loops
std::string BackEndAlgorithms::SplitStringAtUpperCase(std::string origString)
{
    std::vector<std::string> insertAfterLetter;
    std::vector<std::string> subsequentLetterCheck;

    // Regex for lowercase followed by uppercase
    std::regex regex("([a-z])([A-Z])");
    // Regex for lowercase followed by number
    std::regex regex1("([a-z])([0-9])");
    // Regex for number followed by uppercase
    std::regex regex2("([0-9])([A-Z])");
    std::string s = origString;
    std::smatch m;

    while (std::regex_search(s, m, regex)) {
        int index = 0;
        for (auto x : m)
        {
            if (index != 0)
            {
                if (index == 1) // save character into array so can check that when iterating through string and then insert whitespace after the char
                {
                    insertAfterLetter.push_back(m[1]);
                    subsequentLetterCheck.push_back(m[2]);
                }
            }
            index++;
        }
        s = m.suffix().str();
    }
    while (std::regex_search(s, m, regex1)) {
        int index = 0;
        for (auto x : m)
        {
            if (index != 0)
            {
                if (index == 1) // save character into array so can check that when iterating through string and then insert whitespace after the char
                {
                    insertAfterLetter.push_back(m[1]);
                    subsequentLetterCheck.push_back(m[2]);
                }
            }
            index++;
        }
        s = m.suffix().str();
    }
    while (std::regex_search(s, m, regex2)) {
        int index = 0;
        for (auto x : m)
        {
            if (index != 0)
            {
                if (index == 1) // save character into array so can check that when iterating through string and then insert whitespace after the char
                {
                    insertAfterLetter.push_back(m[1]);
                    subsequentLetterCheck.push_back(m[2]);
                }
            }
            index++;
        }
        s = m.suffix().str();
    }

    std::string seperatedString = "";
    int index = 0;
    for (char letter : origString)
    {
        seperatedString += letter;
        for (unsigned int i=0; i < insertAfterLetter.size(); i++)
        {
            std::string insert = insertAfterLetter[i];
            std::string checker = subsequentLetterCheck[i];
            std::string test1 = "";
            test1 += letter;
            std::string test2 = "";

            if (index == origString.size()) { test2 = ""; }
            else { test2 += origString[index + 1]; }

            if (insert == test1 && checker == test2)
            {
                seperatedString += " ";
            }
        }
        index++;
    }

    return seperatedString;
}
//TODO
bool BackEndAlgorithms::DoesDirectoryContainExe(std::filesystem::path dir)
{
    for (const auto& entry : std::filesystem::directory_iterator(dir))
    {
        if (entry.path().extension() == ".exe")
        {
            return true;
        }
    }
    return false;
}
//TODO
std::string BackEndAlgorithms::GetExeInDirectory(std::filesystem::path dir)
{

    for (const auto& entry : std::filesystem::directory_iterator(dir))
    {
        if (entry.path().extension() == ".exe")
        {
            return entry.path().string();
        }
    }
    return "null";
}

void BackEndAlgorithms::AllStores(StoresFile* localData, const int driveIndex, int* noOfStores, int* noOfFolders)
{
    std::string* drive = &(localData->driveNames[driveIndex]);
    std::string* currentSearchDirectoryPath = new std::string(*drive + ":\\");
    std::string* steamFoundLocation = new std::string("");
    std::string* originFoundLocation = new std::string("");
    std::string* ubisoftFoundLocation = new std::string("");
    std::string* epicFoundLocation = new std::string("");

    SearchForStoresAndFolders(currentSearchDirectoryPath, steamFoundLocation, originFoundLocation, ubisoftFoundLocation, epicFoundLocation);

    // Steam -------------------------------------------------------------------------------------------------
    if (*steamFoundLocation != "") {
        localData->directoryLocationsOnDrive[driveIndex][0] = *steamFoundLocation + STEAMAPPS_COMMON;
        localData->isDirectoryOnDrive[driveIndex][0] = true;
        (*noOfFolders)++;
    }
    if (std::filesystem::exists(*steamFoundLocation + "\\Steam.exe")) {
        localData->storeLocationsOnDrive[driveIndex][0] = *steamFoundLocation;
        localData->isStoreOnDrive[driveIndex][0] = true;
        (*noOfStores)++;
    }
    // Origin ------------------------------------------------------------------------------------------------
    if (*originFoundLocation != "") {
        localData->directoryLocationsOnDrive[driveIndex][1] = *originFoundLocation;
        localData->isDirectoryOnDrive[driveIndex][1] = true;
        (*noOfFolders)++;
    }
    if (std::filesystem::exists(*originFoundLocation + "\\Origin.exe")) {
        localData->storeLocationsOnDrive[driveIndex][1] = *originFoundLocation;
        localData->isStoreOnDrive[driveIndex][1] = true;
        (*noOfStores)++;
    }
    // Ubisoft -----------------------------------------------------------------------------------------------
    if (*ubisoftFoundLocation != "") {
        localData->directoryLocationsOnDrive[driveIndex][2] = *ubisoftFoundLocation;
        localData->isDirectoryOnDrive[driveIndex][2] = true;
        (*noOfFolders)++;
    }
    if (std::filesystem::exists(*ubisoftFoundLocation + "\\Ubisoft Game Launcher\\UbisoftGameLauncher.exe")) {
        localData->storeLocationsOnDrive[driveIndex][3] = *ubisoftFoundLocation + "\\Ubisoft Game Launcher";
        localData->isStoreOnDrive[driveIndex][2] = true;
        (*noOfStores)++;
    }
    // Epic --------------------------------------------------------------------------------------------------
    if (*epicFoundLocation != "") {
        localData->directoryLocationsOnDrive[driveIndex][3] = *epicFoundLocation;
        localData->isDirectoryOnDrive[driveIndex][3] = true;
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
