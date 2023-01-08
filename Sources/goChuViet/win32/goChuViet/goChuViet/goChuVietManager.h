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

class goChuVietManager {
public:
	static unsigned short _lastKeyCode;
	static std::vector<LPCTSTR>& getInputType();
	static std::vector<LPCTSTR>& getTableCode();

	static void initEngine();
	static void freeEngine();

	static bool checkUpdate(std::string& newVersion);

	static void createDesktopShortcut();
};