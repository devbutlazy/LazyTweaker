#pragma once

#include <Windows.h>
#include <iostream>

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


