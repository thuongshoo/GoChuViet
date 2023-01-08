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

class MacroDialog :	public BaseDialog {
private:
	HWND listMacro;
	HWND hMacroName, hMacroContent;
	HWND hAddButton, hAutoCaps;
	std::vector<std::vector<Uint32>> keys;
	std::vector<std::string> macroText;
	std::vector<std::string> macroContent;
public:
	MacroDialog(const HINSTANCE & hInstance, const int & resourceId);
	~MacroDialog();
	virtual void fillData() override;
protected:
	INT_PTR eventProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void initDialog();
private:
	void saveAndReload();
	void insertItem(const int& index, LPTSTR macroName, LPTSTR macroContent);

	void onSelectItem(const int& index);
	void onAddMacroButton();
	void onDeleteMacroButton();

	void onImportMacroButton();
	void onExportMacrobutton();

	void onCheckboxClicked(const HWND& hWnd);
};

