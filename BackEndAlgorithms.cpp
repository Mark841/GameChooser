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
        if (localData->driveNames[drivesIndex].find(driveName) != std::string_view::npos)
        {
            FindStoresOnDrive(localData, drivesIndex);
        }
        drivesIndex++;
    }
}
void BackEndAlgorithms::ScanDrive(const int driveIndex)
{
    StoresFile* localData = GetLocalData();
    FindStoresOnDrive(localData, driveIndex);
}
void BackEndAlgorithms::ScanAllDrives()
{
    std::vector<char> allDrives = GetDriveNames();
    int driveIndex = 0;

    std::vector<std::thread> threadVector;
    
    for (char &drive : allDrives)
    {
        // Add threads to vector of threads to keep track of them
        threadVector.emplace_back([&]() { ThreadScanDrive(drive); }); // Pass by reference here, make sure the object lifetime is correct
    }

    // Re-join threads to main thread
    for (auto& thread : threadVector)
    {
        thread.join();
    }

    localFileData->exists = true;
}
void BackEndAlgorithms::ScanAllDrivesInitial()
{
    std::vector<char> allDrives = GetDriveNames();
    int driveIndex = 0;

    std::vector<std::thread> threadVector;
    
    for (unsigned int drivesIndex = 0; drivesIndex < allDrives.size(); drivesIndex++)
    {
        localFileData->driveNames[drivesIndex] = allDrives[drivesIndex];
    }
    
    for (char &drive : allDrives)
    {
        // Add threads to vector of threads to keep track of them
        threadVector.emplace_back([&]() { ThreadScanDrive(drive); }); // Pass by reference here, make sure the object lifetime is correct
    }

    // Re-join threads to main thread
    for (auto& thread : threadVector)
    {
        thread.join();
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
    return GetStringFromVector(localFileData->driveNames);
}
std::vector<std::string> BackEndAlgorithms::GetFolderLocationsStrings()
{
    return GetStringsFrom2DVector(localFileData->directoryLocationsOnDrive);
}
std::vector<std::string> BackEndAlgorithms::GetStoreLocationsStrings()
{
    return GetStringsFrom2DVector(localFileData->storeLocationsOnDrive);
}
std::vector<std::string> BackEndAlgorithms::GetIsFolderOnDriveStrings()
{
    return GetStringsFrom2DVector(localFileData->isDirectoryOnDrive);
}
std::vector<std::string> BackEndAlgorithms::GetIsStoreOnDriveStrings()
{
    return GetStringsFrom2DVector(localFileData->isStoreOnDrive);
}
std::string BackEndAlgorithms::GetNoOfFoldersOnDriveString()
{
    return GetStringFromVector(localFileData->numberOfDirectoriesOnDrive);
}
std::string BackEndAlgorithms::GetNoOfStoresOnDriveString()
{
    return GetStringFromVector(localFileData->numberOfStoresOnDrive);
}

template <typename T>
std::string BackEndAlgorithms::GetStringFromVector(std::vector<T> vector)
{
    std::string fileEntryLine = "";
    for (unsigned i = 0; i < vector.size(); i++)
    {
        fileEntryLine += ToString(vector[i]);
        if (i != vector.size() - 1) {
            fileEntryLine += "|";
        }
    }
    return fileEntryLine;
}
template <typename T>
std::vector<std::string> BackEndAlgorithms::GetStringsFrom2DVector(std::vector<std::vector<T>> vector)
{
    std::vector<std::string> fileEntries;
    std::string fileEntryLine = "";
    for (std::vector<T> driveString : vector)
    {
        fileEntryLine = "";
        for (unsigned int i = 0; i < driveString.size(); i++)
        {
            fileEntryLine += ToString(driveString[i]);
            if (i != driveString.size() - 1) {
                fileEntryLine += "|";
            }
        }
        fileEntries.push_back(fileEntryLine);
    }
    return fileEntries;
}

void BackEndAlgorithms::GetAllGamesFromFolders()
{
    int driveIndex = 0;

    allGames.clear();
    allGamesByDrive.clear();
    allGamesByDrive.resize(localFileData->amountOfDrives);

    for (std::vector<std::string> drive : localFileData->directoryLocationsOnDrive)
    {
        GetAllGamesFromDrive(drive, driveIndex);
        driveIndex++;
    }
}
void BackEndAlgorithms::GetAllGamesFromDrive(const std::vector<std::string> directoryLocationsOnDrive, const int driveIndex)
{
    int storeIndex = 0;
    std::string driveName = localFileData->driveNames[driveIndex];

    for (std::string store : directoryLocationsOnDrive)
    {
        std::vector<std::filesystem::path> subDirectories;
        if (!IsStringNullOrWhitespace(store) && std::filesystem::is_directory(store))
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
            std::string* currentSearchDirectoryPath = new std::string(gameDirectory);
            std::string* foundLocationPath = new std::string("");

            // If its trying to search something that is a directory AND if that directory has an exe in it somewhere - THEN assume its a game dir
            if (std::filesystem::is_directory(gameDirectory) && RecurseSearchForExe(currentSearchDirectoryPath, foundLocationPath)
                && !IsGameDirWhitelisted(gameDirectory))
            {
                GameData gameData;
                gameData.gameName = SplitStringAtUpperCase(sf.filename().string());
                gameData.gameDirectory = *foundLocationPath;
                gameData.gameExe = GetExeInDirectory(*foundLocationPath);
                gameData.store = STORE_ENUMS[storeIndex];
                gameData.drive = driveName[0]; // Use index 0 as want the first character which is drive letter
                allGames.push_back(gameData);
                allGamesByDrive[driveIndex].push_back(gameData);
            }
        }
        storeIndex++;
    }
}

