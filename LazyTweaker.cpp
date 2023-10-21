#include <iostream>
#include <Windows.h>

#include "src/TweakerFunctions.h"
#include "src/AdditionalFunctions.h"
#include "src/ConstText.h"

#include <string>
#include <vector>
#include <cstdio>
#include <cstdint>



int main()
{
    bool returnToMainMenu = true;
    while(returnToMainMenu)
    {
        //system("pause");
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
                    while (choice < '1' || choice > '5') {
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
            char option;
            std::cout << "Would you like to return to the main menu? (y/n): ";
            std::cin >> option;

            while (option != 'y' && option != 'n') {
                std::cout << "Would you like to return to the main menu? (y/n): ";
                std::cin >> option;
            }

            returnToMainMenu = (option == 'n') ? false : true;
        }
        else
        {
            std::cout << "Sorry, this program requires admin privileges. Restart it with admin privileges." << std::endl;
            RestartAsAdmin();
            returnToMainMenu = false;
        }
    }

    return 0;
}