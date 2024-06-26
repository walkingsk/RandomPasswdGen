#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include "GUI.h"
/*
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
*/
#define 生成按钮			1001
#define 退出按钮			1002
#define 编辑框_随机密码	1003
#define 选取密码长度		1004
#define 定时器			1005
// #define 应用图标			1006

#define 数字0_9类型1		0
#define 数字0_9类型2		1
#define 特殊字符类型		2
#define 大写A_Z类型1		3
#define 大写A_Z类型2		4
#define 小写a_z类型1		5
#define 小写a_z类型2		6

#define 字符总数			518

HWND hEdit;
DWORD nStart, nEnd;
HWND hStatic;
TCHAR sLen[4];
TCHAR sSigns[] = T("#$%&_");
TCHAR sRandomPasswd[字符总数];

// HICON hIcon;

VOID FixIndex(DWORD *n)
{
	DWORD nLines = *n / 52;
	if (nLines)
	{
		*n -= nLines * 2;
	}
}

VOID RandomGenerate()
{
	int i;
	int t;

	srand(GetTickCount());
	for (i = 0; i < 字符总数; ++i)
	{
		if ((i + 2) % 52 == 0)
		{
			sRandomPasswd[i++] = '\r';
			sRandomPasswd[i] = '\n';
		}
		else
		{
			t = rand() % 7;
			switch (t)
			{
			case 0:
			case 1:
				sRandomPasswd[i] = rand() % 10 + '0';
				break;

			case 2:
				sRandomPasswd[i] = sSigns[rand() % 5];
				break;

			case 3:
			case 4:
				sRandomPasswd[i] = rand() % 26 + 'A';
				break;

			case 5:
			case 6:
				sRandomPasswd[i] = rand() % 26 + 'a';
				break;

			default:
				break;
			}
		}
	}

	SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sRandomPasswd);
}
VOID UpdateSelectedLength()
{
	SendMessage(hEdit, EM_GETSEL, (WPARAM)&nStart, (LPARAM)&nEnd);
	FixIndex(&nEnd);
	FixIndex(&nStart);
	// wsprintf(sLen, T("%d - %d = %d"), nEnd, nStart, nEnd - nStart);
	wsprintf(sLen, T("%d"), nEnd - nStart);
	SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)sLen);
}

LRESULT CALLBACK DlgFunc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		// SendMessage(hDlg, WM_SETICON, ICON_BIG, (LPARAM)ExtractIcon((HINSTANCE)GetModuleHandle(NULL), T("%SystemRoot%\\system32\\Appwiz.cpl"), 1));
		// hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(应用图标));
		// SendMessage(hDlg, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
		// SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
		SetTimer(hDlg, 定时器, 100, NULL);
		hEdit = GetDlgItem(hDlg, 编辑框_随机密码);
		hStatic = GetDlgItem(hDlg, 选取密码长度);
		RandomGenerate();
		break;
		
	case WM_COMMAND:
		if (HIWORD(wParam) == BN_CLICKED)
		{
			switch (LOWORD(wParam))
			{
			case 生成按钮:
				RandomGenerate();
				break;
			case 退出按钮:
				goto Exit;

			default:
				break;
			}
		}
		break;

	case WM_TIMER:
		switch (wParam)
		{
		case 定时器:
			UpdateSelectedLength();
			break;

		default:
			break;
		}
		break;

	Exit:
	case WM_CLOSE:
		KillTimer(hDlg, 定时器);
		EndDialog(hDlg, IDCANCEL);
		break;

	default:
		break;
	}
	return 0;
}

VOID DlgMain()
{
	CHAR cBuf[1024];
	LPDLGTEMPLATE pdt;
	PWORD pw;

	pdt = (LPDLGTEMPLATE) cBuf;

	pdt->style = DS_CENTER | DS_SETFONT | DS_NOFAILCREATE | DS_MODALFRAME | WS_POPUP | WS_VISIBLE | WS_MINIMIZEBOX | WS_SYSMENU | WS_CAPTION;
	pdt->dwExtendedStyle = 0;
	pdt->cdit = 4;
	pdt->x = 0;
	pdt->y = 0;
	pdt->cx = 225;
	pdt->cy = 111;
	// sizeof(DLGTEMPLATE)=18
	pw = (PWORD)(pdt + 1);
	*pw++ = 0; // No menu
	*pw++ = 0; // Predefined dialog box
	//
	Save(T("RandomPasswdGen"));
	//
	*pw++ = 11;
	Save(T("Consolas"));
	Add(生成按钮, BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 101, 94, 60, 14, 按钮框, T("&Generate"));
	Add(退出按钮, BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 161, 94, 60, 14, 按钮框, T("E&xit"));
	//
	Add(编辑框_随机密码, ES_AUTOVSCROLL | ES_MULTILINE | ES_CENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_VSCROLL, 5, 8, 215, 83, 编辑框, T(""));
	//
	Add(选取密码长度, SS_LEFT | WS_CHILD | WS_VISIBLE, 10, 97, 40, 14, 静态框, T(""));

	DialogBoxIndirectParam(NULL, pdt, NULL, (DLGPROC) DlgFunc, 0);
}
VOID EntryPoint()
{
	DlgMain();

	ExitProcess(0);
}