std::vector<GameData> BackEndAlgorithms::GetGamesAlphabetically(bool descending)
{
    std::vector<GameData> sortedGames = allGames;
    GameData tempData;
    for (unsigned int i = 0; i < sortedGames.size(); i++)
    {
        for (unsigned int j = i + 1; j < sortedGames.size(); j++)
        {
            if (!descending && sortedGames[i].gameName > sortedGames[j].gameName)
            {
                tempData = sortedGames[i];
                sortedGames[i] = sortedGames[j];
                sortedGames[j] = tempData;
            }
            if (descending && sortedGames[i].gameName < sortedGames[j].gameName)
            {
                tempData = sortedGames[i];
                sortedGames[i] = sortedGames[j];
                sortedGames[j] = tempData;
            }
        }
    }

    return sortedGames;
}
std::vector<std::vector<GameData>> BackEndAlgorithms::GetGamesByDrive()
{
    return allGamesByDrive;
}
std::vector<std::vector<GameData>> BackEndAlgorithms::GetGamesByStore()
{
    std::vector<std::vector<GameData>> sortedGames;
    sortedGames.resize(NUMBER_OF_STORES);

    for (GameData game : allGames)
    {
        if (game.store == Stores::STEAM) 
        {
            sortedGames[0].push_back(game);
        }
        else if (game.store == Stores::EA)
        {
            sortedGames[1].push_back(game);
        }
        else if (game.store == Stores::UBISOFT)
        {
            sortedGames[2].push_back(game);
        }
        else if (game.store == Stores::EPIC)
        {
            sortedGames[3].push_back(game);
        }
        /*else if (game.store == Stores::ROCKSTAR)
        {
            sortedGames[4].push_back(game);
        }
        else if (game.store == Stores::BLIZZARD)
        {
            sortedGames[5].push_back(game);
        }*/
    }
    return sortedGames;
}

