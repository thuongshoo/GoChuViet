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

static std::wstring g_goChuVietUpdateStr = L"goChuVietUpdate";
static std::wstring g_cleanOptionStr = L"--clean";
static std::wstring g_replaceOptionStr = L"--replace";

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

static std::wstring GetCurrentProcessFilename() {
	wchar_t path[MAX_PATH] = { 0 };
	DWORD size = MAX_PATH;

	if (QueryFullProcessImageName(GetCurrentProcess(), 0, path, &size)) {
		wchar_t* filename = wcsrchr(path, L'\\');
		return filename ? filename + 1 : L"";
	}
	return L"";
}

static std::filesystem::path getModuleFileName() {
	WCHAR tmpExePath[MAX_PATH]; // Buffer to store the executable path
	DWORD result = GetModuleFileName(NULL, tmpExePath, MAX_PATH);
	if (result == 0) {
		// Handle error, GetModuleFileName failed
		//std::cerr << "Error getting executable path: " << GetLastError() << std::endl;
		return std::filesystem::path();
	}
	return std::filesystem::path(tmpExePath);
}

static void cleanFiles() {
	// calculate the directory which includes this process
	std::filesystem::path currentDir(getModuleFileName());
	currentDir = currentDir.parent_path();

	std::filesystem::path tempDir = currentDir;
	tempDir /= L"_" + g_goChuVietUpdateStr;
	//MessageBox(NULL, tempDir.c_str(), L"tempDir", MB_ICONERROR);
	std::filesystem::remove_all(tempDir);
}


void ReplaceFiles() {
	// calculate the directory which includes this process
	std::filesystem::path exePath(getModuleFileName());
	//MessageBox(NULL, exePath.c_str(), L"ReplaceFiles", MB_ICONERROR);
	std::filesystem::path currentDir(exePath);
	currentDir = currentDir.parent_path();
	std::filesystem::path parentDir = currentDir.parent_path();
	

	std::wstring fullPath(exePath);
	std::filesystem::path currentFile = fullPath;
	//MessageBox(NULL, currentDir.c_str(), L"currentDir", MB_ICONERROR);
	//MessageBox(NULL, parentDir.c_str(), L"parentDir", MB_ICONERROR);
	for (const auto& entry : fs::directory_iterator(currentDir)) {
		std::error_code ec;
		fs::copy(entry.path(), 
			parentDir / entry.path().filename(),
			//fs::copy_options::update_existing |
			fs::copy_options::overwrite_existing |
			fs::copy_options::recursive,
			ec);
		if ( 0 != ec.value()) {
			std::wstring errorMessage = L"Không thể cập nhật tập tin này vì nó đang chạy. Nên thoát tất cả rồi cập nhật lại ";
			errorMessage  += entry.path().c_str();

			std::wstring errorMessageFromSystem(ec.message().begin(), ec.message().end());
			errorMessage += L":";
			errorMessage += errorMessageFromSystem;

			MessageBox(NULL, errorMessage.c_str(), L"Lỗi cập nhật", MB_ICONERROR);
		}

	}
	
	fs::path newExe = parentDir / exePath.filename();
	//MessageBox(NULL, newExe.c_str(), L"newExe", MB_ICONERROR);
	// Verify the copy succeeded
	if (!fs::exists(newExe)) {
		std::wstring msg = L"Failed to copy new version:";
		MessageBox(NULL, msg.c_str(), L"Error", MB_ICONERROR);

		msg = L"currentDir=" + currentDir.wstring() + L" ";
		MessageBox(NULL, msg.c_str(), L"currentDir", MB_ICONERROR);

		msg = L"newExe=" + newExe.wstring() + L" ";
		MessageBox(NULL, msg.c_str(), L"newExe", MB_ICONERROR);
		
		return;
	}

	// Launch new version
	std::wstring command = L"\"";
	command.append(newExe.wstring());
	command.append(L"\"");
	command.append(L" ");
	command.append(g_cleanOptionStr);

	//MessageBox(NULL, command.c_str(), L"ReplaceFiles command", MB_ICONERROR);
	RunHiddenCommand(command, 0); // No wait needed since we'll exit immediately
}

