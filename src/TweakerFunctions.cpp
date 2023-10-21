#include "TweakerFunctions.h"

#include <iostream>
#include <Windows.h>

#include <string>
#include <vector>
#include <cstdio>
#include <cstdint>

// TOGGLE WINDOWS DEFENDER

void ToggleWindowsDefender(const char arg)
{
    HKEY key;
    LONG result;
    DWORD value;
    DWORD dataSize = sizeof(value);
    uint32_t payload = 1;
    
    if (arg == '1') 
    {
        try
        {
            if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Policies\\Microsoft\\Windows Defender"), 0, KEY_ALL_ACCESS, &key) == ERROR_SUCCESS)
            {
                RegSetValueEx(key, TEXT("DisableAntiSpyware"), 0, REG_DWORD, (LPBYTE)&payload, sizeof(payload));

                HKEY subkey;
                if (RegCreateKeyEx(key, TEXT("Real-Time Protection"), 0, 0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, 0, &subkey, 0) == ERROR_SUCCESS)
                {
                    RegSetValueEx(subkey, TEXT("DisableRealtimeMonitoring"), 0, REG_DWORD, (LPBYTE)&payload, sizeof(payload));
                    RegSetValueEx(subkey, TEXT("DisableBehaviorMonitoring"), 0, REG_DWORD, (LPBYTE)&payload, sizeof(payload));
                    RegSetValueEx(subkey, TEXT("DisableOnAccessProtection"), 0, REG_DWORD, (LPBYTE)&payload, sizeof(payload));
                    RegSetValueEx(subkey, TEXT("DisableScanOnRealtimeEnable"), 0, REG_DWORD, (LPBYTE)&payload, sizeof(payload));
                    RegSetValueEx(subkey, TEXT("DisableIOAVProtection"), 0, REG_DWORD, (LPBYTE)&payload, sizeof(payload));
                    RegCloseKey(subkey);

                    std::cout << "Success || Windows Defender disabled." << std::endl;
                    std::cout << "DEVICE RESTART REQUIRED!" << std::endl << std::endl;
                    
                }
                else
                {
                    std::cout << "Error || Failed to create Real-Time Protection subkey." << std::endl << std::endl;
                    
                }

                RegCloseKey(key);
            }
            else
            {
                std::cout << "Error || Failed to open Windows Defender key." << std::endl << std::endl;
                
            }
        }
        catch (const std::exception& e)
        {
            std::cout << "Error || Failed to disable Windows Defender." << std::endl << std::endl;
            
        }
    } 
    else if (arg == '2') 
    {
        try
        {
            // Open the Windows Defender key
            if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Policies\\Microsoft\\Windows Defender"), 0, KEY_ALL_ACCESS, &key) != ERROR_SUCCESS) 
            {
                std::cout << "Error || Failed to open Windows Defender key." << std::endl;
                
            }

            // Delete the registry values
            RegDeleteValue(key, TEXT("DisableAntiSpyware"));
            
            HKEY subkey;
            if (RegOpenKeyEx(key, TEXT("Real-Time Protection"), 0, KEY_ALL_ACCESS, &subkey) == ERROR_SUCCESS) 
            {
                RegDeleteValue(subkey, TEXT("DisableRealtimeMonitoring"));
                RegDeleteValue(subkey, TEXT("DisableBehaviorMonitoring"));
                RegDeleteValue(subkey, TEXT("DisableOnAccessProtection"));
                RegDeleteValue(subkey, TEXT("DisableScanOnRealtimeEnable"));
                RegDeleteValue(subkey, TEXT("DisableIOAVProtection"));
                RegCloseKey(subkey);
            }

            // Delete the "Real-Time Protection" subkey
            RegDeleteKey(key, TEXT("Real-Time Protection"));

            std::cout << "Success || Windows Defender enabled." << std::endl;
            std::cout << "DEVICE RESTART REQUIRED!" << std::endl << std::endl;
            std::cout << "DEVICE RESTART MAY BE REQUIRED!" << std::endl << std::endl;
            
        }
        catch (const std::exception& e)
        {
            std::cout << "Error || Failed to enable Windows Defender." << std::endl << std::endl;
            
        }
    }

    RegCloseKey(key);
}

//TOGGLE WINDOWS TELEMETRY

void ToggleWindowsTelemetry(const char arg) {
    HKEY hKey;
    LONG result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\DataCollection"), 0, KEY_ALL_ACCESS, &hKey);

    if (result != ERROR_SUCCESS) 
    {
        std::cout << "Error || Failed to open the registry key." << std::endl;
    }

    if (arg == '1') 
    {
        DWORD value = 0;
        result = RegSetValueEx(hKey, TEXT("AllowTelemetry"), 0, REG_DWORD, (const BYTE*)&value, sizeof(DWORD));
        if (result == ERROR_SUCCESS) 
        {
            system("sc stop DiagTrack > NUL 2>&1");
            system("sc config DiagTrack start= disabled > NUL 2>&1");
            system("sc stop dmwappushservice > NUL 2>&1");
            system("sc config dmwappushservice start= disabled > NUL 2>&1");

            std::cout << "Success || Windows Telemetry Disabled." << std::endl;
            std::cout << "DEVICE RESTART REQUIRED!" << std::endl << std::endl;
        } 
        else 
        {
            std::cout << "Error || Failed to disable Windows Telemetry." << std::endl;
        }
    } 
    else if (arg == '2') 
    {
        DWORD defaultValue = 1;
        result = RegSetValueEx(hKey, TEXT("AllowTelemetry"), 0, REG_DWORD, (const BYTE*)&defaultValue, sizeof(DWORD));

        if (result == ERROR_SUCCESS) 
        {
            system("sc start DiagTrack > NUL 2>&1");
            system("sc config DiagTrack start= auto > NUL 2>&1");
            system("sc start dmwappushservice > NUL 2>&1");
            system("sc config dmwappushservice start= auto > NUL 2>&1");

            std::cout << "Success || Windows Telemetry Enabled." << std::endl;
            std::cout << "DEVICE RESTART REQUIRED!" << std::endl << std::endl;
        } 
        else 
        {
            std::cout << "Error || Failed to Enable Windows Telemetry." << std::endl;
        }
    }

    RegCloseKey(hKey);
}

