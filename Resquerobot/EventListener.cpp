#define __CV_H__
/*-------- include --------*/
#include "TPIP3.h"           // TPIP�֌W
#include "EventListener.h"   // �E�B���h�E�̃C�x���g�����֌W
#include "cvMat2HDC.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <vector>
#include <fstream>
#include <sys/types.h>
#include <stdio.h>
#pragma  warning(disable:4996)	//	�Z�L�����e�B���ア�Â��֐��ɑ΂���x���̉���


//#include <winsock2.h>
//#include<winsock2.h>
//#include<ws2tcpip.h>

//#pragma comment( lib, "wsock32.lib" )
//#pragma comment( lib, "ws2_32.lib")

#define WIDTH 640
#define HEIGHT 480
#define AXIS_MAX 32767
#define AXIS_MIN -32768

/*-------- �����o�ϐ���` --------*/
static struct GC_STRUCT  mPad;		//!< @brief �Q�[���p�b�h���̓f�[�^
static struct OUT_DT_STR mOutDt;	//!< @brief TPJT�ň���������
static struct INP_DT_STR mInpDt;	//!< @brief TPJT�ň����Z���T�[���
static int    updatePaint;			//!< @brief onPaint �X�V�t���O(0:�X�V�ρ@1:���X�V)
int flag, flag2, button_flag = 0;
DWORD nBegin = ::GetTickCount();  //@comment �v���O�����N�����̃V�X�e���̎��Ԃ�ێ�
DWORD start, end;					//@comment �V�X�e���N�����ԕێ��p�ϐ�
//@comment �R���g���[���[GUI�摜��\������
cvMat2HDC ctrl[12];
//@comment ���A���A���A�~�̈ʒu
const int circlePos[4][2] = { { 1055, 480 }, { 990, 550 }, { 1115, 550 }, { 1055, 620 } };
//@comment�@�����L�[�̈ʒu
const int rec1Pos[2][2] = { { 740, 480 }, { 740, 620 } };
const int rec2Pos[2][2] = { { 670, 550 }, { 800, 550 } };
//@comemnt l1, l2, r1, r2�̈ʒu
const int lrPos[4][2] = { { 700, 300 }, { 700, 370 }, { 1020, 300 }, { 1020, 370 } };
//@comment �R���g���[���[��������Ă��邩
bool ctrlFlg[12] = { false, false, false, false, false, false, false, false, false, false, false, false };
enum CTRL_BUTTON{
	TRGL = 0,
	RCTG = 1,
	CRCL = 2,
	CRSS = 3,
	L1 = 5,
	L2 = 4,
	R1 = 7,
	R2 = 6,
	UP = 8,
	DOWN = 9,
	RGHT = 10,
	LEFT = 11
};


/*-------- �֐���` --------*/
//@comment �R���g���[���[GUI�̉摜�̈ʒu�̏�����
void initCtrlGUI()
{
	//@comment ���{�^��
	for (int i = 0; i < 4; i++){
		ctrl[i].setRendPos(circlePos[i][0], circlePos[i][1]);
	}
	//@comment lr�{�^��
	for (int i = 0; i < 4; i++){
		ctrl[i + 4].setRendPos(lrPos[i][0], lrPos[i][1]);
	}
	//@comment rect1�{�^��
	for (int i = 0; i < 2; i++){
		ctrl[i + 8].setRendPos(rec1Pos[i][0], rec1Pos[i][1]);
	}
	//@comment lr�{�^��
	for (int i = 0; i < 2; i++){
		ctrl[i + 10].setRendPos(rec2Pos[i][0], rec2Pos[i][1]);
	}
}

