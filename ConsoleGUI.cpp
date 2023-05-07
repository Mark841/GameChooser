#include "ConsoleGUI.h"

ConsoleGUI::ConsoleGUI()
{
	DisplayMainMenu();
}
ConsoleGUI::~ConsoleGUI()
{
}

void ConsoleGUI::NewStoresInstalledSinceLastRun()
{
	std::cout << "Hello and welcome to the PC Game Store combiner" << std::endl;
	std::cout << "Have new stores or drives been installed since last run of this application?" << std::endl;
	std::cout << "Or have new folders been made for where games are stored on existing drives?" << std::endl;
	std::cout << "\nIf any of these are true please enter 'y' or 'yes'" << std::endl;
	std::cout << "---------------------------------------------------------------------------------------" << std::endl;

	if (GetYesOrNoFromUser("SCAN YOUR MACHINE for STORES and GAME FOLDERS again"))
	{
		std::vector<std::string> customSteam = GetCustomDirectoryNames(Stores::STEAM);
		std::vector<std::string> customEa = GetCustomDirectoryNames(Stores::EA);
		std::vector<std::string> customUbisoft = GetCustomDirectoryNames(Stores::UBISOFT);
		std::vector<std::string> customEpic = GetCustomDirectoryNames(Stores::EPIC);

		manager->GetFileManagerHandler()->WriteCustomDirectoriesToFileOverwrite();

		manager->ScanAllDrives();
	}
}