//TOGGLE WINDOWS UPDATES

void ToggleWindowsUpdates(const char arg)
{
    HKEY hKey;
    DWORD dwValue = 0;
    DWORD dwSize = sizeof(DWORD);
    if (arg == '1')
    {
        RegSetKeyValue(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Services\\WaaSMedicSvc"), TEXT("Start"), REG_DWORD, L"4", sizeof(L"4"));
        RegSetKeyValue(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Services\\WaaSMedicSvc"), TEXT("FailureActions"), REG_BINARY, NULL, 0);
        RegSetKeyValue(HKEY_LOCAL_MACHINE, TEXT("Software\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU"), TEXT("NoAutoUpdate"), REG_DWORD, L"1", sizeof(L"1"));
        // Delete downloaded update files
        DeleteFile(TEXT("C:\\Windows\\SoftwareDistribution\\*.*"));
        RemoveDirectory(TEXT("C:\\Windows\\SoftwareDistribution"));
        // Disable update related scheduled tasks
        system("powershell -command \"Get-ScheduledTask -TaskPath '\\Microsoft\\Windows\\InstallService\\*' | Disable-ScheduledTask; Get-ScheduledTask -TaskPath '\\Microsoft\\Windows\\UpdateOrchestrator\\*' | Disable-ScheduledTask; Get-ScheduledTask -TaskPath '\\Microsoft\\Windows\\UpdateAssistant\\*' | Disable-ScheduledTask; Get-ScheduledTask -TaskPath '\\Microsoft\\Windows\\WaaSMedic\\*' | Disable-ScheduledTask; Get-ScheduledTask -TaskPath '\\Microsoft\\Windows\\WindowsUpdate\\*' | Disable-ScheduledTask; Get-ScheduledTask -TaskPath '\\Microsoft\\WindowsUpdate\\*' | Disable-ScheduledTask\"");

        std::cout << "Success || Windows Updates Disabled." << std::endl;
        std::cout << "DEVICE RESTART REQUIRED!" << std::endl << std::endl;
        
    }
    else if (arg == '2')
    {
        RegSetKeyValue(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Services\\WaaSMedicSvc"), TEXT("Start"), REG_DWORD, L"2", sizeof(L"2"));
        // If you have the original failureActions, set them back here.
        // RegSetKeyValue(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Services\\WaaSMedicSvc", L"FailureActions", REG_BINARY, originalFailureActions, sizeof(originalFailureActions));
        RegSetKeyValue(HKEY_LOCAL_MACHINE, TEXT("Software\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU"), TEXT("NoAutoUpdate"), REG_DWORD, L"0", sizeof(L"0"));
        // Re-enable update related scheduled tasks if they were disabled
        system("powershell -command \"Get-ScheduledTask -TaskPath '\\Microsoft\\Windows\\InstallService\\*' | Enable-ScheduledTask; Get-ScheduledTask -TaskPath '\\Microsoft\\Windows\\UpdateOrchestrator\\*' | Enable-ScheduledTask; Get-ScheduledTask -TaskPath '\\Microsoft\\Windows\\UpdateAssistant\\*' | Enable-ScheduledTask; Get-ScheduledTask -TaskPath '\\Microsoft\\Windows\\WaaSMedic\\*' | Enable-ScheduledTask; Get-ScheduledTask -TaskPath '\\Microsoft\\Windows\\WindowsUpdate\\*' | Enable-ScheduledTask; Get-ScheduledTask -TaskPath '\\Microsoft\\WindowsUpdate\\*' | Enable-ScheduledTask\"");
        
        std::cout << "Success || Windows Updates Enabled." << std::endl;
        std::cout << "DEVICE RESTART REQUIRED!" << std::endl << std::endl;
        
    }
    RegCloseKey(hKey);
}

//TOGGLE WINDOWS 11 OLD CONTEXT MENU

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
            
        }
        else {
            RegCloseKey(hSubKey);
            RegCloseKey(hKey);
            std::cout << "Error || Failed to enable Windows 11 Old Context Menu." << std::endl;
            
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
            
        }
    }
    RegCloseKey(hKey);
}

//DELETE UWP PROGRAMS

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

bool UninstallApp(std::string appName, const char arg) {
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
            return true;
        } 
        else 
        {
            std::cout << "Error || " << "Failed to remove " << appName << " package." << std::endl;
        }
    } 
    else 
    {
        std::cout << "Error || " << "Failed to retrieve the " << appName << " package full name." << std::endl;
        std::cout << "Probably, the app is already deleted from your device." << std::endl;
    }
    return false;
}