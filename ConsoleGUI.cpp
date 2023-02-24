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
		std::vector<std::string> customOrigin = GetCustomDirectoryNames(Stores::ORIGIN);
		std::vector<std::string> customUbisoft = GetCustomDirectoryNames(Stores::UBISOFT);
		std::vector<std::string> customEpic = GetCustomDirectoryNames(Stores::EPIC);

		manager->GetFileManagerHandler()->WriteCustomDirectoriesToFileOverwrite();

		manager->ScanAllDrives(customSteam, customOrigin, customUbisoft, customEpic);
	}
}

void ConsoleGUI::DisplayMainMenu()
{
	NewStoresInstalledSinceLastRun();

	int userInput = 0;
	while (userInput != -1)
	{
		std::cout << "\n\n\nHello and welcome to the PC Game Store combiner, please select an option from below" << std::endl;
		std::cout << "1 - Scan system for stores (by drive or all drives)" << std::endl;
		std::cout << "2 - Specify store or game folder locations" << std::endl;
		std::cout << "3 - View all games on system" << std::endl;
		std::cout << "4 - Play last played game" << std::endl;
		std::cout << "5 - Open stores" << std::endl;
		std::cout << "6 - Search for game on stores" << std::endl;
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
			std::cout << "Scan system for stores (by drive or all drives) page has been selected" << std::endl;
			userInput = DisplayScanByDrive();
			break;
		case 2:
			std::cout << "Specify store or game folder locations page has been selected" << std::endl;
			userInput = DisplayFolderIdentifier();
			break;
		case 3:
			std::cout << "View all games on system page has been selected" << std::endl;
			userInput = DisplayAllGames();
			break;
		case 4:
			std::cout << "Play last played game has been selected" << std::endl;
			break;
		case 5:
			std::cout << "Open stores page has been selected" << std::endl;
			userInput = DisplayStores();
			break;
		case 6:
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
		std::vector<std::string> customOrigin = GetCustomDirectoryNames(Stores::ORIGIN);
		std::vector<std::string> customUbisoft = GetCustomDirectoryNames(Stores::UBISOFT);
		std::vector<std::string> customEpic = GetCustomDirectoryNames(Stores::EPIC);

		manager->GetFileManagerHandler()->WriteCustomDirectoriesToFileOverwrite();

		//TODO - remove all custom vectors and make the method use the customData struct
		manager->ScanDrive(driveName, customSteam, customOrigin, customUbisoft, customEpic);
		break;
	}
	case 2:
	{
		std::cout << "Specify store or game folder locations has been selected" << std::endl;

		std::vector<std::string> customSteam = GetCustomDirectoryNames(Stores::STEAM);
		std::vector<std::string> customOrigin = GetCustomDirectoryNames(Stores::ORIGIN);
		std::vector<std::string> customUbisoft = GetCustomDirectoryNames(Stores::UBISOFT);
		std::vector<std::string> customEpic = GetCustomDirectoryNames(Stores::EPIC);

		manager->GetFileManagerHandler()->WriteCustomDirectoriesToFileOverwrite();

		//TODO - remove all custom vectors and make the method use the customData struct
		manager->ScanAllDrives(customSteam, customOrigin, customUbisoft, customEpic);
		break;
	}
	case 3:
		std::cout << "Returning to Main Menu" << std::endl; 
		break;
	default:
		std::cout << "EXITING SYSTEM" << std::endl;
		return -1;
	}
}

//TODO - Specify store or game folder locations page has been selected
int ConsoleGUI::DisplayFolderIdentifier()
{
	int userInput;
	std::cout << "\n\nHello and welcome to the PC Game Store combiners TODO, please select an option from below" << std::endl;
	std::cout << "1 - TODO" << std::endl;
	std::cout << "2 - TODO" << std::endl;
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
		std::cout << "TODO has been selected" << std::endl;
		break;
	case 2:
		std::cout << "TODO has been selected" << std::endl;
		break;
	case 3:
		std::cout << "Returning to Main Menu" << std::endl;
		break;
	default:
		std::cout << "EXITING SYSTEM" << std::endl;
		return -1;
	}
}

//TODO - View all games on system
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
		bool orderByDescending = GetYesOrNoFromUser("order the games in DESCENDING ALPHABETICAL ORDER");
		std::vector<std::string> gamesByAlphabet = manager->GetAlgorithmsHandler()->GetGamesAlphabetically(orderByDescending);
		for (std::string game : gamesByAlphabet)
		{
			std::cout << game << std::endl;
		}
		break;
	}
	case 2:
	{
		std::cout << "View games by drive has been selected" << std::endl;
		std::vector<std::vector<std::string>> gamesByDrive = manager->GetAlgorithmsHandler()->GetGamesByDrive();
		std::vector<char> driveNames = manager->GetAlgorithmsHandler()->GetDriveNames();
		int index = 0;
		for (std::vector<std::string> drive : gamesByDrive)
		{
			std::cout << "Games on drive " << driveNames[index] << ":" << std::endl;
			for (std::string game : drive)
			{
				std::cout << "\t" << game << std::endl;
			}
			index++;
		}
		break;
	}
	case 3:
	{
		std::cout << "View games by store has been selected" << std::endl;
		std::vector<std::vector<std::string>> gamesByStore = manager->GetAlgorithmsHandler()->GetGamesByStore();
		std::vector<std::string> storeNames = STORE_NAMES;
		int index = 0;
		for (std::vector<std::string> drive : gamesByStore)
		{
			std::cout << "Games on store " << storeNames[index] << ":" << std::endl;
			for (std::string game : drive)
			{
				std::cout << "\t" << game << std::endl;
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
}

//TODO - Open stores
int ConsoleGUI::DisplayStores()
{
	int userInput;
	std::cout << "\n\nHello and welcome to the PC Game Store combiners TODO, please select an option from below" << std::endl;
	std::cout << "1 - TODO" << std::endl;
	std::cout << "2 - TODO" << std::endl;
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
		std::cout << "TODO has been selected" << std::endl;
		break;
	case 2:
		std::cout << "TODO has been selected" << std::endl;
		break;
	case 3:
		std::cout << "Returning to Main Menu" << std::endl;
		break;
	default:
		std::cout << "EXITING SYSTEM" << std::endl;
		return -1;
	}
}

//TODO - Search for game on stores
int ConsoleGUI::DisplayStoresWithSearch()
{
	int userInput;
	std::cout << "\n\nHello and welcome to the PC Game Store combiners TODO, please select an option from below" << std::endl;
	std::cout << "1 - TODO" << std::endl;
	std::cout << "2 - TODO" << std::endl;
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
		std::cout << "TODO has been selected" << std::endl;
		break;
	case 2:
		std::cout << "TODO has been selected" << std::endl;
		break;
	case 3:
		std::cout << "Returning to Main Menu" << std::endl;
		break;
	default:
		std::cout << "EXITING SYSTEM" << std::endl;
		return -1;
	}
}

// --------------------------- Private ---------------------------------------------------------------------------------------------------------------------------------------

std::vector<std::string> ConsoleGUI::GetCustomDirectoryNames(Stores store)
{
	std::string platformName = StoreToString(store);
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
	std::string answer;
	std::cout << "Would you like to " << aboutValue << ", if you would please type 'y' or 'yes' and then press ENTER: " << std::endl;
	std::getline(std::cin, answer);
	if (answer == "y" || answer == "yes")
	{
		return true;
	}
	else
	{
		return false;
	}
}