//@comment �R���g���[���[GUI�ւ̉�����Ă��邩�ǂ����̃t���O�ύX
void switchButtons()
{
	//@comment R1
	if (mPad.Button[7] == 128){ ctrlFlg[R1] = true; }
	else{ ctrlFlg[R1] = false; }

	//@comment L1
	if (mPad.Button[6] == 128){ ctrlFlg[L1] = true; }
	else{ ctrlFlg[L1] = false; }

	//@comment R1
	if (mPad.Button[5] == 128){ ctrlFlg[R2] = true; }
	else{ ctrlFlg[R2] = false; }

	//@comment L1
	if (mPad.Button[4] == 128){ ctrlFlg[L2] = true; }
	else{ ctrlFlg[L2] = false; }

	//@comment Triangle
	if (mPad.Button[0] == 128){ ctrlFlg[TRGL] = true; }
	else{ ctrlFlg[TRGL] = false; }

	//@comment Circle
	if (mPad.Button[1] == 128){ ctrlFlg[CRCL] = true; }
	else{ ctrlFlg[CRCL] = false; }

	//@comment Cross
	if (mPad.Button[2] == 128){ ctrlFlg[CRSS] = true; }
	else{ ctrlFlg[CRSS] = false; }

	//@comment Rectangle
	if (mPad.Button[3] == 128){ ctrlFlg[RCTG] = true; }
	else{ ctrlFlg[RCTG] = false; }

	//@comment ������
	if (mPad.POV[0] == 0){ ctrlFlg[UP] = true; }
	else{ ctrlFlg[UP] = false; }

	//@comment �������
	if (mPad.POV[0] == 18000){ ctrlFlg[DOWN] = true; }
	else{ ctrlFlg[DOWN] = false; }

	//@comment �������
	if (mPad.POV[0] == 27000){ ctrlFlg[RGHT] = true; }
	else{ ctrlFlg[RGHT] = false; }

	//@comment �E�����
	if (mPad.POV[0] == 9000){ ctrlFlg[LEFT] = true; }
	else{ ctrlFlg[LEFT] = false; }
}

//@comment �R���g���[���[GUI�̕`��
void rendController()
{
	for (int i = 0; i < 12; i++){
		ctrl[i].setHDC();
	}
	//@comment ���{�^��
	for (int i = 0; i < 4; i++){
		if (ctrlFlg[i]){ ctrl[i].load("./img/circle_on"); }
		else{ ctrl[i].load("./img/circle"); }
	}
	//@comment lr�{�^��
	for (int i = 0; i < 4; i++){
		if (ctrlFlg[i + 4]){ ctrl[i + 4].load("./img/lr_on"); }
		else{ ctrl[i + 4].load("img/lr"); }
	}
	//@comment rect1�{�^��
	for (int i = 0; i < 2; i++){
		if (ctrlFlg[i + 8]){ ctrl[i + 8].load("./img/rect_1_on"); }
		else{ ctrl[i + 8].load("./img/rect_1"); }
	}
	//@comment lr�{�^��
	for (int i = 0; i < 2; i++){
		if (ctrlFlg[i + 10]){ ctrl[i + 10].load("./img/rect_2_on"); }
		else{ ctrl[i + 10].load("./img/rect_2"); }
	}

	for (int i = 0; i < 12; i++){
		ctrl[i].releaseHDC();
	}
}

/**
* WM_CREATE�̃��b�Z�[�W�N���b�J�[\n
* �E�B���h�E�����������O�ɃR�[�������֐�\n
* �����Ő��������^�C�}�[�𗘗p���ATPIP�Ƃ̒ʐM�A��ʂ̕`��̃C�x���g�𔭐����܂�
*
* @param[in]  hwnd            �C�x���g�����������E�B���h�E�̃n���h��
* @param[in]  lpCreateStruct  �E�B���h�E�쐬���̃p�����[�^
*
* @retval ���TRUE
*
* @see http://msdn.microsoft.com/en-us/library/ms632619(VS.85).aspx
*
*/
BOOL onCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct) {


	TPJT_set_ctrl(&mOutDt, sizeof(mOutDt));	// ����o�̓f�[�^�Z�b�g

	SetTimer(hwnd, ID_MYTIMER, 60, NULL);	// �^�C�}�[�𐶐�����
	initCtrlGUI();
	return TRUE; //������FALSE(0)�ɂ���ƃ��b�Z�[�W��Destroy���Ă΂��
}


/**
* WM_ACTIVATE�̃��b�Z�[�W�N���b�J�[\n
* �E�B���h�E���A�N�e�B�u/��A�N�e�B�u�ɂȂ�ۂɃR�[�������֐�
*
* @param[in] hwnd          �C�x���g�����������E�B���h�E�̃n���h��
* @param[in] state         �E�B���h�E���A�N�e�B�u/��A�N�e�B�u���̏��
* @param[in] hwndActDeact  �E�B���h�E�̃n���h��\n
*                            state == 0�̏ꍇ�́A�V�����A�N�e�B�u�ɂȂ����E�B���h�E�̃n���h��\n
*                            state != 0�̏ꍇ�́A����܂ŃA�N�e�B�u�ł������E�B���h�E�̃n���h��
* @param[in] fMinimized    �E�B���h�E���ŏ�������Ă��邩�̔���t���O\n
*                            0�ȊO�̒l�̏ꍇ�̓E�B���h�E�͍ŏ�������Ă��܂�\n
*                            0�̏ꍇ�̓E�B���h�E�͍ŏ�������Ă��܂���\n
*
* @see http://msdn.microsoft.com/ja-jp/library/ms646274(d=lightweight).aspx
*
*/
void onActivate(HWND hwnd, UINT state, HWND hwndActDeact, BOOL fMinimized) {
	return;
}



