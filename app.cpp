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


int main()
{
    std::cout << MainWindowText << std::endl;
    
    system("pause");
    return 0;
}