void ConsoleGUI::DisplayMainMenu()
{
	if (manager->GetAskToRescanOnStartup()) NewStoresInstalledSinceLastRun();

	int userInput = 0;
	while (userInput != -1)
	{
		std::cout << "\n\n\nHello and welcome to the PC Game Store combiner, please select an option from below" << std::endl;
		std::cout << "1 - Scan system for stores (by drive or all drives)" << std::endl;
		std::cout << "2 - ACCURACY BOOSTER: Specify search/scan store or game directory names OR add additional whitelist directory names" << std::endl;
		std::cout << "3 - Give a random installed game to play" << std::endl;
		std::cout << "4 - View all games on system" << std::endl;
		std::cout << "5 - Play last played game" << std::endl;
		std::cout << "6 - Open stores" << std::endl;
		std::cout << "7 - Search for game on stores" << std::endl;
		std::cout << "0 - EXIT" << std::endl;
		std::cout << "---------------------------------------------------------------------------------------" << std::endl;
		std::cout << "Please enter a numbered option: ";
		std::cin >> userInput;

		while (userInput < 0 || userInput > 7)
		{
			std::cout << "Please enter a valid option: ";
			std::cin >> userInput;
		}
		switch (userInput)
		{
		case 1:
			std::cout << "Scan system for stores (by drive or all drives) page has been selected" << std::endl;
			userInput = DisplayScanByDrive();
			break;
		case 2:
			std::cout << "Specify store or game folder locations page has been selected" << std::endl;
			userInput = DisplayFolderIdentifier();
			break;
		case 3:
			std::cout << "Give a random installed game to play" << std::endl;
			userInput = DisplayRandomGame();
			break;
		case 4:
			std::cout << "View all games on system page has been selected" << std::endl;
			userInput = DisplayAllGames();
			break;
		case 5:
			std::cout << "Play last played game has been selected" << std::endl;
			manager->GetAlgorithmsHandler()->LaunchGame(*(manager->GetAlgorithmsHandler()->GetLastPlayedGameData()));
			break;
		case 6:
			std::cout << "Open stores page has been selected" << std::endl;
			userInput = DisplayStores();
			break;
		case 7:
			std::cout << "Search for game on stores page has been selected" << std::endl;
			userInput = DisplayStoresWithSearch();
			break;
		default:
			std::cout << "EXITING SYSTEM" << std::endl;
			userInput = -1;
			break;
		}
	}
}
int ConsoleGUI::DisplayScanByDrive()
{
	int userInput;
	std::cout << "\n\nHello and welcome to the PC Game Store combiners file scanner, please select an option from below" << std::endl;
	std::cout << "1 - Scan system for stores by drive" << std::endl;
	std::cout << "2 - Scan system for stores across all drives" << std::endl;
	std::cout << "3 - Return to Main Menu" << std::endl;
	std::cout << "0 - EXIT" << std::endl;
	std::cout << "---------------------------------------------------------------------------------------" << std::endl;
	std::cout << "Please enter a numbered option: ";
	std::cin >> userInput;

	while (userInput < 0 || userInput > 3)
	{
		std::cout << "Please enter a valid option: ";
		std::cin >> userInput;
	}
	switch (userInput)
	{
	case 1:
	{
		std::cout << "Scan system for stores (by drive or all drives) has been selected" << std::endl;
		std::cout << "Please enter a drive to scan, your current drives are: " << std::endl;
		std::vector<char> allDrives = manager->GetAlgorithmsHandler()->GetDriveNames();
		for (char drive : allDrives)
		{
			std::cout << (char) drive << ", ";
		}
		std::cout << "\nPlease enter a drive to scan: " << std::endl;
		char driveName = NULL;
		std::cin >> driveName;

		while (std::find(allDrives.begin(), allDrives.end(), std::toupper(driveName)) == allDrives.end())
		{
			std::cout << "Please enter a valid drive: ";
			std::cin >> driveName;
		}

		std::vector<std::string> customSteam = GetCustomDirectoryNames(Stores::STEAM);
		std::vector<std::string> customEa = GetCustomDirectoryNames(Stores::EA);
		std::vector<std::string> customUbisoft = GetCustomDirectoryNames(Stores::UBISOFT);
		std::vector<std::string> customEpic = GetCustomDirectoryNames(Stores::EPIC);

		manager->GetFileManagerHandler()->WriteCustomDirectoriesToFileOverwrite();

		manager->ScanDrive(driveName);
		break;
	}
	case 2:
	{
		std::cout << "Specify store or game folder locations has been selected" << std::endl;

		std::vector<std::string> customSteam = GetCustomDirectoryNames(Stores::STEAM);
		std::vector<std::string> customEa = GetCustomDirectoryNames(Stores::EA);
		std::vector<std::string> customUbisoft = GetCustomDirectoryNames(Stores::UBISOFT);
		std::vector<std::string> customEpic = GetCustomDirectoryNames(Stores::EPIC);

		manager->GetFileManagerHandler()->WriteCustomDirectoriesToFileOverwrite();

		manager->ScanAllDrives();
		break;
	}
	case 3:
		std::cout << "Returning to Main Menu" << std::endl; 
		break;
	default:
		std::cout << "EXITING SYSTEM" << std::endl;
		return -1;
	}
	return -5;
}
//TOTEST
int ConsoleGUI::DisplayFolderIdentifier()
{
	int userInput;
	std::cout << "\n\nHello and welcome to the PC Game Store combiners specifying store or game folder locations on drive for next scan or whitelist directory names to not search in (can drastically speed up drive scanning), please select an option from below" << std::endl;
	std::cout << "1 - Enter custom directory names" << std::endl;
	std::cout << "2 - Enter new whitelist directory names" << std::endl;
	std::cout << "3 - Return to Main Menu" << std::endl;
	std::cout << "0 - EXIT" << std::endl;
	std::cout << "---------------------------------------------------------------------------------------" << std::endl;
	std::cout << "Please enter a numbered option: ";
	std::cin >> userInput;

	while (userInput < 0 || userInput > 3)
	{
		std::cout << "Please enter a valid option: ";
		std::cin >> userInput;
	}
	switch (userInput)
	{
	case 1:
	{
		std::cout << "Entering new custom search directory names has been selected" << std::endl;

		std::vector<std::string> customSteam = GetCustomDirectoryNames(Stores::STEAM);
		std::vector<std::string> customEa = GetCustomDirectoryNames(Stores::EA);
		std::vector<std::string> customUbisoft = GetCustomDirectoryNames(Stores::UBISOFT);
		std::vector<std::string> customEpic = GetCustomDirectoryNames(Stores::EPIC);

		manager->GetFileManagerHandler()->WriteCustomDirectoriesToFileOverwrite();

		break;
	}
	case 2:
	{
		std::cout << "Entering new whitelist directory names has been selected" << std::endl;
		std::vector<std::string> newWhitelists = GetVectorOfStringsFromUser("WHITELIST DIRECTORY NAMES");
		manager->GetAlgorithmsHandler()->AddToWhitelistData(newWhitelists);
		manager->GetFileManagerHandler()->WriteWhitelistsToFileOverwrite();

		break;
	}
	case 3:
		std::cout << "Returning to Main Menu" << std::endl;
		break;
	default:
		std::cout << "EXITING SYSTEM" << std::endl;
		return -1;
	}
	return -5;
}

