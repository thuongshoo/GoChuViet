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
#include "goChuVietManager.h"
#include <shlobj.h>

static std::vector<LPCTSTR> _inputType = {
	_T("Telex"),
	_T("VNI"),
	_T("Simple Telex"),
};

static std::vector<LPCTSTR> _tableCode = {
	_T("Unicode"),
	_T("TCVN3 (ABC)"),
	_T("VNI Windows"),
	_T("Unicode Tổ hợp"),
	_T("Vietnamese Locale CP 1258")
};

/*-----------------------------------------------------------------------*/

extern void goChuVietInit();
extern void goChuVietFree();

unsigned short  goChuVietManager::_lastKeyCode = 0;

std::vector<LPCTSTR>& goChuVietManager::getInputType() {
	return _inputType;
}

std::vector<LPCTSTR>& goChuVietManager::getTableCode() {
	return _tableCode;
}

void goChuVietManager::initEngine() {
	goChuVietInit();
}

void goChuVietManager::freeEngine() {
	goChuVietFree();
}

bool goChuVietManager::checkUpdate(std::string& newVersion) {
	std::wstring dataW = goChuVietHelper::getContentOfUrl(L"https://raw.githubusercontent.com/thuongshoo/GoChuViet/master/version.json");
	std::string data = wideStringToUtf8(dataW);

	//simple parse
	data = data.substr(data.find("latestWinVersion"));
	data = data.substr(data.find("\"versionName\":"));
	data = data.substr(14);
	data = data.substr(data.find("\""));
	data = data.substr(1);
	std::string versionName = data.substr(0, data.find("\""));
	newVersion = versionName;
	data = data.substr(data.find("\"versionCode\":"));
	data = data.substr(14);
	std::string versionCodeString = data.substr(0, data.find("}"));
	DWORD versionCode = (DWORD)atoi(versionCodeString.c_str());
	DWORD currentVersion = goChuVietHelper::getVersionNumber();
	versionCode = (versionCode << 16) | (versionCode & 0x00FF00) | (versionCode >> 16 & 0xFF);
	currentVersion = (currentVersion << 16) | (currentVersion & 0x00FF00) | (currentVersion >> 16 & 0xFF);
	if (versionCode > currentVersion) {
		return true;
	}
	return false;
}

void goChuVietManager::createDesktopShortcut() {
	CoInitialize(NULL);
	IShellLink* pShellLink = NULL;
	HRESULT hres;
	hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_ALL,
							IID_IShellLink, (void**)&pShellLink);
	if (SUCCEEDED(hres)) {
		std::wstring path = goChuVietHelper::getFullPath();
		pShellLink->SetPath(path.c_str());
		pShellLink->SetDescription(_T("GoChuViet - Bộ gõ Tiếng Việt"));
		pShellLink->SetIconLocation(path.c_str(), 0);

		IPersistFile* pPersistFile;
		hres = pShellLink->QueryInterface(IID_IPersistFile, (void**)&pPersistFile);

		if (SUCCEEDED(hres)) {
			wchar_t desktopPath[MAX_PATH + 1];
			wchar_t savePath[MAX_PATH + 10];
			SHGetFolderPath(NULL, CSIDL_DESKTOP, NULL, 0, desktopPath);
			wsprintf(savePath, _T("%s\\GoChuViet.lnk"), desktopPath);
			/*hres = */ pPersistFile->Save(savePath, TRUE);
			pPersistFile->Release();
			pShellLink->Release();
		}
	}
}
