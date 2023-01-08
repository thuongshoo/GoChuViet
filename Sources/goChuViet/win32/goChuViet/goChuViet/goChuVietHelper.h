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
#pragma once
#include "stdafx.h"

extern int CF_RTF;
extern int CF_HTML;
extern int CF_OPENKEY;

class goChuVietHelper {
private:
	static void openKey();
public:
	static void setRegInt(LPCTSTR key, const int& val);
	static int getRegInt(LPCTSTR key, const int& defaultValue);

	static void setRegBinary(LPCTSTR key, const myByte_t* pData, const int& size);
	static myByte_t* getRegBinary(LPCTSTR key, DWORD& outSize);

	static void registerRunOnStartup(const int& val);

	static LPTSTR getExecutePath();

	static std::string& getFrontMostAppExecuteName();
	static std::string& getLastAppExecuteName();

	static std::wstring getFullPath();

	static std::wstring getClipboardText(const int& type);
	static void setClipboardText(LPCTSTR data, const int& len, const int& type);

	static bool quickConvert();

	static DWORD getVersionNumber();
	static std::wstring getVersionString();

	static std::wstring getContentOfUrl(LPCTSTR url);
};