//TOTEST
int ConsoleGUI::DisplayRandomGame()
{
	int userInput;
	std::cout << "\n\nHello and welcome to the PC Game Store combiners display a random game, please select an option from below" << std::endl;

jumpPoint:
	std::vector<GameData> allGames = manager->GetAlgorithmsHandler()->GetGamesAlphabetically(false);

	srand((int) time(0));
	int index = 1 + (rand() % allGames.size());
	std::cout << "\n\t\t\t" << allGames[index].gameName << "\n" << std::endl;


	std::cout << "1 - Get another random game" << std::endl;
	std::cout << "2 - Launch selected game" << std::endl;
	std::cout << "3 - Return to Main Menu" << std::endl;
	std::cout << "0 - EXIT" << std::endl;
	std::cout << "---------------------------------------------------------------------------------------" << std::endl;
	std::cout << "Please enter a numbered option: ";
	std::cin >> userInput;

	while (userInput < 0 || userInput > 3)
	{
		std::cout << "Please enter a valid option: ";
		std::cin >> userInput;
	}
	switch (userInput)
	{
	case 1:
		std::cout << "Selecting another random game: ";
		goto jumpPoint;
	case 2:
		std::cout << "Opening " << allGames[index].gameName << ": ";
		manager->SetLastPlayedGame(allGames[index]);
		manager->GetAlgorithmsHandler()->LaunchGame(allGames[index]);
		break;
	case 3:
		std::cout << "Returning to Main Menu" << std::endl;
		break;
	default:
		std::cout << "EXITING SYSTEM" << std::endl;
		return -1;
	}
	return -5;
}

int ConsoleGUI::DisplayAllGames()
{
	int userInput;
	std::cout << "\n\nHello and welcome to the PC Game Store combiners game displayer, please select an option from below" << std::endl;
	std::cout << "1 - View games alphabetically" << std::endl;
	std::cout << "2 - View games by drive" << std::endl;
	std::cout << "3 - View games by store" << std::endl;
	std::cout << "4 - Return to Main Menu" << std::endl;
	std::cout << "0 - EXIT" << std::endl;
	std::cout << "---------------------------------------------------------------------------------------" << std::endl;
	std::cout << "Please enter a numbered option: ";
	std::cin >> userInput;

	while (userInput < 0 || userInput > 4)
	{
		std::cout << "Please enter a valid option: ";
		std::cin >> userInput;
	}
	switch (userInput)
	{
	case 1:
	{
		std::cout << "View games alphabetically has been selected" << std::endl;
		std::vector<GameData> gamesByAlphabet = manager->GetAlgorithmsHandler()->GetGamesAlphabetically(GetYesOrNoFromUser("order the games in DESCENDING ALPHABETICAL ORDER"));

		for (GameData game : gamesByAlphabet)
		{
			std::cout << game.gameName << std::endl;
		}
		break;
	}
	case 2:
	{
		std::cout << "View games by drive has been selected" << std::endl;
		std::vector<std::vector<GameData>> gamesByDrive = manager->GetAlgorithmsHandler()->GetGamesByDrive();
		std::vector<char> driveNames = manager->GetAlgorithmsHandler()->GetDriveNames();
		int index = 0;
		for (std::vector<GameData> drive : gamesByDrive)
		{
			if (drive.size() != 0) 
			{ 
				std::cout << "\nGames on drive - " << driveNames[index] << ":" << std::endl; 
			}

			for (GameData game : drive)
			{
				std::cout << "\t" << game.gameName << std::endl;
			}
			index++;
		}
		break;
	}
	case 3:
	{
		std::cout << "View games by store has been selected" << std::endl;
		std::vector<std::vector<GameData>> gamesByStore = manager->GetAlgorithmsHandler()->GetGamesByStore();
		std::vector<std::string> storeNames = STORE_NAMES_UPPER;
		int index = 0;
		for (std::vector<GameData> drive : gamesByStore)
		{
			if (drive.size() != 0)
			{
				std::cout << "\nGames on store - " << storeNames[index] << ":" << std::endl;
			}

			for (GameData game : drive)
			{
				std::cout << "\t" << game.gameName << std::endl;
			}
			index++;
		}
		break;
	}
	case 4:
		std::cout << "Returning to Main Menu" << std::endl;
		break;
	default:
		std::cout << "EXITING SYSTEM" << std::endl;
		return -1;
	}
	return -5;
}

