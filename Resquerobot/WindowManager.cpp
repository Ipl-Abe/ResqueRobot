/**
* @file WindowManager.cpp
* @brief ウィンドウの生成やコールバックの登録を行う
* @author Iwata Naoki
* @date 2011-03-19
* @version 1.00
* @version 1.01 2013/03/22 katayama
*
* Copyright (C) 2010 - TPIP User Community All rights reserved.
* このファイルの著作権は、TPIPユーザーコミュニティの規約に従い使用許諾をします。
*/


/*--------- include ---------*/

#include "WindowManager.h"
#include "EventListener.h"

/*--------- 関数定義 ---------*/

/**
* ウィンドウのイベントのコールバック\n
* イベントの処理はメッセージクラッカーを使用して行うので、\n
* 処理の実装は@link EventListener.cpp @endlinkで行う
*
* @param[in] hwnd    ウィンドウハンドル
* @param[in] message コールバックのメッセージ番号
* @param[in] wParam  イベントのパラメータ
* @param[in] lParam  イベントのパラメータ
*
* @see http://msdn.microsoft.com/en-us/library/ms633573(VS.85).aspx
*
*/
static LRESULT CALLBACK wndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message) {
		// メッセージクラッカー
		HANDLE_MSG(hwnd, WM_CREATE, onCreate);
		HANDLE_MSG(hwnd, WM_CLOSE, onClose);
		HANDLE_MSG(hwnd, WM_DESTROY, onDestroy);
		HANDLE_MSG(hwnd, WM_SIZE, onSize);
		HANDLE_MSG(hwnd, WM_TIMER, onTimer);
		HANDLE_MSG(hwnd, WM_KEYDOWN, onKeydown);
		HANDLE_MSG(hwnd, WM_KEYUP, onKeyup);
		HANDLE_MSG(hwnd, WM_PAINT, onPaint);
		HANDLE_MSG(hwnd, WM_LBUTTONDOWN, onLButtonDown);
		HANDLE_MSG(hwnd, WM_LBUTTONUP, onLButtonUp);
		HANDLE_MSG(hwnd, WM_LBUTTONDBLCLK, onLButtonDblClk);
		HANDLE_MSG(hwnd, WM_RBUTTONDOWN, onRButtonDown);
		HANDLE_MSG(hwnd, WM_RBUTTONUP, onRButtonUp);
		HANDLE_MSG(hwnd, WM_RBUTTONDBLCLK, onRButtonDblClk);
		HANDLE_MSG(hwnd, WM_MOUSEMOVE, onMouseMove);
	default:
		break;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}


/**
* メイン画面生成\n
* メイン画面を生成し、ハンドルを返す
*
* @param[in] hInstance インスタンス
* @param[in] title     ウィンドウのタイトル
* @param[in] x         スクリーン上にウィンドウを表示する左上X座標の位置
* @param[in] y         ウィンドウ左上Y座標
* @param[in] w         ウィンドウ横幅
* @param[in] h         ウィンドウ縦幅
*
* @return ウィンドウハンドル
*
*/
extern HWND createMainWindow(HINSTANCE hInstance, const TCHAR* title, int x, int y, int w, int h) {

	WNDCLASS wc; // ウィンドウクラス属性構造体
	HWND     hWnd;     // ウィンドウハンドラ

	TCHAR    className[] = TEXT("MAIN");

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = wndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = className;

	if (!RegisterClass(&wc)) {
		MessageBox(NULL, TEXT("This program requires Windows NT!"), className, MB_ICONERROR);
		return 0;
	}

	// Windowの生成
	hWnd = CreateWindow(className, title, WS_OVERLAPPEDWINDOW, x, y, w, h, NULL, NULL, hInstance, NULL);

	return hWnd;

}
