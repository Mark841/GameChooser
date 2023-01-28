#include "BackEndAlgorithms.h"
#include "FileManager.h"

//TODO
void BackEndAlgorithms::ScanDrive(char driveName)
{
    // Do I want to save to file in here, could be quite costly if doing for every drive
    // Maybe have default bool param to state whether to save to file or not
}

//TODO
void BackEndAlgorithms::ScanAllDrives()
{
    std::vector<char> allDrives = BackEndAlgorithms::GetDriveNames();
    for (char drive : allDrives)
    {
        ScanDrive(drive);
    }
}

//TODO
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