int ConsoleGUI::DisplayStores()
{
	int userInput;
	std::cout << "\n\nHello and welcome to the PC Game Store combiners store selector, please select an option from below" << std::endl;
	std::cout << "1 - Open Steam" << std::endl;
	std::cout << "2 - Open Origin" << std::endl;
	std::cout << "3 - Open Ubisoft" << std::endl;
	std::cout << "4 - Open Epic" << std::endl;
	std::cout << "5 - Return to Main Menu" << std::endl;
	std::cout << "0 - EXIT" << std::endl;
	std::cout << "---------------------------------------------------------------------------------------" << std::endl;
	std::cout << "Please enter a numbered option: ";
	std::cin >> userInput;

	while (userInput < 0 || userInput > 5)
	{
		std::cout << "Please enter a valid option: ";
		std::cin >> userInput;
	}
	switch (userInput)
	{
	case 1:
		std::cout << "Open Steam has been selected" << std::endl;
		manager->GetAlgorithmsHandler()->LaunchStore(Stores::STEAM);
		break;
	case 2:
		std::cout << "Open Origin has been selected" << std::endl;
		manager->GetAlgorithmsHandler()->LaunchStore(Stores::EA);
		break;
	case 3:
		std::cout << "Open Ubisoft has been selected" << std::endl;
		manager->GetAlgorithmsHandler()->LaunchStore(Stores::UBISOFT);
		break;
	case 4:
		std::cout << "Open Epic has been selected" << std::endl;
		manager->GetAlgorithmsHandler()->LaunchStore(Stores::EPIC);
		break;
	case 5:
		std::cout << "Returning to Main Menu" << std::endl;
		break;
	default:
		std::cout << "EXITING SYSTEM" << std::endl;
		return -1;
	}
	return -5;
}

//TODO - Search for game on stores
int ConsoleGUI::DisplayStoresWithSearch()
{
	int userInput;
	std::cout << "\n\nHello and welcome to the PC Game Store combiners store searcher, please select an option from below" << std::endl;
	std::cout << "1 - Search for a game" << std::endl;
	std::cout << "2 - Return to Main Menu" << std::endl;
	std::cout << "0 - EXIT" << std::endl;
	std::cout << "---------------------------------------------------------------------------------------" << std::endl;
	std::cout << "Please enter a numbered option: ";
	std::cin >> userInput;

	while (userInput < 0 || userInput > 2)
	{
		std::cout << "Please enter a valid option: ";
		std::cin >> userInput;
	}
	switch (userInput)
	{
	case 1:
	{
		std::cout << "Search for a game has been selected" << std::endl;

		std::cout << "\nPlease enter a game to search for: " << std::endl;
		std::string gameName;
		std::cin >> gameName;

		std::vector<SearchGameData> gameOnStores = manager->GetAlgorithmsHandler()->SearchStores(gameName);

		std::cout << "The game " << gameName << " was found on the stores below" << std::endl;
		for (unsigned int i = 0; i < NUMBER_OF_STORES; i++)
		{
			std::cout << STORE_NAMES_UPPER[i] << "\t-\t" << gameOnStores[i].price << std::endl;
		}

		break;
	}
	case 2:
		std::cout << "Returning to Main Menu" << std::endl;
		break;
	default:
		std::cout << "EXITING SYSTEM" << std::endl;
		return -1;
	}
	return -5;
}

// --------------------------- Private ---------------------------------------------------------------------------------------------------------------------------------------

std::vector<std::string> ConsoleGUI::GetVectorOfStringsFromUser(std::string purpose)
{
	std::vector<std::string> custom;
	std::cout << "Please enter the names for your " << purpose << ", please enter each name and then press ENTER, if you have no more to add please type 'n' or 'no' and press ENTER: " << std::endl;
	std::string customData = "null";
	while (true)
	{
		std::cout << "\tCUSTOM " << purpose << " NAME: ";
		std::getline(std::cin, customData);
		if (customData == "n" || customData == "no")
		{
			break;
		}
		if (customData != "")
		{
			custom.push_back(customData);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	return custom;
}

std::vector<std::string> ConsoleGUI::GetCustomDirectoryNames(Stores store)
{
	std::string platformName = manager->GetAlgorithmsHandler()->ToString(store);
	std::vector<std::string> custom;

	std::cout << "If you have any CUSTOM DIRECTORY names for your " << platformName << " games library, please enter each name and then press ENTER, if you have no custom directory names please type 'n' or 'no' and press ENTER: " << std::endl;
	std::string customDirectory = "null";
	while (true)
	{
		std::cout << "\tCUSTOM " << platformName << " DIRECTORY NAME: ";
		std::getline(std::cin, customDirectory);
		if (customDirectory == "n" || customDirectory == "no")
		{
			break;
		}
		if (customDirectory != "")
		{
			custom.push_back(customDirectory);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	manager->GetAlgorithmsHandler()->AddToCustomDirectoryData(store, custom);
	return custom;
}

bool ConsoleGUI::GetYesOrNoFromUser(std::string aboutValue)
{
	std::string answer = "";
	std::cout << "Would you like to " << aboutValue << ", if you would please type 'y' or 'yes' and then press ENTER: " << std::endl;
	std::cin >> answer;
	std::cout<< std::endl;

	if (answer == "y" || answer == "yes")
	{
		return true;
	}
	else
	{
		return false;
	}
}
