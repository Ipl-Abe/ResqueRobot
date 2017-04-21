/**
* @file EventListener.h
* @brief ���b�Z�[�W�N���b�J�[
* @author Iwata Naoki
* @date 2011-03-19
* @version 1.00
*
* Copyright (C) 2010 - TPIP User Community All rights reserved.
* ���̃t�@�C���̒��쌠�́ATPIP���[�U�[�R�~���j�e�B�̋K��ɏ]���g�p���������܂��B
*/


#ifndef __MSG_CRACKER_H__
#define __MSG_CRACKER_H__

#include <windows.h>

#define ID_MYTIMER 201 //!< @brief �^�C�}�[ID


/** WM_CREATE�̃��b�Z�[�W�N���b�J�[ */
BOOL onCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);

/** WM_ACTIVATE�̃��b�Z�[�W�N���b�J�[ */
void onActivate(HWND hwnd, UINT state, HWND hwndActDeact, BOOL fMinimized);

/** WM_DESTROY�̃��b�Z�[�W�N���b�J�[ */
void onDestroy(HWND hwnd);

/** WM_SIZE�̃��b�Z�[�W�N���b�J�[ */
void onSize(HWND hwnd, UINT state, int cx, int cy);

/** WM_TIMER�̃��b�Z�[�W�N���b�J�[ */
void onTimer(HWND hwnd, UINT id);

/** WM_KEYDOWN�̃��b�Z�[�W�N���b�J�[ */
void onKeydown(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags);

/** WM_KEYUP�̃��b�Z�[�W�N���b�J�[ */
void onKeyup(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags);

/** WM_PAINT�̃��b�Z�[�W�N���b�J�[ */
void onPaint(HWND hwnd);

/** WM_LBUTTONDOWN�̃��b�Z�[�W�N���b�J�[ */
void onLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);

/** WM_LBUTTONDBLCLK�̃��b�Z�[�W�N���b�J�[ */
void onLButtonDblClk(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);

/** WM_LBUTTONUP�̃��b�Z�[�W�N���b�J�[ */
void onLButtonUp(HWND hwnd, int x, int y, UINT keyFlags);

/** WM_RBUTTONDOWN�̃��b�Z�[�W�N���b�J�[ */
void onRButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);

/** WM_RBUTTONDBLCLK�̃��b�Z�[�W�N���b�J�[ */
void onRButtonDblClk(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);

/** WM_RBUTTONUP�̃��b�Z�[�W�N���b�J�[ */
void onRButtonUp(HWND hwnd, int x, int y, UINT keyFlags);

/** WM_MOUSEMOVE�̃��b�Z�[�W�N���b�J�[ */
void onMouseMove(HWND hwnd, int x, int y, UINT keyFlags);

/** WM_CLOSE�̃��b�Z�[�W�N���b�J�[ */
void onClose(HWND hwnd);



#endif //__MSG_CRACKER_H__