/**
* WM_CLOSE�̃��b�Z�[�W�N���b�J�[\n
* �E�B���h�E���A�v���P�[�V�������I������ۂɃR�[�������֐�\n
* �I���̊m�F���s���AYES�Ȃ�΃E�B���h�E��j������BNO�Ȃ�Δj�����Ȃ�
*
* @param[in] hwnd  �C�x���g�����������E�B���h�E�̃n���h��
*
* @see http://msdn.microsoft.com/en-us/library/ms632617(VS.85).aspx
*
*/
void onClose(HWND hwnd) {

	int ans = 0; // �߂�l�擾�p

	// ���b�Z�[�W�_�C�A���O��\�����A�I���̊m�F������
	ans = MessageBox(hwnd, TEXT("�I�����܂����H"), TEXT("�I���m�F"), MB_YESNO | MB_ICONEXCLAMATION);

	// YES���I�����ꂽ�ꍇ�̓E�B���h�E�����
	if (ans == IDYES) {
		DestroyWindow(hwnd); // �E�C���h�E�����֐�
	}

	return;
}



/**
* WM_DESTROY�̃��b�Z�[�W�N���b�J�[\n
* �E�B���h�E���j�������ۂɃR�[�������֐�\n
* TPIP���C�u�����Ɛ��������^�C�}�[�̉�����s��
*
* @param[in]  hwnd �C�x���g�����������E�B���h�E�̃n���h��
*
* @see http://msdn.microsoft.com/en-us/library/ms632620(VS.85).aspx
*
*/
void onDestroy(HWND hwnd) {

	// TPIP���C�u�����Q�̉��
	TPGM_delete();
	TPGC_close();
	TPJT_close();

	//�^�C�}�[���
	KillTimer(hwnd, ID_MYTIMER);
	PostQuitMessage(0);

	return;
}



/**
* WM_SIZE�̃��b�Z�[�W�N���b�J�[\n
* �E�B���h�E�̃T�C�Y���ύX���ꂽ��ɃR�[�������֐�\n
* TPGM�Ŏg�p���Ă���T�[�t�F�C�X��ύX��̃T�C�Y�ō\��������
*
* @param[in]  hwnd  �C�x���g�����������E�B���h�E�̃n���h��
* @param[in]  state �T�C�Y�ύX�̃^�C�v
* @param[in]  cx    �E�B���h�E�̉���
* @param[in]  cy    �E�B���h�E�̏c��
*
* @see http://msdn.microsoft.com/en-us/library/ms632646(v=vs.85).aspx
*
*/
void onSize(HWND hwnd, UINT state, int cx, int cy) {

	// �T�[�t�F�C�X�̍č\��
	TPGM_delete();
	TPGM_create(hwnd, QVGA, NULL);

	return;
}



