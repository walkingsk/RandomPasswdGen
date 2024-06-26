#include <Windows.h>
#include "GUI.h"


PWORD pwAlign(PWORD lpIn)
{
	ULONG ul = (ULONG)lpIn;
	ul += 3;
	ul >>= 2;
	ul <<= 2;
	return (PWORD)ul;
}
DWORD SaveTxt(PTCHAR pSrc, PWORD pDst)
{
	DWORD i;
	for (i = 0;; ++pSrc, ++pDst)
	{
		++i;
		*pDst = *pSrc;
		if (!*pSrc)
			break;
	}
	return i;
}
DWORD SaveTxtW(PWORD pSrc, PWORD pDst)
{
	DWORD i;
	for (i = 0;; ++pSrc, ++pDst)
	{
		++i;
		*pDst = *pSrc;
		if (!*pSrc)
			break;
	}
	return i;
}
/*
 * AddCtrl 和 AddCtrlEx 对最后一个形式参数支持 ANSI 和 Unicode 字串
 * 但由于 PDLGITEMTEMPLATEA 和 PDLGITEMTEMPLATEW 是完全一致的
 * 并且 Unicode 已成主流
 * 支持 TCHAR 的 SaveTxt 对待 ANSI MBCS 字串仅仅简单直接二进制转换为 Unicode 字串
 * 并未取当前代码页 使用 MultiByteToWideChar
 * 因此，实际上未真正支持 ANSI MBCS 字串
 */
VOID AddCtrl(PWORD *ppw, WORD dwId, DWORD dwStyle, WORD x, WORD y, WORD cx, WORD cy, WORD wAtom, PTCHAR sInitText)
{
	PDLGITEMTEMPLATE pdit;
	*ppw = pwAlign(*ppw);

	pdit = (PDLGITEMTEMPLATE)(*ppw);
	pdit->id = dwId;
	pdit->style = dwStyle;
	pdit->dwExtendedStyle = 0;
	pdit->x = x;
	pdit->y = y;
	pdit->cx = cx;
	pdit->cy = cy;

	*ppw = (PWORD)(pdit + 1);
	*(*ppw)++ = 0xFFFF;
	*(*ppw)++ = wAtom;

	(*ppw) += SaveTxt(sInitText, *ppw);

	*(*ppw)++ = 0; // No Creation Data
}
VOID AddCtrlEx(PWORD *ppw, WORD dwId, DWORD dwStyle, WORD x, WORD y, WORD cx, WORD cy, PWSTR sCtrl, PTCHAR sInitText)
{
	PDLGITEMTEMPLATE pdit;
	*ppw = pwAlign(*ppw);

	pdit = (PDLGITEMTEMPLATE)(*ppw);
	pdit->id = dwId;
	pdit->style = dwStyle;
	pdit->dwExtendedStyle = 0;
	pdit->x = x;
	pdit->y = y;
	pdit->cx = cx;
	pdit->cy = cy;

	*ppw = (PWORD)(pdit + 1);

	(*ppw) += SaveTxtW(sCtrl, *ppw);
	(*ppw) += SaveTxt(sInitText, *ppw);

	*(*ppw)++ = 0; // No Creation Data
}