static HRESULT downloadFile(WCHAR *currentDir, std::wstring &versionName, std::wstring &os, std::wstring &platformName,
	std::wstring& filename)
{
	WCHAR outputFileName[MAX_PATH];
	wsprintf(outputFileName, TEXT("%s-%s-%s.exe"),
		filename.c_str(),
		os.c_str(),
		platformName.c_str());

	WCHAR updateUrl[MAX_PATH];
	wsprintf(updateUrl, TEXT("https://github.com/thuongshoo/GoChuViet/releases/download/%s/%s"),
		versionName.c_str(),
		outputFileName);

	WCHAR tempFolder[MAX_PATH];
	wsprintf(tempFolder, TEXT("%s\\_%s"), currentDir, g_goChuVietUpdateStr.c_str());
	CreateDirectory(tempFolder, NULL);

	WCHAR downloadFileName[MAX_PATH];
	wsprintf(downloadFileName, TEXT("%s\\%s"), tempFolder, outputFileName);
	// return new fullpath file name
	filename = downloadFileName;
	return URLDownloadToFile(NULL, updateUrl, downloadFileName, 0, NULL);
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
	} 
	else {
		MessageBox(hDlg, _T("Có lỗi trong quá trình cập nhật, vui lòng thử lại sau! 1"), _T("GoChuViet Update"), MB_OK);
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
	std::wstring filename = L"goChuViet";
	res = downloadFile(currentDir, versionName, os, platformName, filename);
	if (res != S_OK) {
		std::wstring msg = L"Không thể tải về: ";
		msg += filename;
		msg += L" ";
		msg += L"Có lỗi trong quá trình cập nhật, vui lòng thử lại sau!";
		msg += L" ";
		MessageBox(hDlg, msg.c_str(), _T("GoChuViet Error"), MB_OK);
		ExitProcess(0);
	}
	//MessageBox(hDlg, filename.c_str(), _T("GoChuViet successfull"), MB_OK);
	filename = g_goChuVietUpdateStr;
	HRESULT res2 = downloadFile(currentDir, versionName, os, platformName, filename);
	if (res2 == S_OK) {
		std::wstring cmd = L"\"";
		cmd.append(filename);
		cmd.append(L"\"");
		cmd.append(L" ");
		cmd.append(g_replaceOptionStr);
		
		//MessageBox(hDlg, cmd.c_str(), _T("UpdateThreadFunction cmd"), MB_OK);
		RunHiddenCommand(cmd, 0);
	}
	else {
		std::wstring msg = L"Không thể tải về: ";
		msg += filename;
		msg += L" ";
		msg += L"Có lỗi trong quá trình cập nhật, vui lòng thử lại sau!";
		MessageBox(hDlg, msg.c_str(), _T("GoChuViet Error"), MB_OK);
	}
	ExitProcess(0);
	
	return 0;
}

void StartUpdate() {
	//MessageBox(NULL, L"StartUpdate", L"StartUpdate", MB_OK);
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
		//MessageBox(NULL, L"StartUpdate", L"MainDialogProcess", MB_OK);
		StartUpdate();
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			DestroyWindow(hDlg);// , LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	
	case WM_DESTROY:
		PostQuitMessage(0);  // Important for modeless dialogs
		return TRUE;
	}
	return (INT_PTR)FALSE;
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

	std::filesystem::path exePath(getModuleFileName());

	//bool silentMode = false;
	bool replaceMode = false;
	bool cleanMode = false;
	for (int i = 1; i < argc; ++i) {
		//if (wcscmp(argv[i], L"--silent") == 0) silentMode = true;
		if (wcscmp(argv[i], g_replaceOptionStr.c_str()) == 0) replaceMode = true;
		if (wcscmp(argv[i], g_cleanOptionStr.c_str()) == 0)  cleanMode = true;
	}

	if (replaceMode) {
		// Perform update logic
		/*if (!silentMode) {
			MessageBox(NULL, L"Installing updates...", L"Updater", MB_OK);
		}*/
		//MessgeBox(NULL, exePath.c_str(), L"replaceMode", MB_OK);
		Sleep(1000);
		ReplaceFiles();
		return 0;
	}

	if (cleanMode) {
		//MessageBox(NULL, exePath.c_str(), L"cleanMode", MB_OK);
		Sleep(1000);
		cleanFiles();
		return 0;
	}
	else
	{
		//MessageBox(NULL, exePath.c_str(), L"mainMode", MB_OK); 
		hDlg = CreateDialogParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG_UPDATER), 0, MainDialogProcess, 0);
		ShowWindow(hDlg, SW_SHOWNORMAL);

		MSG msg;
		// Main message loop:
		while (GetMessage(&msg, nullptr, 0, 0)) {			
			if (!IsDialogMessage(hDlg, &msg)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			if (!IsWindow(hDlg)) {
				break;
			}
		}

	}
	return 0;
}