/**
* WM_TIMER�̃��b�Z�[�W�N���b�J�[\n
* �^�C�}�[���I�������ۂɃR�[�������֐�\n
* �Q�[���p�b�h����̓��́ATPIP�Ƃ̒ʐM�A��ʂ̕`5��̃C�x���g�𔭐�����\n
* ����f�[�^�̉��H����TPJT_set_ctrl()�����s����܂łɍs������
*
* @param[in]  hwnd �C�x���g�����������E�B���h�E�̃n���h��1
* @param[in]  id   �C�x���g���N�������^�C�}�[ID
*
* @see http://msdn.microsoft.com/en-us/library/ms644902(VS.85).aspx
*
*/
void onTimer(HWND hwnd, UINT id) {
	if (id == ID_MYTIMER) {		// �\�����Ȃ��^�C�}�[����̃C�x���g�͖�������

		TPGC_get(&mPad);		// �Q�[���p�b�h����̓��͂��擾

		TPJT_get_sens(&mInpDt, sizeof(mInpDt));	// �Z���T���͂��擾

		//@comment GUI��̃R���g���[���\����ύX
		//switchButtons();

		// R�P�{�^������
		//if (mPad.Button[5] == 128){
		//flag2 += 1;
		//Sleep(300);
		//if (flag2 == 3){
		//flag2 = 0;
		//}
		//}
		//@comment start�{�^��,select�{�^���ŃJ�����؂�ւ�

		if (mPad.Button[8] == 128){
			//if (cameraFlg){
			TPJT_chg_camera(0);
			//cameraFlg = false;
		}

		if (mPad.Button[9] == 128){
			TPJT_chg_camera(1);
			//cameraFlg = true;
		}

		//@comment �A�[���֐�
		if (mPad.Button[6] == 128){
			if (mOutDt.PWM[0] >= 800)
			{
				mOutDt.PWM[0] = 800;
			}
			else
			{
				mOutDt.PWM[0] += 20;
			}
			TPJT_set_ctrl(&mOutDt, sizeof(mOutDt));	// ����o�̓f�[�^�Z�b�g
		}
		if (mPad.Button[4] == 128){
			if (mOutDt.PWM[0] <= -500)
			{
				mOutDt.PWM[0] = -500;
			}
			else
			{
				mOutDt.PWM[0] -= 20;
			}
			TPJT_set_ctrl(&mOutDt, sizeof(mOutDt));
		}
		//@comment �J�����p�x
		if (mPad.Button[5] == 128){
			if (mOutDt.PWM[1] >= 800)
			{
				mOutDt.PWM[1] = 800;
			}
			else
			{
				mOutDt.PWM[1] += 30;
			}
			TPJT_set_ctrl(&mOutDt, sizeof(mOutDt));
		}
		if (mPad.Button[7] == 128){
			if (mOutDt.PWM[1] <= -800)
			{
				mOutDt.PWM[1] = -800;
			}
			else
			{
				mOutDt.PWM[1] -= 30;
			}
			TPJT_set_ctrl(&mOutDt, sizeof(mOutDt));
		}
		//@comment ���[�^PWM
		if (mPad.POV[0] == 0){

			if (mOutDt.PWM[3] >= 650)
			{
				mOutDt.PWM[3] = 650;
			}
			else
			{
				mOutDt.PWM[3] += 50;
			}
			TPJT_set_ctrl(&mOutDt, sizeof(mOutDt));
		}
		if (mPad.POV[0] == 18000){

			if (mOutDt.PWM[3] <= 0)
			{
				mOutDt.PWM[3] = 0;
			}
			else
			{
				mOutDt.PWM[3] -= 50;
			}
			TPJT_set_ctrl(&mOutDt, sizeof(mOutDt));
		}


		/*
		if (mPad.POV[0] == 0){    //������
		flag = 1;
		mOutDt.d_out = 5;	// d_out��D1��D3��1�o��
		TPJT_set_ctrl(&mOutDt, sizeof(mOutDt));	// ����o�̓f�[�^�Z�b�g
		}
		if (mPad.POV[0] == 18000){   //�������
		flag = 2;
		mOutDt.d_out = 10;	// d_out��D2��D4��1�o��
		TPJT_set_ctrl(&mOutDt, sizeof(mOutDt));	// ����o�̓f�[�^�Z�b�g
		}
		if (mPad.POV[0] == 27000){    //�������
		flag = 3;
		mOutDt.d_out = 9;	// d_out��D1��D4��1�o��
		TPJT_set_ctrl(&mOutDt, sizeof(mOutDt));	// ����o�̓f�[�^�Z�b�g
		}
		if (mPad.POV[0] == 9000){    //�E�����
		flag = 4;
		mOutDt.d_out = 6;	// d_out��D2��D3��1�o��
		TPJT_set_ctrl(&mOutDt, sizeof(mOutDt));	// ����o�̓f�[�^�Z�b�g
		}
		if (mPad.POV[0] == -1){
		flag = 0;
		mOutDt.d_out = 0;
		}
		*/

		if ((mPad.axis[0] > AXIS_MIN / 2) && (mPad.axis[0] < AXIS_MAX / 2)){
			if ((mPad.axis[1] < AXIS_MIN / 2))
			{
				//��
				flag = 1;			//�O�i
				mOutDt.d_out = 5;	// d_out��D1��D3��1�o��
				TPJT_set_ctrl(&mOutDt, sizeof(mOutDt));	// ����o�̓f�[�^�Z�b�g
			}
			if ((mPad.axis[1] > AXIS_MAX / 2))
			{
				//��
				flag = 2;
				mOutDt.d_out = 10;	// d_out��D2��D4��1�o��
				TPJT_set_ctrl(&mOutDt, sizeof(mOutDt));	// ����o�̓f�[�^�Z�b�g
			}
		}
		if (mPad.axis[0] > AXIS_MAX / 2){
			if ((mPad.axis[1] > AXIS_MIN / 2) && (mPad.axis[1] < AXIS_MAX / 2))
			{
				//�E
				flag = 4;
				mOutDt.d_out = 6;	// d_out��D2��D3��1�o��
				TPJT_set_ctrl(&mOutDt, sizeof(mOutDt));	// ����o�̓f�[�^�Z�b�g
			}
		}
		if (mPad.axis[0] < AXIS_MIN / 2){    //�������
			if ((mPad.axis[1] > AXIS_MIN / 2) && (mPad.axis[1] < AXIS_MAX / 2))
			{
				//��
				flag = 3;
				mOutDt.d_out = 9;	// d_out��D1��D4��1�o��
				TPJT_set_ctrl(&mOutDt, sizeof(mOutDt));	// ����o�̓f�[�^�Z�b�g
			}
		}
		if ((mPad.axis[0] > AXIS_MIN / 2) && (mPad.axis[0] < AXIS_MAX / 2) &&
			(mPad.axis[1] > AXIS_MIN / 2) && (mPad.axis[1] < AXIS_MAX / 2))
		{
			//��~
			flag = 0;
			mOutDt.d_out = 0;
		}
		TPJT_set_ctrl(&mOutDt, sizeof(mOutDt));	// ����o�̓f�[�^�Z�b�g
	}
	/*
	��ʕ`��X�V�̊Ď�����
	�^�C�}�[�C�x���g���ԓ��ɉ�ʍX�V�����������ꍇWM_PAINT���b�Z�[�W�𑗐M���s���B
	*/
	if (hwnd != NULL) {		// �E�B���h�E����������Ă��邩�H
		if (updatePaint) {	// onPaint �X�V�t���O�����X�V���H
			InvalidateRect(hwnd, NULL, FALSE);	// WM_PAINT���b�Z�[�W�𑗐M
		}
		updatePaint = 1;	//  onPaint �X�V�t���O��RESET
	}
	return;
}


