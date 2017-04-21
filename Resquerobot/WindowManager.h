/**
* @file WindowManager.h
* @brief �E�B���h�E�Ǘ�
* @author Iwata Naoki
* @date 2011-03-19
* @version 1.00
*
* Copyright (C) 2010 - TPIP User Community All rights reserved.
* ���̃t�@�C���̒��쌠�́ATPIP���[�U�[�R�~���j�e�B�̋K��ɏ]���g�p���������܂��B
*/


#ifndef __WINDOW_MANAGER_H__
#define __WINDOW_MANAGER_H__

#include <Windows.h>
#include <WindowsX.h>

/** ���C���E�B���h�E�̐��� */
extern HWND createMainWindow(HINSTANCE hInstance, const TCHAR* title, int x, int y, int w, int h);


#endif