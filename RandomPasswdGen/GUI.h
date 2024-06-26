#ifndef GUI_H
#define GUI_H

/*
0x0080	Button
0x0081	Edit
0x0082	Static
0x0083	List box
0x0084	Scroll bar
0x0085	Combo box

#define CTL_BTN 0x0080
#define CTL_EDT 0x0081
#define CTL_STA 0x0082
#define CTL_LST 0x0083
#define CTL_SCB 0x0084
#define CTL_CBO 0x0085
*/
#define 按钮框	0x0080
#define 编辑框	0x0081
#define 静态框	0x0082
#define 列表框	0x0083
#define 滚动条	0x0084
#define 组合框	0x0085

#include <Windows.h>
#include <CommCtrl.h>

#ifndef T
#define T TEXT
#endif
#define Save(s) pw+=SaveTxt(s,pw)
#define Add(n,f,left,top,width,height,t,s) AddCtrl(&pw,n,f,left,top,width,height,t,s)
#define AddEx(n,f,left,top,width,height,t,s) AddCtrlEx(&pw,n,f,left,top,width,height,t,s)

PWORD pwAlign(PWORD);
VOID AddCtrl(PWORD *, WORD, DWORD, WORD, WORD, WORD, WORD, WORD, PTCHAR);
VOID AddCtrlEx(PWORD *, WORD, DWORD, WORD, WORD, WORD, WORD, PWSTR, PTCHAR);
DWORD SaveTxt(PTCHAR, PWORD);
DWORD SaveTxtW(PWORD, PWORD);

#endif