/**
* WM_KEYDOWN�̃��b�Z�[�W�N���b�J�[\n
* �V�X�e���L�[�ȊO�̃L�[�������ꂽ�ۂɃR�[�������֐�\n
* �V�X�e���L�[�Ƃ�Alt�L�[��������Ă��Ȃ���Ԃ̃L�[�̎�������
*
* @param[in]  hwnd    �C�x���g�����������E�B���h�E�̃n���h��
* @param[in]  vk      ���z�L�[�R�[�h
* @param[in]  fDown   ���TRUE
* @param[in]  cRepeat ���b�Z�[�W�̃��s�[�g��
* @param[in]  flags   lParam��HIWORD�ɒ�`����Ă���t���O
*
* @see http://msdn.microsoft.com/en-us/library/ms646280(VS.85).aspx
*
*/
void onKeydown(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags) {

	switch (vk) {
	case VK_ESCAPE: // ESC�L�[
	case VK_F12:    // F12
		onClose(hwnd);	// �E�C���h�E����鏈��
		return;
	case VK_F1:
		TPJT_chg_camera(0);
		break;
	case VK_F2:
		TPJT_chg_camera(1);
		break;

	default: // �ʏ�
		return;
	}

	return;
}

/**
* WM_KEYUP�̃��b�Z�[�W�N���b�J�[\n
* �V�X�e���L�[�ȊO�̃L�[�������ꂽ�ۂɃR�[�������֐�\n
* �V�X�e���L�[�Ƃ�Alt�L�[��������Ă��Ȃ���Ԃ̃L�[�̎�������
*
* @param[in]  hwnd    �C�x���g�����������E�B���h�E�̃n���h��
* @param[in]  vk      ���z�L�[�R�[�h
* @param[in]  fDown   ���FALSE
* @param[in]  cRepeat ���b�Z�[�W�̃��s�[�g��
* @param[in]  flags   lParam��HIWORD�ɒ�`����Ă���t���O
*
* @see http://msdn.microsoft.com/en-us/library/ms646281(VS.85).aspx
*
*/
void onKeyup(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags) {
	return;
}

/**
* WM_PAINT�̃��b�Z�[�W�N���b�J�[\n
* �V�X�e���A�܂��͑��̃A�v���P�[�V���������ʂ̍X�V�v�����������ۂɃR�[�������֐�\n
* Jpeg�f�[�^�̎�o���A��ʕ`����s��
*
* @param[in]  hwnd  �C�x���g�����������E�B���h�E�̃n���h��
*
* @see http://msdn.microsoft.com/en-us/library/dd145213(VS.85).aspx
*
*/

