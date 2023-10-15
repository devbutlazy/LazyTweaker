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

const std::string DefenderToggleText = R"(
===============================================================
                    Toggle Windows Defender
===============================================================
)";


void ToggleWindowsDefender(const int arg);

int main()
{
    int choice;
    std::cout << MainWindowText << std::endl;
    std::cout << ">>> ";
    std::cin >> choice;

    switch(choice)
    {
        case 1:
            int arg;
            std::cout << DefenderToggleText << std::endl << std::endl;
            std::cout << "[1] Disable Windows Defender" << std::endl << "[2] Enable Windows Defender" << std::endl << std::endl;
            std::cout << ">>> ";
            std::cin >> arg;  
            ToggleWindowsDefender(arg);

            break;
        case 2:
            break;
    }
    
    system("pause");
    return 0;
}


void ToggleWindowsDefender(const int arg) 
{
    HKEY key;
    LONG result;
    DWORD value;
    DWORD dataSize = sizeof(value);

    result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows Defender", 0, KEY_ALL_ACCESS, &key);
    if (result != ERROR_SUCCESS) 
    {
        std::cout << "Error || Failed to access Windows Defender registry." << std::endl;
        return;
    }

    if (arg == 1) 
    {
        value = 0;
        result = RegSetValueExW(key, L"DisableAntiSpyware", 0, REG_DWORD, reinterpret_cast<const BYTE*>(&value), dataSize);
        if (result == ERROR_SUCCESS) 
        {
            std::cout << "Success || Windows Defender disabled." << std::endl << std::endl;
            main();
        } 
        else 
        {
            std::cout << "Error || Failed to disable Windows Defender." << std::endl << std::endl;
            main();
        }
    } 
    else if (arg == 2) 
    {
        value = 1;
        result = RegSetValueExW(key, L"DisableAntiSpyware", 0, REG_DWORD, reinterpret_cast<const BYTE*>(&value), dataSize);
        if (result == ERROR_SUCCESS) 
        {
            std::cout << "Success || Windows Defender enabled." << std::endl << std::endl;
            main();
        } 
        else 
        {
            std::cout << "Error || Failed to enable Windows Defender." << std::endl << std::endl;
            main();
        }
    } 
    else 
    //TODO: FIX THIS
    {
        int arg;    
        if (!arg == 1 && !arg == 2) 
        {
            ToggleWindowsDefender(arg);
        }
        else
        {
            std::cout << "Error || Invalid argument." << std::endl << "[1] Disable Windows Defender" << std::endl << "[2] Enable Windows Defender" << std::endl;
            std::cout << ">>> ";
            std::cin >> arg;
        }
    }

    RegCloseKey(key);
}