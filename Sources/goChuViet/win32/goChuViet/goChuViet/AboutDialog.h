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
#include "BaseDialog.h"

class AboutDialog :	public BaseDialog {
protected:
	INT_PTR eventProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void initDialog();
public:
	AboutDialog(const HINSTANCE & hInstance, const int & resourceId);
	~AboutDialog();
	virtual void fillData() override;
private:
	HWND hUpdateButton;
	void onUpdateButton();
};