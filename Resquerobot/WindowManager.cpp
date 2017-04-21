/**
* @file WindowManager.cpp
* @brief �E�B���h�E�̐�����R�[���o�b�N�̓o�^���s��
* @author Iwata Naoki
* @date 2011-03-19
* @version 1.00
* @version 1.01 2013/03/22 katayama
*
* Copyright (C) 2010 - TPIP User Community All rights reserved.
* ���̃t�@�C���̒��쌠�́ATPIP���[�U�[�R�~���j�e�B�̋K��ɏ]���g�p���������܂��B
*/


/*--------- include ---------*/

#include "WindowManager.h"
#include "EventListener.h"

/*--------- �֐���` ---------*/

/**
* �E�B���h�E�̃C�x���g�̃R�[���o�b�N\n
* �C�x���g�̏����̓��b�Z�[�W�N���b�J�[���g�p���čs���̂ŁA\n
* �����̎�����@link EventListener.cpp @endlink�ōs��
*
* @param[in] hwnd    �E�B���h�E�n���h��
* @param[in] message �R�[���o�b�N�̃��b�Z�[�W�ԍ�
* @param[in] wParam  �C�x���g�̃p�����[�^
* @param[in] lParam  �C�x���g�̃p�����[�^
*
* @see http://msdn.microsoft.com/en-us/library/ms633573(VS.85).aspx
*
*/
static LRESULT CALLBACK wndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message) {
		// ���b�Z�[�W�N���b�J�[
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
* ���C����ʐ���\n
* ���C����ʂ𐶐����A�n���h����Ԃ�
*
* @param[in] hInstance �C���X�^���X
* @param[in] title     �E�B���h�E�̃^�C�g��
* @param[in] x         �X�N���[����ɃE�B���h�E��\�����鍶��X���W�̈ʒu
* @param[in] y         �E�B���h�E����Y���W
* @param[in] w         �E�B���h�E����
* @param[in] h         �E�B���h�E�c��
*
* @return �E�B���h�E�n���h��
*
*/
extern HWND createMainWindow(HINSTANCE hInstance, const TCHAR* title, int x, int y, int w, int h) {

	WNDCLASS wc; // �E�B���h�E�N���X�����\����
	HWND     hWnd;     // �E�B���h�E�n���h��

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

	// Window�̐���
	hWnd = CreateWindow(className, title, WS_OVERLAPPEDWINDOW, x, y, w, h, NULL, NULL, hInstance, NULL);

	return hWnd;

}
