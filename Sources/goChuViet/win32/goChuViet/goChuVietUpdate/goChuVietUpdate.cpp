/*----------------------------------------------------------
GoChuViet - The Cross platform Open source Vietnamese Keyboard application.

Copyright (C) 2022 thuongshoo
Contact: yuyoonshoo@gmail.com
Github: https://github.com/thuongshoo/GoChuViet
Fanpage: https://www.youtube.com/channel/UCp6B47bJF90k1e16mAv59_w

This file is belong to the GoChuViet project, Win32 version
which is released under GPL license.
You can fork, modify, improve this program. If you
redistribute your new version, it MUST be open source.
-----------------------------------------------------------*/

#include "framework.h"
#include "goChuVietUpdate.h"
#include <Urlmon.h>
#include <fstream>
#include <sstream>
#include <string>
#pragma comment(lib, "Urlmon.lib")

#include <shellapi.h>
//using namespace std;
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;
INT_PTR CALLBACK MainDialogProcess(HWND, UINT, WPARAM, LPARAM);
void ReplaceFiles();
HWND hDlg;

std::wstring goChuVietUpdateStr = L"goChuVietUpdate";

static std::wstring GetProcessorArchitecture()
{
	SYSTEM_INFO si;
	GetNativeSystemInfo(&si);  // Gets the true system info regardless of WOW64

	switch (si.wProcessorArchitecture)
	{
	case PROCESSOR_ARCHITECTURE_AMD64: return L"x64";
	case PROCESSOR_ARCHITECTURE_ARM64: return L"arm64";
	case PROCESSOR_ARCHITECTURE_INTEL: return L"x86";
	default: return L"Unknown";
	}
}

static void RunHiddenCommand(const std::wstring& command, DWORD timeoutMs = 5000) {
	STARTUPINFOW si{ sizeof(si) };
	PROCESS_INFORMATION pi{};
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;

	CreateProcessW(nullptr,
		const_cast<LPWSTR>(command.c_str()),
		nullptr, nullptr, FALSE,
		CREATE_NO_WINDOW,
		nullptr, nullptr, &si, &pi);
	//wait for timeoutMs miliseconds
	WaitForSingleObject(pi.hProcess, timeoutMs);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

static void cleanFiles() {
	std::filesystem::path currentDir = std::filesystem::current_path();
	std::filesystem::path tempDir = currentDir;
	tempDir /= L"_" + goChuVietUpdateStr;
	
	std::filesystem::remove_all(tempDir);
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	// Parse command line
	int argc;
	LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);

	bool silentMode = false;
	bool updateMode = false;
	bool cleanMode = false;
	for (int i = 1; i < argc; ++i) {
		if (wcscmp(argv[i], L"--silent") == 0) silentMode = true;
		if (wcscmp(argv[i], L"--update") == 0) updateMode = true;
		if (wcscmp(argv[i], L"--clean") == 0)  cleanMode = true;
	}

	if (updateMode) {
		// Perform update logic
		if (!silentMode) {
			MessageBox(NULL, L"Installing updates...", L"Updater", MB_OK);
		}
		ReplaceFiles();
	}
	else if (cleanMode) {
		cleanFiles();
	}
	else
	{
		hDlg = CreateDialogParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG_UPDATER), 0, MainDialogProcess, 0);
		ShowWindow(hDlg, SW_SHOWNORMAL);

		MSG msg;
		// Main message loop:
		while (GetMessage(&msg, nullptr, 0, 0)) {
			if (!IsDialogMessage(hDlg, &msg)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}
	return 0;
}


void ReplaceFiles() {
	// Get the current working directory
	std::filesystem::path currentDir = std::filesystem::current_path();
	std::filesystem::path parentPath = currentDir.parent_path();

	
	WCHAR exePath[MAX_PATH]; // Buffer to store the executable path
	DWORD result = GetModuleFileName(NULL, exePath, MAX_PATH);

	if (result == 0) {
		// Handle error, GetModuleFileName failed
		std::cerr << "Error getting executable path: " << GetLastError() << std::endl;
		return ;
	}

	std::wstring fullPath(exePath);
	std::filesystem::path currentFile = fullPath;
	std::filesystem::copy(
		currentFile,
		parentPath,
		fs::copy_options::update_existing |
		fs::copy_options::overwrite_existing
	);

	// Get paths
	fs::path currentExe = exePath;
	fs::path parentDir = currentExe.parent_path().parent_path();
	fs::path newExe = parentDir / currentExe.filename();
	
	// Verify the copy succeeded
	if (!fs::exists(newExe)) {
		MessageBoxW(NULL, L"Failed to copy new version", L"Error", MB_ICONERROR);
		return;
	}

	// Change working directory to parent before launch
	if (!SetCurrentDirectoryW(parentDir.c_str())) {
		MessageBoxW(NULL, L"Failed to change working directory", L"Error", MB_ICONERROR);
		return;
	}
	// Launch new version
	std::wstring command = L"\"" + newExe.wstring() + L"\"";
	command.append(L" --clean");
	RunHiddenCommand(command, 0); // No wait needed since we'll exit immediately
	
}

