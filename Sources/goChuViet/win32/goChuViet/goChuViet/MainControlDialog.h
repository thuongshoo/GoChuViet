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

class MainControlDialog : public BaseDialog {
private:
	HWND hTab, hTabPage1, hTabPage2, hTabPage3, hTabPage4;
	HWND comboBoxInputType;
	HWND comboBoxTableCode;
	HWND checkCtrl, checkAlt, checkWin, checkShift, textSwitchKey, checkBeep;
	HWND checkVietnamese, checkEnglish;
	HWND checkModernOrthorgraphy, checkFixRecommendBrowser, checkShowOnStartup, checkRunWithWindows,
		checkSpelling, checkRestoreIfWrongSpelling, checkUseClipboard, checkModernIcon,
		checkAllowZWJF, checkTempOffSpelling, checkQuickStartConsonant, checkQuickEndConsonant;
	HWND checkSmartSwitchKey, checkCapsFirstChar, checkQuickTelex, checkUseMacro, checkUseMacroInEnglish;
	HWND checkCreateDesktopShortcut, checkCheckNewVersion, checkRunAsAdmin, checkSupportMetroApp, checkMacroAutoCaps;
	HWND checkFixChromium, checkRememberTableCode, checkTempOffgoChuViet;
	HWND hUpdateButton;
private:
	void initDialog();
	void onComboBoxSelected(const HWND& hCombobox, const int& comboboxId);
	void onCheckboxClicked(const HWND& hWnd);
	void onCharacter(const HWND& hWnd, const UINT16& keyCode);
	void setSwitchKeyText(const HWND& hWnd, const UINT16 & keyCode);
	void onTabIndexChanged();
	void onUpdateButton();
	void requestRestartAsAdmin();
protected:
	INT_PTR eventProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static INT_PTR CALLBACK tabPageEventProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	MainControlDialog(const HINSTANCE& hInstance, const int& resourceId);
	virtual ~MainControlDialog();
	virtual void fillData() override;
	void setSwitchKey(const unsigned short& code);

	friend INT_PTR CALLBACK tabPageEventProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