void BackEndAlgorithms::LaunchGame(const GameData& game)
{
    LaunchExe(game.gameExe);
}
void BackEndAlgorithms::LaunchStore(const Stores& store)
{
    switch (store)
    {
    case Stores::STEAM: 
        for (unsigned int i = 0; i < localFileData->isStoreOnDrive.size(); i++)
        {
            if (localFileData->isStoreOnDrive[i][STEAM_INDEX])
            {
                LaunchExe(localFileData->storeLocationsOnDrive[i][STEAM_INDEX]);
            }
        }
        break;
    case Stores::EA:
        for (unsigned int i = 0; i < localFileData->isStoreOnDrive.size(); i++)
        {
            if (localFileData->isStoreOnDrive[i][EA_INDEX])
            {
                LaunchExe(localFileData->storeLocationsOnDrive[i][EA_INDEX]);
            }
        }
        break;
    case Stores::UBISOFT:
        for (unsigned int i = 0; i < localFileData->isStoreOnDrive.size(); i++)
        {
            if (localFileData->isStoreOnDrive[i][UBISOFT_INDEX])
            {
                LaunchExe(localFileData->storeLocationsOnDrive[i][UBISOFT_INDEX]);
            }
        }
        break;
    case Stores::EPIC:
        for (unsigned int i = 0; i < localFileData->isStoreOnDrive.size(); i++)
        {
            if (localFileData->isStoreOnDrive[i][EPIC_INDEX])
            {
                LaunchExe(localFileData->storeLocationsOnDrive[i][EPIC_INDEX]);
            }
        }
        break;
    default:
        break;
    }
}

void BackEndAlgorithms::LaunchExe(const std::string exe)
{
    ShellExecuteA(NULL, NULL, exe.c_str(), NULL, NULL, SW_SHOW);
}

std::vector<SearchGameData> BackEndAlgorithms::SearchStores(const std::string gameName)
{
    std::vector<SearchGameData> gameOnStores;
    for (Stores store : STORE_ENUMS)
    {
        SearchGameData* result = SearchStore(store, gameName);
        if (result != nullptr)
        {
            gameOnStores.push_back(*result);
        }
    }
    return gameOnStores;
}
//TODO
SearchGameData* BackEndAlgorithms::SearchStore(const Stores& storeName, const std::string gameName)
{
    SearchGameData* resultData = nullptr;
    // --- STEAM ------------------------------------------------------------------------------------------------------------------------------------------------------------
    if (storeName == Stores::STEAM)
    {
        SteamSearch(gameName, resultData);
    }
    // --- EA ---------------------------------------------------------------------------------------------------------------------------------------------------------------
    else if (storeName == Stores::EA)
    {
        EASearch(gameName, resultData);
    }
    // --- UBISOFT ----------------------------------------------------------------------------------------------------------------------------------------------------------
    else if (storeName == Stores::UBISOFT)
    {
        UbisoftSearch(gameName, resultData);
    }
    // --- EPIC -------------------------------------------------------------------------------------------------------------------------------------------------------------
    else if (storeName == Stores::EPIC)
    {
        EpicSearch(gameName, resultData);
    }
    return resultData;
}

// --------------------------- Private ---------------------------------------------------------------------------------------------------------------------------------------

void BackEndAlgorithms::ThreadScanDrive(const char drive)
{
    ScanDrive(drive);
}

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

