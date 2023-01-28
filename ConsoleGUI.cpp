#include "ConsoleGUI.h"
#include "BackEndAlgorithms.h"
#include <iostream>

//TODO
ConsoleGUI::ConsoleGUI()
{
	DisplayMainMenu();
}
//TODO
ConsoleGUI::~ConsoleGUI()
{
}

void ConsoleGUI::DisplayMainMenu()
{
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
		std::vector<char> allDrives = BackEndAlgorithms::GetDriveNames();
		char driveName = NULL;
		std::cout << "Please enter a drive to scan, your current drives are: " << std::endl;
		for (char drive : allDrives)
		{
			std::cout << (char) drive << ", ";
		}
		std::cout << "\nPlease enter a drive to scan: " << std::endl;
		std::cin >> driveName;

		while (std::find(allDrives.begin(), allDrives.end(), std::toupper(driveName)) == allDrives.end())
		{
			std::cout << "Please enter a valid drive: ";
			std::cin >> driveName;
		}

		BackEndAlgorithms::ScanDrive(driveName);
		break;
	}
	case 2:
		std::cout << "Specify store or game folder locations has been selected" << std::endl;
		BackEndAlgorithms::ScanAllDrives();
		break;
	case 3:
		std::cout << "Returning to Main Menu" << std::endl; 
		break;
	default:
		std::cout << "EXITING SYSTEM" << std::endl;
		return -1;
	}
}

//TODO
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

//TODO
int ConsoleGUI::DisplayAllGames()
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

//TODO
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

//TODO
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