void onPaint(HWND hwnd) {
	//DWORD nBegin = ::GetTickCount();
	static int img_sz = 0; //�摜��荞�݃T�C�Y  
	IplImage *tpipImage, *dst_img, *gray_img; //���͉摜�o�b�t�@
	HDC   hdc;       // �f�o�C�X�R���e�L�X�g
	//RECT  dst, src = {0, 0, 640, 480};
	void* mJpegData;  // JPEG�f�[�^�i�[�ϐ�
	int   mJpegSize;  // JPEG�f�[�^�T�C�Y
	int connectId = TPJT_get_com_mode();
	updatePaint = 1;			// onPaint �X�V�t���O���X�V�ς�
	//OpenCV�̉摜�o�b�t�@�̐���
	tpipImage = cvCreateImage(cvSize(320, 300), IPL_DEPTH_8U, 3);
	//tpipImage���T�C�Y�p�摜
	dst_img = cvCreateImage(cvSize(600, 600), IPL_DEPTH_8U, 3);
	gray_img = cvCreateImage(cvSize(600, 600), IPL_DEPTH_8U, 1);
	//Jpeg�f�[�^�̎��o��
	mJpegData = TPJT_get_jpeg_file(0, 0, &mJpegSize);	// JPEG�f�[�^�̎�o��



	if ((mJpegData) && (mJpegSize > 0)) {	// JPEG�f�[�^���L��̏ꍇ



	//	img_sz = TPGM_JPEGbuffer2CV(mJpegData, mJpegSize, tpipImage);
		//cvResize(tpipImage, dst_img, CV_INTER_LINEAR);
		//cvCvtColor(dst_img, gray_img, CV_BGR2GRAY);
		//cvThreshold(gray_img,gray_img,0,255,CV_THRESH_BINARY|CV_THRESH_OTSU);
		//cvAdaptiveThreshold(gray_img, gray_img, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 7, 8);
		//img_sz = TPGM_JPEGbuffer2CV(mJpegData,mJpegSize,tpipImage);

		cvNamedWindow("cv", CV_WINDOW_AUTOSIZE || CV_WINDOW_FREERATIO);
		cvNamedWindow("cv_gray", CV_WINDOW_AUTOSIZE || CV_WINDOW_FREERATIO);
		//cvShowImage("cv",tpipImage);
		cvShowImage("cv", dst_img);
		cvShowImage("cv_gray", gray_img);


		TPGM_decode(mJpegData, mJpegSize);	// JPEG�f�[�^���J�����摜�Ƀf�R�[�h����
	}
	TPJT_free_jpeg_file();					// JPEG�f�[�^�̉��
	cvReleaseImage(&tpipImage);
	cvReleaseImage(&dst_img);
	cvReleaseImage(&gray_img);

	TPGM_copy(100, 50);			// �E�B���h�E���W(0,0)�ʒu�ɌŒ�T�C�Y(480x640)�ŃJ�����f����`�悷�� 
	//TPGM_copy2(&src, &dst);	// �T�C�Y��ύX���ăJ�����f����`�悷�鎞�Ɏg�p����B

	hdc = TPGM_getDC();			// �f�o�C�X�R���e�L�X�g���擾����

	char msg[40], msg1[40], msg2[40], msg3[40], msg4[40], wifi[40], connect[40], axis1[20], axis2[40],
		axis3[40], axis4[40], axis5[40], axis6[40], axis7[40], axis8[40];	// ������i�[�ϐ���`
	char timer[40];
	char str[40] = "    ";
	LPTSTR lpt = NULL;
	SetBkColor(hdc, RGB(0, 0, 0));				// �����w�i�F�w��
	SetTextColor(hdc, RGB(255, 255, 255));		// �����F�w��i���j

	//////////////////////////////////////////////////////////////
	//@comment  ���[�^�̏�Ԃ�\��
	//
	//////////////////////////////////////////////////////////////


	if (flag == 1){
		lpt = TEXT("�O�i");
		TextOut(hdc, 750, 180, lpt, lstrlen(lpt));
	}
	if (flag == 2){
		lpt = TEXT("���");
		TextOut(hdc, 750, 180, lpt, lstrlen(lpt));
	}

	if (flag == 3){
		lpt = TEXT("���i");
		TextOut(hdc, 750, 180, lpt, lstrlen(lpt));
	}
	if (flag == 4){
		lpt = TEXT("�E�i");
		TextOut(hdc, 750, 180, lpt, lstrlen(lpt));
	}
	if (flag == 0){
		lpt = TEXT("��~");
		TextOut(hdc, 750, 180, lpt, lstrlen(lpt));
	}


	////////////////////////////////////////////////////////////////////
	//@comment�@�v���O�����N��������̌o�ߎ��Ԃ�\��
	//
	////////////////////////////////////////////////////////////////////
	sprintf(msg, "Timer %3d. ", ((GetTickCount() - nBegin) / 1000) / 60);
	TextOut(hdc, 745, 0, (LPCSTR)msg, lstrlen((LPCSTR)msg));
	sprintf(msg, "%3d. ", ((GetTickCount() - nBegin) / 1000) % 60);
	TextOut(hdc, 810, 0, (LPCSTR)msg, lstrlen((LPCSTR)msg));
	sprintf(msg, "%d", (GetTickCount64() - nBegin) % 1000);
	TextOut(hdc, 840, 0, (LPCSTR)msg, lstrlen((LPCSTR)msg));



	////////////////////////////////////////////////////////////////////
	//@comment�@�e�T�[�{�̒l��\��
	//
	////////////////////////////////////////////////////////////////////
	sprintf(msg1, "servo1 = %7d", mOutDt.PWM[0]);
	TextOut(hdc, 745, 250, (LPCSTR)msg1, lstrlen((LPCSTR)msg1));
	sprintf(msg2, "servo2 = %7d", mOutDt.PWM[1]);
	TextOut(hdc, 745, 300, (LPCSTR)msg2, lstrlen((LPCSTR)msg2));
	sprintf(msg4, "motor PWM = %7d", mOutDt.PWM[3]);
	TextOut(hdc, 745, 150, msg4, lstrlen(msg4));


	//////////////////////////////////////////////////////////////////////
	//@comment WiFi�̓d�g���x��\��
	//
	//////////////////////////////////////////////////////////////////////
	sprintf(wifi, "WiFi = %d", TPJT_Get_Wlink());
	TextOut(hdc, 0, 200, (LPCSTR)wifi, lstrlen((LPCSTR)wifi));


	////////////////////////////////////////////////////////////////////
	//@comment ����`���̒ʐM���ID���o��
	//
	////////////////////////////////////////////////////////////////////
	sprintf(connect, "connect = %d", connectId);
	TextOut(hdc, 0, 250, (LPCSTR)connect, lstrlen((LPCSTR)connect));

	//////////////////////////////////////////////////////////////////////
	//@comment ���Ԍv��
	//�@�@�@�@�@�@�@�@�@�_�~�A���̖ڂ̓_��
	//////////////////////////////////////////////////////////////////////

	if (mPad.Button[1] == 128){

		start = GetTickCount64();
		button_flag = 1;
	}
	if (mPad.Button[2] == 128){
		end = GetTickCount();
		if (button_flag){
			//�\���̐��`
			sprintf(timer, "Get Time %3d. ", (end - start) / 1000);
			TextOut(hdc, 750, 100, (LPCSTR)timer, lstrlen((LPCSTR)timer));
			sprintf(timer, "%2d", end - start);
			TextOut(hdc, 840, 100, (LPCSTR)timer, lstrlen((LPCSTR)timer));
		}
		button_flag = 0;
	}


	TPGM_releaseDC();			// �f�o�C�X�R���e�L�X�g�����
	TPGM_screen();				// �X�N���[���֕`��

	ValidateRect(hwnd, NULL);	// ��ʍX�V��K�p����

	return;
}