bool BackEndAlgorithms::SearchForStoresAndFolders(std::string* currentSearchDirectoryPath, std::string* foundSteamLocationPath, std::string* foundEaDirPath, std::string* foundEaStorePath, std::string* foundUbisoftLocationPath, std::string* foundEpicLocationPath,
    bool* foundSteam, bool* foundEA, bool* foundUbisoft, bool* foundEpic, int depth)
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
            if (!*foundSteam && std::filesystem::is_directory(folder) && IsSubDirectoryName(*currentSearchDirectoryPath, steamName) && !IsSubpathOfAlternateStore(*currentSearchDirectoryPath, steamName)) // Need to check if the directory name CONTAINS store and not is directly equal to because it will have the extension at the end
            {
                *foundSteamLocationPath = std::string(folder.string());
                *foundSteam = true;
            }
        }
        for (std::string eaName : customDirectoryData->eaDirectories)
        {
            if (!IsSubpath(*currentSearchDirectoryPath, "Desktop") && std::filesystem::is_directory(folder) && IsSubDirectoryName(*currentSearchDirectoryPath, eaName) && !IsSubpathOfAlternateStore(*currentSearchDirectoryPath, eaName)) // Need to check if the directory name CONTAINS store and not is directly equal to because it will have the extension at the end
            {
                *foundEaDirPath = std::string(folder.string());
                *foundEA = true;
            }
            //TODO This does not get found
            if (IsSubpath(*currentSearchDirectoryPath, "Desktop") && std::filesystem::is_directory(folder) && IsSubDirectoryName(*currentSearchDirectoryPath, eaName) && !IsSubpathOfAlternateStore(*currentSearchDirectoryPath, eaName)) // Need to check if the directory name CONTAINS store and not is directly equal to because it will have the extension at the end
            {
                *foundEaStorePath = std::string(folder.string());
                *foundEA = true;
            }
        }
        for (std::string ubisoftName : customDirectoryData->ubisoftDirectories)
        {
            if (!*foundUbisoft && std::filesystem::is_directory(folder) && IsSubDirectoryName(*currentSearchDirectoryPath, ubisoftName) && !IsSubpathOfAlternateStore(*currentSearchDirectoryPath, ubisoftName)) // Need to check if the directory name CONTAINS store and not is directly equal to because it will have the extension at the end
            {
                *foundUbisoftLocationPath = std::string(folder.string());
                *foundUbisoft = true;
            }
        }
        for (std::string epicName : customDirectoryData->epicDirectories)
        {
            if (!*foundEpic && std::filesystem::is_directory(folder) && IsSubDirectoryName(*currentSearchDirectoryPath, epicName) && !IsSubpathOfAlternateStore(*currentSearchDirectoryPath, epicName)) // Need to check if the directory name CONTAINS store and not is directly equal to because it will have the extension at the end
            {
                *foundEpicLocationPath = std::string(folder.string());
                *foundEpic = true;
            }
        }

        if (*foundSteam && *foundEA && *foundUbisoft && *foundEpic)
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
            if (SearchForStoresAndFolders(&subFolder, foundSteamLocationPath, foundEaDirPath, foundEaStorePath, foundUbisoftLocationPath, foundEpicLocationPath, foundSteam, foundEA, foundUbisoft, foundEpic, depth + 1))
            {
                return true;
            }
        }
    }
    return false;
}

