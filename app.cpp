#include <iostream>
#include <Windows.h>
#include <string>
#include <limits>

#define LOGGING

const std::string MainWindowText = R"(
===============================================================
		    	Windows Tweaker
===============================================================
[1] Toggle Windows Defender (Enable/Disable)
[2] Toggle Telemetry (Enable/Disable)
[3] Toggle Windows Updates (Enable/Disable)
[4] Enable Windows 11 Old Context Menu
[5] Delete UWP Applications (OneDrive, Paint3D, XBOX, Cortana)
===============================================================
)";

const std::string DefenderToggleText = R"(
===============================================================
                Toggle Windows Defender
===============================================================
)";

const std::string TelemetryToggleText = R"(
===============================================================
                Toggle Windows Telemetry
===============================================================
)";

const std::string UpdatesToggleText = R"(
===============================================================
                Toggle Windows Updates
===============================================================
)";


void ToggleWindowsDefender(const char arg);
void ToggleWindowsTelemetry(const char arg);
void ToggleWindowsUpdates(const char arg);
void RetrunToMainMenu();

bool IsRunAsAdmin() {
    BOOL isAdmin = FALSE;
    SID_IDENTIFIER_AUTHORITY ntAuthority = SECURITY_NT_AUTHORITY; // Define the SID identifier authority

    PSID adminGroup; // Pointer to store the administrator group SID

    // Allocate and initialize the administrator group SID
    if (AllocateAndInitializeSid(&ntAuthority, 2,
                                 SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS,
                                 0, 0, 0, 0, 0, 0, &adminGroup)) {

        // Check if the current token is a member of the administrator group
        if (!CheckTokenMembership(nullptr, adminGroup, &isAdmin)) {
            isAdmin = FALSE;
        }

        // Free the memory allocated for the administrator group SID
        FreeSid(adminGroup);
    }

    // Return true if the current process is running as an administrator, false otherwise
    return isAdmin != 0;
}

//Restarts the program with administrator privileges.
void RestartAsAdmin() {
    // Get the current executable file path
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);

    // Prepare to relaunch the program with admin privileges
    SHELLEXECUTEINFOA sei = { sizeof(SHELLEXECUTEINFOA) };
    sei.lpVerb = "runas"; // Request admin privileges
    sei.lpFile = exePath;  // Use the current executable path
    sei.nShow = SW_NORMAL;

    // Try to relaunch the program with admin privileges
    if (!ShellExecuteExA(&sei)) {
        DWORD error = GetLastError();
        std::cout << "Failed to restart with admin privileges (error code: " << error << ")" << std::endl;
    }
}

int main()
{
    if(IsRunAsAdmin())
    {
        int choice;
        std::cout << MainWindowText << std::endl;
        std::cout << ">>> ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                char arg;
                std::cout << DefenderToggleText << std::endl << std::endl;
                std::cout << "[1] Disable Windows Defender" << std::endl << "[2] Enable Windows Defender" << std::endl << std::endl;
                std::cout << ">>> ";
                std::cin >> arg;

                // Validate the input in a do-while loop
                while(arg != '1' && arg != '2'){
                    std::cout << "Error || Invalid argument." << std::endl << std::endl;
                    std::cout <<  "[1] Disable Windows Defender" << std::endl << "[2] Enable Windows Defender" << std::endl;
                    std::cout << ">>> ";
                    std::cin >> arg;
                }

                ToggleWindowsDefender(arg);
                break;
            }
            case 2:
                char arg;
                std::cout << TelemetryToggleText << std::endl << std::endl;
                std::cout << "[1] Disable Windows Telemetry" << std::endl << "[2] Enable Windows Telemetry" << std::endl << std::endl;
                std::cout << ">>> ";
                std::cin >> arg;

                // Validate the input in a do-while loop
                while(arg != '1' && arg != '2'){
                    std::cout << "Error || Invalid argument." << std::endl << std::endl;
                    std::cout <<  "[1] Disable Windows Telemetry" << std::endl << "[2] Enable Windows Telemetry" << std::endl;
                    std::cout << ">>> ";
                    std::cin >> arg;
                }

                ToggleWindowsTelemetry(arg);
                break;
            case 3:
                char option;
                std::cout << UpdatesToggleText << std::endl << std::endl;
                std::cout << "[1] Disable Windows Updates" << std::endl << "[2] Enable Windows Updates" << std::endl << std::endl;
                std::cout << ">>> ";
                std::cin >> option;

                // Validate the input in a do-while loop
                while(option != '1' && option != '2'){
                    std::cout << "Error || Invalid argument." << std::endl << std::endl;
                    std::cout <<  "[1] Disable Windows Updates" << std::endl << "[2] Enable Windows Updates" << std::endl;
                    std::cout << ">>> ";
                    std::cin >> option;
                }

                ToggleWindowsUpdates(option);
                break;
            case 4:
                //Do code
                break;
            case 5:
                //Do code
                break;
            default:
                std::cout << "Invalid choice. Restart the program!" << std::endl;
        }
            
        system("pause");
    }
    else
    {
        std::cout << "Sorry, this programm requires admin privileges. Restart it with admin privileges." << std::endl;
        RestartAsAdmin();
    }
    return 0;
}

