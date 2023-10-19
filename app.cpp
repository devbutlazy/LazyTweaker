#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <cstdio>

#define LOGGING

const std::string MainWindowText = R"(
===============================================================
		    	Windows Tweaker
===============================================================
[1] Toggle Windows Defender (Enable/Disable)
[2] Toggle Telemetry (Enable/Disable)
[3] Toggle Windows Updates (Enable/Disable)
[4] Enable Windows 11 Old Context Menu
[5] Delete UWP Applications (OneDrive, Paint3D, XBOX, Cortana, Edge, FeedbackHub)
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

const std::string ContextMenuToggleText = R"(
===============================================================
                Toggle Context Menu
===============================================================
)";

const std::string UWPAppsToggleText = R"(
===============================================================
                UWP Apps Deletion
===============================================================
)";


void ToggleWindowsDefender(const char arg);
void ToggleWindowsTelemetry(const char arg);
void ToggleWindowsUpdates(const char arg);
void ToggleWindowsContextMenu(const char arg);
bool UninstallApp(const std::string& appName, const char arg);
bool UninstallApp(const std::string& appName, const char arg);
std::string GetPackageFullName(const std::string& appName);

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
            case 1: 
            {
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
            {
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
            }
            case 3:
            {
                char arg;
                std::cout << UpdatesToggleText << std::endl << std::endl;
                std::cout << "[1] Disable Windows Updates" << std::endl << "[2] Enable Windows Updates" << std::endl << std::endl;
                std::cout << ">>> ";
                std::cin >> arg;

                // Validate the input in a do-while loop
                while(arg != '1' && arg != '2'){
                    std::cout << "Error || Invalid argument." << std::endl << std::endl;
                    std::cout <<  "[1] Disable Windows Updates" << std::endl << "[2] Enable Windows Updates" << std::endl;
                    std::cout << ">>> ";
                    std::cin >> arg;
                }

                ToggleWindowsUpdates(arg);
                break;
            }
            case 4:
            {
                char arg;
                std::cout << ContextMenuToggleText << std::endl << std::endl;
                std::cout <<  "[1] Enable Windows 11 Old Context Menu" << std::endl << "[2] Disable Windows 11 Old Context Menu" << std::endl << std::endl;
                std::cout << ">>> ";
                std::cin >> arg;

                // Validate the input in a do-while loop
                while(arg != '1' && arg != '2'){
                    std::cout << "Error || Invalid argument." << std::endl << std::endl;
                    std::cout <<  "[1] Enable Windows 11 Old Context Menu" << std::endl << "[2] Disable Windows 11 Old Context Menu" << std::endl;
                    std::cout << ">>> ";
                    std::cin >> arg;
                }

                ToggleWindowsContextMenu(arg);

                break;
            }
            case 5:
            {
                char choice;
                std::cout << "Which UWP app would you like to uninstall?" << std::endl << std::endl;
                std::cout << "[1] OneDrive" << std::endl << "[2] Microsoft Edge" << std::endl;
                std::cout << "[3] Paint3D" << std::endl << "[4] XBOX" << std::endl;
                std::cout << "[5] Cortana" << std::endl << "[6] FeedbackHub" << std::endl << std::endl;
                std::cout << ">>> ";
                std::cin >> choice;

                // Validate the user's choice
                while (choice < '1' && choice > '5') {
                    std::cout << "Error: Invalid choice." << std::endl << std::endl;
                    std::cout << "[1] OneDrive" << std::endl << "[2] Microsoft Edge" << std::endl;
                    std::cout << "[3] Paint3D" << std::endl << "[4] XBOX" << std::endl;
                    std::cout << "[5] Cortana" << std::endl << "[6] FeedbackHub" << std::endl << std::endl;
                    std::cout << ">>> ";
                    std::cin >> choice;
                }

                switch(choice)
                {
                    case '1':
                        UninstallApp("Microsoft.OneDrive", choice);
                        break;
                    case '2':
                        UninstallApp("Microsoft.MicrosoftEdge", choice);
                        break;
                    case '3':
                        UninstallApp("Microsoft.MSPaint", choice);
                        break;
                    case '4':
                        UninstallApp("Microsoft.XboxApp", choice);
                        break;
                    case '5':
                        UninstallApp("Microsoft.549981C3F5F10", choice);;
                        break;
                    case '6':
                        UninstallApp("Microsoft.WindowsFeedbackHub", choice);
                        break;
                }

                break;
            }
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

void ToggleWindowsContextMenu(const char arg)
{
    HKEY hKey;
    LONG regResult;


    if (arg == '1')
    {
        LONG lResult = RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Software\\Classes\\CLSID\\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}"), 0, KEY_READ | KEY_WRITE, &hKey);

        // Set the default value of the registry key.
        lResult = RegSetValueEx(hKey, NULL, 0, REG_SZ, NULL, 0);

        HKEY hSubKey;
        lResult = RegCreateKeyEx(hKey, TEXT("InprocServer32"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE, NULL, &hSubKey, NULL);

        lResult = RegSetValueEx(hSubKey, NULL, 0, REG_SZ, NULL, 0);

        RegCloseKey(hSubKey);
        RegCloseKey(hKey);

        if (lResult == ERROR_SUCCESS) {
            std::cout << "Success || Windows 11 Old Context Menu Enabled." << std::endl;
            std::cout << "DEVICE RESTART REQUIRED!" << std::endl << std::endl;
            RetrunToMainMenu();
        }
        else {
            RegCloseKey(hSubKey);
            RegCloseKey(hKey);
            std::cout << "Error || Failed to enable Windows 11 Old Context Menu." << std::endl;
            RetrunToMainMenu();
        }
    }
    else if (arg == '2')
    {
        regResult = RegDeleteKey(HKEY_CURRENT_USER, TEXT("Software\\Classes\\CLSID\\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}\\InprocServer32"));

        // Delete the main key {86ca1aa0-34aa-4e8b-a509-50c905bae2a2}
        regResult = RegDeleteKey(HKEY_CURRENT_USER, TEXT("Software\\Classes\\CLSID\\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}"));
        
        if (regResult != ERROR_SUCCESS) {
            std::cout << "Success || Windows 11 Old Context Menu Disabled." << std::endl;
            std::cout << "DEVICE RESTART REQUIRED!" << std::endl << std::endl;
            RetrunToMainMenu();
        }
    }
    RegCloseKey(hKey);
}

std::string GetPackageFullName(const std::string& appName) {
    // Construct the command to get the package full name
    std::string getPkgFullNameCmd = "powershell -Command \"Get-AppxPackage | Where-Object {$_.NonRemovable -eq $False -and $_.Name -eq '" + appName + "'} | Select -ExpandProperty PackageFullName\"";
    
    // Execute the command and read the output
    char pkgFullName[256];
    FILE* pipe = _popen(getPkgFullNameCmd.c_str(), "r");
    
    // If the output is not empty
    if (fgets(pkgFullName, sizeof(pkgFullName), pipe) != nullptr) 
    {
        _pclose(pipe);
        size_t len = strlen(pkgFullName);
        
        // Remove the newline character from the end of the output
        if (pkgFullName[len - 1] == '\n') 
        {
            pkgFullName[len - 1] = '\0';
        }
        
        // Return the package full name
        return std::string(pkgFullName);
    } 
    else 
    {
        _pclose(pipe);
        
        // Return an empty string if the output is empty
        return "";
    }
}

bool UninstallApp(const std::string& appName, const char arg) {
    std::string pkgFullName = GetPackageFullName(appName);

    // Check if the package full name is not empty
    if (!pkgFullName.empty()) {
        // Construct the command to remove the app package
        std::string removePkgCmd = "powershell -Command \"Remove-AppxPackage -Package '" + pkgFullName + "'\"";
        
        // Execute the command and get the result
        int result = system(removePkgCmd.c_str());

        // Check if the removal was successful
        if (result == 0) 
        {
            std::cout << "Success || " << appName << " package removed successfully." << std::endl;
            RetrunToMainMenu();
            return true;
        } 
        else 
        {
            std::cout << "Error || " << "Failed to remove " << appName << " package." << std::endl;
            RetrunToMainMenu();
        }
    } 
    else 
    {
        std::cout << "Error || " << "Failed to retrieve the " << appName << " package full name." << std::endl;
        std::cout << "Probably, the app is already deleted from your device." << std::endl;
        RetrunToMainMenu();
    }
    return false;
}