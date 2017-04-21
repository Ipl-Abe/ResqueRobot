/**
* @file WindowManager.h
* @brief ウィンドウ管理
* @author Iwata Naoki
* @date 2011-03-19
* @version 1.00
*
* Copyright (C) 2010 - TPIP User Community All rights reserved.
* このファイルの著作権は、TPIPユーザーコミュニティの規約に従い使用許諾をします。
*/


#ifndef __WINDOW_MANAGER_H__
#define __WINDOW_MANAGER_H__

#include <Windows.h>
#include <WindowsX.h>

/** メインウィンドウの生成 */
extern HWND createMainWindow(HINSTANCE hInstance, const TCHAR* title, int x, int y, int w, int h);


#endif