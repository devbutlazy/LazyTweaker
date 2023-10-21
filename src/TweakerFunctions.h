#pragma once

#include <string>
#include "TweakerFunctions.cpp"

void ToggleWindowsDefender(const char arg);
void ToggleWindowsTelemetry(const char arg);
void ToggleWindowsUpdates(const char arg);
void ToggleWindowsContextMenu(const char arg);
bool UninstallApp(std::string appName, const char arg);
std::string GetPackageFullName(const std::string& appName);
void RunSystemCommand(const std::string& command);