/**
* WM_LBUTTONDOWN�̃��b�Z�[�W�N���b�J�[\n
* �E�B���h�E���Ń}�E�X�̍��{�^�����������񂾍ۂɃR�[�������֐�
*
* @param[in]  hwnd          �C�x���g�����������E�B���h�E�̃n���h��
* @param[in]  fDoubleClick  ���FALSE
* @param[in]  x             �C�x���g�����������ۂ̃}�E�X��X���W
* @param[in]  y             �C�x���g�����������ۂ̃}�E�X��Y���W
* @param[in]  keyFlags      ������Ă��鉼�z�L�[�̃t���O
*
* @see http://msdn.microsoft.com/en-us/library/ms645607(VS.85).aspx
*
*/

void onLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags) {

}





/**
* WM_LBUTTONUP�̃��b�Z�[�W�N���b�J�[\n
* �E�B���h�E���Ń}�E�X�̍��{�^���𗣂����ۂɃR�[�������֐�
*
* @param[in]  hwnd      �C�x���g�����������E�B���h�E�̃n���h��
* @param[in]  x         �C�x���g�����������ۂ̃}�E�X��X���W
* @param[in]  y         �C�x���g�����������ۂ̃}�E�X��Y���W
* @param[in]  keyFlags  ������Ă��鉼�z�L�[�̃t���O
*
* @see http://msdn.microsoft.com/en-us/library/ms645608(VS.85).aspx
*
*/
void onLButtonUp(HWND hwnd, int x, int y, UINT keyFlags) {

}



