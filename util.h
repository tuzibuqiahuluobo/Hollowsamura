#pragma once

#include <graphics.h>

#pragma comment(lib, "WINMM.lib")
#pragma comment(lib, "MSIMG32.lib")


struct Rect
{
	int x, y;
	int w, h;
};

inline void putimage_ex(IMAGE* img, const Rect* rect_dst, const Rect* rect_src = nullptr)
{
	// 定义混合函数，用于AlphaBlend函数
	static BLENDFUNCTION blend_func = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	// 调用AlphaBlend函数进行图像混合
	AlphaBlend(
		GetImageHDC(GetWorkingImage()), // 目标设备上下文句柄
		rect_dst->x, rect_dst->y, rect_dst->w, rect_dst->h,// 目标矩形区域
		GetImageHDC(img), // 源设备上下文句柄
		rect_src ? rect_src->x : 0, rect_src ? rect_src->y : 0,// 源矩形区域的起始坐标
		rect_src ? rect_src->w : img->getwidth(),// 源矩形区域的宽度
		rect_src ? rect_src->h : img->getheight(),// 源矩形区域的高度
		blend_func // 混合函数
	);
}

inline void load_audio(LPCTSTR path, LPCTSTR id)
{
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("open %s alias %s"), path, id);
	mciSendString(str_cmd, NULL, 0, NULL);
}

inline void play_audio(LPCTSTR id, bool loop = false)
{
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("play %s %s from 0"), id, loop ? _T("repeat") : _T(""));
	mciSendString(str_cmd, NULL, 0, NULL);
}

inline void stop_audio(LPCTSTR id)
{
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("stop %s"), id);
	mciSendString(str_cmd, NULL, 0, NULL);
}