DWORD WINAPI UpdateThreadFunction(LPVOID lpParam) {
	WCHAR currentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, currentDir);

	WCHAR path[MAX_PATH];

	wsprintf(path, TEXT("%s\\_goChuViet.tempf"), currentDir);
	HRESULT res = URLDownloadToFile(NULL, L"https://raw.githubusercontent.com/thuongshoo/GoChuViet/master/version.json", path, 0, NULL);

	std::wstring data;
	if (res == S_OK) {
		std::wifstream t(path);
		std::wstringstream buffer;
		buffer << t.rdbuf();
		t.close();
		DeleteFile(path);
		data = buffer.str();
	} else {
		MessageBox(hDlg, _T("Có lỗi trong quá trình cập nhật, vui lòng thử lại sau!"), _T("GoChuViet Update"), MB_OK);
		ExitProcess(0);
		return 0;
	}

	//simple parse
	data = data.substr(data.find(L"latestWinVersion"));
	data = data.substr(data.find(L"\"versionName\":"));
	data = data.substr(14);
	data = data.substr(data.find(L"\""));
	data = data.substr(1);
	std::wstring versionName = data.substr(0, data.find(L"\""));
	
	std::wstring platformName = GetProcessorArchitecture();
	
	std::wstring os = L"Windows";
	// calculate zip file name
	WCHAR updateUrl[MAX_PATH];
	wsprintf(updateUrl, TEXT("https://github.com/thuongshoo/GoChuViet/releases/download/%s/%s-%s.zip"),
		versionName.c_str(),
		os.c_str(),
		platformName.c_str());

	wsprintf(path, TEXT("%s\\_goChuVietUpdate.zip"), currentDir);
	res = URLDownloadToFile(NULL, updateUrl, path, 0, NULL);

	if (res == S_OK) {
		// extract zip file
		RunHiddenCommand(L"powershell.exe -NoP -NonI -Command \"Expand-Archive '.\\_goChuVietUpdate.zip' '.\\_goChuVietUpdate'\" ");
		//
		WCHAR fileName[MAX_PATH];
		wsprintf(fileName, TEXT("goChuViet-%s-%s.exe"),
			os.c_str(),
			platformName.c_str());
		// remove old file
		DeleteFile(fileName);

		WCHAR newFileName[MAX_PATH];
		wsprintf(newFileName, TEXT("_goChuVietUpdate\\%s"),
					fileName);
		// move goChuViet from temp folder to current folder
		MoveFile(newFileName, fileName);
		// delete the downloaded file
		DeleteFile(path);
		//
		WCHAR newUpdateFileName[MAX_PATH];
		wsprintf(newUpdateFileName, TEXT("_goChuVietUpdate\\goChuVietUpdate-%s-%s.exe"),
			os.c_str(),
			platformName.c_str());

		std::wstring cmd = L"\"";
		cmd.append(newUpdateFileName);
		cmd.append(L"\" --update");
		RunHiddenCommand(cmd);
		ExitProcess(0);
	} else {
		MessageBox(hDlg, _T("Có lỗi trong quá trình cập nhật, vui lòng thử lại sau!"), _T("GoChuViet Update"), MB_OK);
		ExitProcess(0);
	}
	return 0;
}

void StartUpdate() {
	DWORD hThread;
	HANDLE t = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		UpdateThreadFunction,       // thread function name
		0,          // argument to thread function 
		0,                      // use default creation flags 
		&hThread);   // returns the thread identifier 
}
// Message handler for about box.
INT_PTR CALLBACK MainDialogProcess(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message) {
	case WM_INITDIALOG: {
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_OPENKEYUPDATE));
		if (hIcon) {
			SendMessage(hDlg, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
		}
		StartUpdate();
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