/**
* WM_LBUTTONDBLCLK�̃��b�Z�[�W�N���b�J�[\n
* �E�B���h�E���Ń}�E�X�̍��{�^�����_�u���N���b�N�����ۂɃR�[�������֐�
*
* @param[in]  hwnd          �C�x���g�����������E�B���h�E�̃n���h��
* @param[in]  fDoubleClick  ���TRUE
* @param[in]  x             �C�x���g�����������ۂ̃}�E�X��X���W
* @param[in]  y             �C�x���g�����������ۂ̃}�E�X��Y���W
* @param[in]  keyFlags      ������Ă��鉼�z�L�[�̃t���O
*
* @see http://msdn.microsoft.com/en-us/library/ms645606(VS.85).aspx
*
*/
void onLButtonDblClk(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags) {
	return;
}



/**
* WM_LBUTTONDOWN�̃��b�Z�[�W�N���b�J�[\n
* �E�B���h�E���Ń}�E�X�̉E�{�^�����������񂾍ۂɃR�[�������֐�
*
* @param[in]  hwnd          �C�x���g�����������E�B���h�E�̃n���h��
* @param[in]  fDoubleClick  ���FALSE
* @param[in]  x             �C�x���g�����������ۂ̃}�E�X��X���W
* @param[in]  y             �C�x���g�����������ۂ̃}�E�X��Y���W
* @param[in]  keyFlags      ������Ă��鉼�z�L�[�̃t���O
*
* @see http://msdn.microsoft.com/en-us/library/ms646242(VS.85).aspx
*
*/
void onRButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags) {

	return;
}



/**
* WM_RBUTTONUP�̃��b�Z�[�W�N���b�J�[\n
* �E�B���h�E���Ń}�E�X�̉E�{�^���𗣂����ۂɃR�[�������֐�
*
* @param[in]  hwnd      �C�x���g�����������E�B���h�E�̃n���h��
* @param[in]  x         �C�x���g�����������ۂ̃}�E�X��X���W
* @param[in]  y         �C�x���g�����������ۂ̃}�E�X��Y���W
* @param[in]  keyFlags  ������Ă��鉼�z�L�[�̃t���O
*
* @see http://msdn.microsoft.com/en-us/library/ms646243(VS.85).aspx
*
*/
void onRButtonUp(HWND hwnd, int x, int y, UINT keyFlags) {
	return;
}



/**
* WM_RBUTTONDOWN�̃��b�Z�[�W�N���b�J�[\n
* �E�B���h�E���Ń}�E�X�̉E�{�^�����_�u���N���b�N�����ۂɃR�[�������֐�
*
* @param[in]  hwnd          �C�x���g�����������E�B���h�E�̃n���h��
* @param[in]  fDoubleClick  ���TRUE
* @param[in]  x             �C�x���g�����������ۂ̃}�E�X��X���W
* @param[in]  y             �C�x���g�����������ۂ̃}�E�X��Y���W
* @param[in]  keyFlags      ������Ă��鉼�z�L�[�̃t���O
*
* @see http://msdn.microsoft.com/en-us/library/ms646241(VS.85).aspx
*
*/
void onRButtonDblClk(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags) {
	return;
}



/**
* WM_MOUSEMOVE�̃��b�Z�[�W�N���b�J�[\n
* �E�B���h�E���Ń}�E�X���������ۂɃR�[�������֐�
*
* @param[in]  hwnd      �C�x���g�����������E�B���h�E�̃n���h��
* @param[in]  x         �C�x���g�����������ۂ̃}�E�X��X���W
* @param[in]  y         �C�x���g�����������ۂ̃}�E�X��Y���W
* @param[in]  keyFlags  ������Ă��鉼�z�L�[�̃t���O
*
* @see http://msdn.microsoft.com/en-us/library/ms645616(VS.85).aspx
*
*/
void onMouseMove(HWND hwnd, int x, int y, UINT keyFlags) {
	return;
}
