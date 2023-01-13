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

class SystemTrayHelper {
private:
	static void CALLBACK WaitToCreateFakeWindow(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime);
	static HWND createFakeWindow(const HINSTANCE& hIns);
	static void createPopupMenu();

	static void _createSystemTrayIcon(const HINSTANCE& hIns);
public:
	static void createSystemTrayIcon(const HINSTANCE& hIns);
	static void updateData();
	static void removeSystemTray();
};