void RetrunToMainMenu()
{
    char option;

    std::cout << "Would you like to return to main menu? (y/n): ";
    std::cin >> option;

    while(option != 'y' && option != 'n')
    {
        std::cout << "Would you like to return to main menu? (y/n): ";
        std::cin >> option;
    }

    if(option == 'y')
    {
        main();
    }
    else if(option == 'n')
    {
        system("exit");
    }
}

void ToggleWindowsDefender(const char arg) 
{
    HKEY key;
    LONG result;
    DWORD value;
    DWORD dataSize = sizeof(value);

    result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows Defender", 0, KEY_ALL_ACCESS, &key);
    if (result != ERROR_SUCCESS) 
    {
        std::cout << "Error || Failed to access Windows Defender registry." << std::endl;
    }

    if (arg == '1') 
    {
        value = 0;
        result = RegSetValueExW(key, L"DisableAntiSpyware", 0, REG_DWORD, reinterpret_cast<const BYTE*>(&value), dataSize);
        if (result == ERROR_SUCCESS) 
        {
            std::cout << "Success || Windows Defender disabled." << std::endl;
            std::cout << "DEVICE RESTART REQUIRED!" << std::endl << std::endl;
            RetrunToMainMenu();
        } 
        else 
        {
            std::cout << "Error || Failed to disable Windows Defender." << std::endl << std::endl;
            RetrunToMainMenu();
        }
    } 
    else if (arg == '2') 
    {
        value = 1;
        result = RegSetValueExW(key, L"DisableAntiSpyware", 0, REG_DWORD, reinterpret_cast<const BYTE*>(&value), dataSize);
        if (result == ERROR_SUCCESS) 
        {
            std::cout << "Success || Windows Defender enabled." << std::endl;
            std::cout << "DEVICE RESTART REQUIRED!" << std::endl << std::endl;
            RetrunToMainMenu();
        } 
        else 
        {
            std::cout << "Error || Failed to enable Windows Defender." << std::endl << std::endl;
            RetrunToMainMenu();
        }
    } 

    RegCloseKey(key);
}


void ToggleWindowsTelemetry(const char arg)
{
    HKEY hKey;
    LONG result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\DataCollection"), 0, KEY_ALL_ACCESS, &hKey);

    if (arg == '1')
    {
        if (result == ERROR_SUCCESS)
        {
            DWORD value = 0;
            result = RegSetValueEx(hKey, TEXT("AllowTelemetry"), 0, REG_DWORD, (const BYTE*)&value, sizeof(DWORD));
            if (result == ERROR_SUCCESS)
            {
                std::cout << "Success || Windows Telemetry Disabled." << std::endl;
                std::cout << "DEVICE RESTART REQUIRED!" << std::endl << std::endl;
                RetrunToMainMenu();
            }
            else
            {
                std::cout << "Error || Failed to disable Windows Telemetry." << std::endl;
                RetrunToMainMenu();
            }
        }
    }
    else if (arg == '2')
    {
        if (result == ERROR_SUCCESS)
        {
            DWORD value = 1;
            result = RegSetValueEx(hKey, TEXT("AllowTelemetry"), 0, REG_DWORD, (const BYTE*)&value, sizeof(DWORD));
            if (result == ERROR_SUCCESS)
            {
                std::cout << "Success || Windows Telemetry Enabled." << std::endl;
                std::cout << "DEVICE RESTART REQUIRED!" << std::endl << std::endl;
                RetrunToMainMenu();
            }
            else
            {
                std::cout << "Error || Failed to enable Windows Telemetry." << std::endl;
                RetrunToMainMenu();
            }
        }
    }
    RegCloseKey(hKey);
}

void ToggleWindowsUpdates(const char arg)
{
    HKEY hKey;
    DWORD dwValue = 0;
    DWORD dwSize = sizeof(DWORD);
    if (arg == '1')
    {
        RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\WindowsUpdate\\Auto Update"), 0, KEY_SET_VALUE, &hKey);
        RegSetValueEx(hKey, TEXT("AUOptions"), 0, REG_DWORD, (BYTE*)&dwValue, dwSize);
        std::cout << "Success || Windows Updates Disabled." << std::endl;
        std::cout << "DEVICE RESTART REQUIRED!" << std::endl << std::endl;
        RetrunToMainMenu();
    }
    else if (arg == '2')
    {
        RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\WindowsUpdate\\Auto Update"), 0, KEY_ALL_ACCESS, &hKey);
        RegDeleteValue(hKey, TEXT("AUOptions"));
        std::cout << "Success || Windows Updates Enabled." << std::endl;
        std::cout << "DEVICE RESTART REQUIRED!" << std::endl << std::endl;
        RetrunToMainMenu();
    }
    RegCloseKey(hKey);
}