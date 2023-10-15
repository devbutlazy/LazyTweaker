#include <iostream>
#include <Windows.h>
#include <string>

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

void ToggleWindowsDefender(const int arg) {
    HKEY key;
    LONG result;
    DWORD value;
    DWORD dataSize = sizeof(value);

    // Open the Windows Defender registry key
    result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows Defender", 0, KEY_ALL_ACCESS, &key);

    // Check if the key was opened successfully
    if (result == ERROR_SUCCESS) 
    {
        if (arg == 1) 
        {
            value = 0;
            // Disable Windows Defender by setting the "DisableAntiSpyware" value to 0
            result = RegSetValueExW(key, L"DisableAntiSpyware", 0, REG_DWORD, reinterpret_cast<const BYTE*>(&value), dataSize);
            if (result == ERROR_SUCCESS) 
            {
                std::cout << "Success || Windows Defender disabled." << std::endl;
            } else 
            {
                std::cout << "Error || Failed to disable Windows Defender." << std::endl;
            }
        } 
        else if (arg == 2) 
        {
            value = 1;
            // Enable Windows Defender by setting the "DisableAntiSpyware" value to 1
            result = RegSetValueExW(key, L"DisableAntiSpyware", 0, REG_DWORD, reinterpret_cast<const BYTE*>(&value), dataSize);
            if (result == ERROR_SUCCESS) 
            {
                std::cout << "Success || Windows Defender enabled." << std::endl;
            } else 
            {
                std::cout << "Error || Failed to enable Windows Defender." << std::endl;
            }
        } 
        else 
        {
            // Invalid argument
            std::cout << "Error || Invalid argument." << std::endl << "[1] Disable Windows Defender" << std::endl << "[2] Enable Windows Defender" << std::endl;
        }
        // Close the registry key
        RegCloseKey(key);
    } 
    else 
    {
        std::cout << "Error || Failed to access Windows Defender registry." << std::endl;
    }
}

int main()
{
    int choice;
    std::cout << MainWindowText << std::endl;
    std::cout << ">>>";
    std::cin >> choice;

    switch(choice)
    {
        case 1:
            int arg;
            std::cout << R"(
===============================================================
                    Toggle Windows Defender
===============================================================
            )" << std::endl << std::endl;
            std::cout << "[1] Disable Windows Defender" << std::endl << "[2] Enable Windows Defender" << std::endl;
            std::cout << ">>>";
            std::cin >> arg;  
            ToggleWindowsDefender(arg);

            break;
        case 2:
            break;
    }
    
    system("pause");
    return 0;
}