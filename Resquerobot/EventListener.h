/**
* @file EventListener.h
* @brief メッセージクラッカー
* @author Iwata Naoki
* @date 2011-03-19
* @version 1.00
*
* Copyright (C) 2010 - TPIP User Community All rights reserved.
* このファイルの著作権は、TPIPユーザーコミュニティの規約に従い使用許諾をします。
*/


#ifndef __MSG_CRACKER_H__
#define __MSG_CRACKER_H__

#include <windows.h>

#define ID_MYTIMER 201 //!< @brief タイマーID


/** WM_CREATEのメッセージクラッカー */
BOOL onCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);

/** WM_ACTIVATEのメッセージクラッカー */
void onActivate(HWND hwnd, UINT state, HWND hwndActDeact, BOOL fMinimized);

/** WM_DESTROYのメッセージクラッカー */
void onDestroy(HWND hwnd);

/** WM_SIZEのメッセージクラッカー */
void onSize(HWND hwnd, UINT state, int cx, int cy);

/** WM_TIMERのメッセージクラッカー */
void onTimer(HWND hwnd, UINT id);

/** WM_KEYDOWNのメッセージクラッカー */
void onKeydown(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags);

/** WM_KEYUPのメッセージクラッカー */
void onKeyup(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags);

/** WM_PAINTのメッセージクラッカー */
void onPaint(HWND hwnd);

/** WM_LBUTTONDOWNのメッセージクラッカー */
void onLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);

/** WM_LBUTTONDBLCLKのメッセージクラッカー */
void onLButtonDblClk(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);

/** WM_LBUTTONUPのメッセージクラッカー */
void onLButtonUp(HWND hwnd, int x, int y, UINT keyFlags);

/** WM_RBUTTONDOWNのメッセージクラッカー */
void onRButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);

/** WM_RBUTTONDBLCLKのメッセージクラッカー */
void onRButtonDblClk(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);

/** WM_RBUTTONUPのメッセージクラッカー */
void onRButtonUp(HWND hwnd, int x, int y, UINT keyFlags);

/** WM_MOUSEMOVEのメッセージクラッカー */
void onMouseMove(HWND hwnd, int x, int y, UINT keyFlags);

/** WM_CLOSEのメッセージクラッカー */
void onClose(HWND hwnd);



#endif //__MSG_CRACKER_H__