bool BackEndAlgorithms::RecurseSearchForExe(std::string* currentSearchDirectoryPath, std::string* foundLocationPath, int depth)
{// If its trying to search something that isn't a directory OR if it is over the maximum directory search depth
    if (!std::filesystem::is_directory(*currentSearchDirectoryPath) || depth > MAX_GAME_DIRECTORY_DEPTH)
    {
        return false;
    }

    // Creates a list to hold all sub folders
    std::vector<std::filesystem::path> subFolders;
    std::filesystem::path folder = std::filesystem::path(*currentSearchDirectoryPath);

    try
    {
        if (std::filesystem::is_directory(folder) && DoesDirectoryContainExe(folder)) // Need to check if the directory name CONTAINS store and not is directly equal to because it will have the extension at the end
        {
            *foundLocationPath = std::string(folder.string());
            return true;
        }

        for (const auto& entry : std::filesystem::directory_iterator(*currentSearchDirectoryPath))
        {
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
            if (RecurseSearchForExe(&subFolder, foundLocationPath, depth + 1))
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
        if (!(IsStoreACustomDir(currentStoreName, storeName)) && (path.find(storeName) != std::string_view::npos))
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

bool BackEndAlgorithms::IsStoreACustomDir(const std::string dirName, const std::string storeName)
{
    if (dirName == storeName
        || dirName == storeName + " Games"
        || dirName == storeName + " Desktop"
        || dirName == storeName + " Library"
        || dirName == storeName + "Games"
        || dirName == storeName + "Desktop"
        || dirName == storeName + "Library")
    {
        return true;
    }
    return false;
}

bool BackEndAlgorithms::IsGameDirWhitelisted(const std::string dirName)
{
    return (IsSubpath(dirName, "Launcher")
        || IsSubpath(dirName, "Epic Online Services")
        || IsSubpath(dirName, "Steamworks Shared")
        || IsSubpath(dirName, "SteamVR"));
}

std::string BackEndAlgorithms::SplitStringAtUpperCase(std::string origString)
{
    std::vector<std::string> insertAfterLetter;
    std::vector<std::string> subsequentLetterCheck;
    std::smatch m;

    // Regex for lowercase followed by uppercase
    std::regex regex("([a-z])([A-Z])");
    // Regex for lowercase followed by number
    std::regex regex1("([a-z])([0-9])");
    // Regex for number followed by uppercase
    std::regex regex2("([0-9])([A-Z])");

    // Regex for lowercase followed by uppercase
    RegexChecker(regex, origString, m, insertAfterLetter, subsequentLetterCheck);
    // Regex for lowercase followed by number
    RegexChecker(regex1, origString, m, insertAfterLetter, subsequentLetterCheck);
    // Regex for number followed by uppercase
    RegexChecker(regex2, origString, m, insertAfterLetter, subsequentLetterCheck);

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
void BackEndAlgorithms::RegexChecker(std::regex regex, std::string origString, std::smatch match, std::vector<std::string>& insertAfterLetter, std::vector<std::string>& subsequentLetterCheck)
{
    while (std::regex_search(origString, match, regex)) {
        int index = 0;
        for (auto x : match)
        {
            if (index != 0)
            {
                if (index == 1) // save character into array so can check that when iterating through string and then insert whitespace after the char
                {
                    insertAfterLetter.push_back(match[1]);
                    subsequentLetterCheck.push_back(match[2]);
                }
            }
            index++;
        }
        origString = match.suffix().str();
    }
}
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

std::string BackEndAlgorithms::ToLower(std::string string)
{
    std::transform(string.begin(), string.end(), string.begin(), [](unsigned char c) { return std::tolower(c); });
    return string;
}

void BackEndAlgorithms::AllStores(StoresFile* localData, const int driveIndex, int* noOfStores, int* noOfFolders)
{
    std::string* drive = &(localData->driveNames[driveIndex]);
    std::string* currentSearchDirectoryPath = new std::string(*drive + ":\\");
    std::string* steamFoundLocation = new std::string("");
    std::string* eaDirLocation = new std::string("");
    std::string* eaStoreLocation = new std::string("");
    std::string* ubisoftFoundLocation = new std::string("");
    std::string* epicFoundLocation = new std::string("");
    bool* foundSteam = new bool(false);
    bool* foundEA = new bool(false);
    bool* foundUbi = new bool(false);
    bool* foundEpic = new bool(false);

    SearchForStoresAndFolders(currentSearchDirectoryPath, steamFoundLocation, eaDirLocation, eaStoreLocation, ubisoftFoundLocation, epicFoundLocation, foundSteam, foundEA, foundUbi, foundEpic);

    // Steam -------------------------------------------------------------------------------------------------
    if (*steamFoundLocation != "") {
        localData->directoryLocationsOnDrive[driveIndex][0] = *steamFoundLocation + STEAMAPPS_COMMON;
        localData->isDirectoryOnDrive[driveIndex][0] = true;
        (*noOfFolders)++;
    }
    if (std::filesystem::exists(*steamFoundLocation + "\\Steam.exe")) {
        localData->storeLocationsOnDrive[driveIndex][0] = *steamFoundLocation + "\\Steam.exe";
        localData->isStoreOnDrive[driveIndex][0] = true;
        (*noOfStores)++;
    }
    // EA ------------------------------------------------------------------------------------------------
    if (*eaDirLocation != "") {
        localData->directoryLocationsOnDrive[driveIndex][1] = *eaDirLocation;
        localData->isDirectoryOnDrive[driveIndex][1] = true;
        (*noOfFolders)++;
    }
    if (std::filesystem::exists(*eaStoreLocation + "\\EADesktop.exe") || std::filesystem::exists(*eaStoreLocation + "\\EALauncher.exe")) {
        localData->storeLocationsOnDrive[driveIndex][1] = *eaStoreLocation + "\\EALauncher.exe";
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
        localData->storeLocationsOnDrive[driveIndex][2] = *ubisoftFoundLocation + "\\Ubisoft Game Launcher\\UbisoftGameLauncher.exe";
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
        localData->storeLocationsOnDrive[driveIndex][3] = *epicFoundLocation + "\\Launcher\\Engine\\Binaries\\Win64\\EpicGamesLauncher.exe";
        localData->isStoreOnDrive[driveIndex][3] = true;
        (*noOfStores)++;
    }

    delete currentSearchDirectoryPath;
    delete steamFoundLocation, eaDirLocation, eaStoreLocation, ubisoftFoundLocation, epicFoundLocation;
    delete foundSteam, foundEA, foundUbi, foundEpic;
}


bool BackEndAlgorithms::SteamSearch(const std::string gameName, SearchGameData* resultData)
{
    std::string searchURL = STEAM_SEARCH_URL + gameName;

    CURLplusplus client;
    std::string result = client.Get(searchURL).substr(59550, 7500);
    std::string result2 = BackEndAlgorithms::ToLower(result);
    int startSearchIndex = result2.find(gameName) - 150;

    int urlStartIndex = result.find("href", startSearchIndex) + 6;                              // Plus 6 for the 'href="' at start of the span tag
    int urlEndIndex = result.find("\r\n", urlStartIndex) - 1;                                   // Minus 1 for the '<' at start of the span tag
    std::string url = result.substr(urlStartIndex, urlEndIndex - urlStartIndex);
    
    int nameStartIndex = result.find("title", startSearchIndex) + 7;                            // Plus 7 for the 'title="' at start of the span tag
    int nameEndIndex = result.find("/span", nameStartIndex) - 1;                                // Minus 1 for the '<' at start of the span tag
    std::string name = result.substr(nameStartIndex, nameEndIndex - nameStartIndex);

    int priceStartIndex = result.find("data-price-final", startSearchIndex) + 18;               // Plus 18 for the 'data-price-final="' in the tag
    int priceEndIndex = result.find("\"", priceStartIndex);
    std::string price = result.substr(priceStartIndex, priceEndIndex - priceStartIndex);
    price = price.substr(0, price.length() - 2) + "." + price.substr(price.length() - 2);
    //resultData->price = price;

    int discountStartIndex = result.find("search_discount", startSearchIndex);
    if (discountStartIndex != 0)
    {
        discountStartIndex = result.find("span", discountStartIndex) + 5;       // Plus 5 for the 'span>' in the tag
        int discountEndIndex = result.find("/span", discountStartIndex) - 1;    // Minus 1 for the '<' at start of the span tag
        std::string discount = result.substr(discountStartIndex, discountEndIndex - discountStartIndex);
        //resultData->discount = discount;
    }

    return resultData;
}
bool BackEndAlgorithms::EASearch(const std::string gameName, SearchGameData* resultData)
{
    return resultData;
}
bool BackEndAlgorithms::UbisoftSearch(const std::string gameName, SearchGameData* resultData)
{
    return resultData;
}
bool BackEndAlgorithms::EpicSearch(const std::string gameName, SearchGameData* resultData)
{
    return resultData;
}