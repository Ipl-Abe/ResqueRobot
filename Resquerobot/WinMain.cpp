/**
* @file WinMain.cpp
* @brief WIN32 API�𗘗p�����v���O�����̃G���g���[�|�C���g�p���W���[��
* @author Iwata Naoki -> Y.Katayama
* @date 2011-03-19
* @version 1.00
* @version 1.01 2013/03/21 katayama
*
* Copyright (C) 2008 TPIP User Community All rights reserved.
* ���̃t�@�C���̒��쌠�́ATPIP���[�U�[�R�~���j�e�B�̋K��ɏ]���g�p���������܂��B
*/

/** \mainpage
* 2015�N�u�K��T���v��
*/


/*--------- �萔��` ---------*/

#define TITLE         ("Robot_3")    //!< @brief �A�v���P�[�V�����̃^�C�g��
#define WINDOW_WIDTH  (1200)                    //!< @brief �E�B���h�E�̉���
#define WINDOW_HEIGHT ( 650)                    //!< @brief �E�B���h�E�̏c��

#define IP            ("192.168.2.103")		//3���@

/*--------- include ---------*/

#include <Windows.h>        // Win32API�֌W

#include "TPIP3.h"          // TPIP�֌W

#include "WindowManager.h"  // �E�B���h�E�֌W



/*--------- �֐���` ---------*/

/**
* �T�u�V�X�e����Windows�ɂ����ۂ̃v���O�����̃G���g���[�|�C���g(��ԍŏ��Ɏ��s�����֐�)\n
* �C�x���g�̏�����@link EventListener.cpp @endlink�Ŏ�������
*
* @param[in] hInstance     ���݂̃C���X�^���X
* @param[in] hPrevInstance �ȑO�̃C���X�^���X
* @param[in] szCmdLine     �R�}���h���C������
* @param[in] iCmdShow      �E�B���h�E�̕\�����@
*
* @see http://msdn.microsoft.com/en-us/library/ms633559(VS.85).aspx
*
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {


	HWND hwnd; // �E�B���h�E�n���h��
	MSG  msg;  // �C�x���g�̃��b�Z�[�W
	TCHAR title[] = TEXT("robot_3");
	hwnd = createMainWindow(hInstance, title, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);	// �E�B���h�E�̐���

	TPGM_create(hwnd, VGA, NULL);	// �摜��ԁi�T�[�t�F�C�X�j�𐶐�����
	TPGC_init(hInstance, hwnd);		// �Q�[���R���g���[�����͊֐��̏�����

	TPJT_set_video_inf(VGA);		// �J�����f���̉𑜓x���w�肷��
	TPJT_init(IP, hwnd);			// �ʐM��̐ݒ�
	TPJT_set_com_req(0x03, 0);		// �ʐM���e�̐ݒ�

	ShowWindow(hwnd, iCmdShow);		// �E�B���h�E�̕\��

	// �C�x���g����������
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}
	return msg.wParam;
}