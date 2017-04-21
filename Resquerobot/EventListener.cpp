#define __CV_H__
/*-------- include --------*/
#include "TPIP3.h"           // TPIP関係
#include "EventListener.h"   // ウィンドウのイベント処理関係
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
#pragma  warning(disable:4996)	//	セキュリティが弱い古い関数に対する警告の解除


//#include <winsock2.h>
//#include<winsock2.h>
//#include<ws2tcpip.h>

//#pragma comment( lib, "wsock32.lib" )
//#pragma comment( lib, "ws2_32.lib")

#define WIDTH 640
#define HEIGHT 480
#define AXIS_MAX 32767
#define AXIS_MIN -32768

/*-------- メンバ変数定義 --------*/
static struct GC_STRUCT  mPad;		//!< @brief ゲームパッド入力データ
static struct OUT_DT_STR mOutDt;	//!< @brief TPJTで扱う制御情報
static struct INP_DT_STR mInpDt;	//!< @brief TPJTで扱うセンサー情報
static int    updatePaint;			//!< @brief onPaint 更新フラグ(0:更新済　1:未更新)
int flag, flag2, button_flag = 0;
DWORD nBegin = ::GetTickCount();  //@comment プログラム起動時のシステムの時間を保持
DWORD start, end;					//@comment システム起動時間保持用変数
//@comment コントローラーGUI画像を表示する
cvMat2HDC ctrl[12];
//@comment △、□、○、×の位置
const int circlePos[4][2] = { { 1055, 480 }, { 990, 550 }, { 1115, 550 }, { 1055, 620 } };
//@comment　方向キーの位置
const int rec1Pos[2][2] = { { 740, 480 }, { 740, 620 } };
const int rec2Pos[2][2] = { { 670, 550 }, { 800, 550 } };
//@comemnt l1, l2, r1, r2の位置
const int lrPos[4][2] = { { 700, 300 }, { 700, 370 }, { 1020, 300 }, { 1020, 370 } };
//@comment コントローラーが押されているか
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


/*-------- 関数定義 --------*/
//@comment コントローラーGUIの画像の位置の初期化
void initCtrlGUI()
{
	//@comment ○ボタン
	for (int i = 0; i < 4; i++){
		ctrl[i].setRendPos(circlePos[i][0], circlePos[i][1]);
	}
	//@comment lrボタン
	for (int i = 0; i < 4; i++){
		ctrl[i + 4].setRendPos(lrPos[i][0], lrPos[i][1]);
	}
	//@comment rect1ボタン
	for (int i = 0; i < 2; i++){
		ctrl[i + 8].setRendPos(rec1Pos[i][0], rec1Pos[i][1]);
	}
	//@comment lrボタン
	for (int i = 0; i < 2; i++){
		ctrl[i + 10].setRendPos(rec2Pos[i][0], rec2Pos[i][1]);
	}
}

//@comment コントローラーGUIへの押されているかどうかのフラグ変更
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

	//@comment 上を入力
	if (mPad.POV[0] == 0){ ctrlFlg[UP] = true; }
	else{ ctrlFlg[UP] = false; }

	//@comment 下を入力
	if (mPad.POV[0] == 18000){ ctrlFlg[DOWN] = true; }
	else{ ctrlFlg[DOWN] = false; }

	//@comment 左を入力
	if (mPad.POV[0] == 27000){ ctrlFlg[RGHT] = true; }
	else{ ctrlFlg[RGHT] = false; }

	//@comment 右を入力
	if (mPad.POV[0] == 9000){ ctrlFlg[LEFT] = true; }
	else{ ctrlFlg[LEFT] = false; }
}

//@comment コントローラーGUIの描画
void rendController()
{
	for (int i = 0; i < 12; i++){
		ctrl[i].setHDC();
	}
	//@comment ○ボタン
	for (int i = 0; i < 4; i++){
		if (ctrlFlg[i]){ ctrl[i].load("./img/circle_on"); }
		else{ ctrl[i].load("./img/circle"); }
	}
	//@comment lrボタン
	for (int i = 0; i < 4; i++){
		if (ctrlFlg[i + 4]){ ctrl[i + 4].load("./img/lr_on"); }
		else{ ctrl[i + 4].load("img/lr"); }
	}
	//@comment rect1ボタン
	for (int i = 0; i < 2; i++){
		if (ctrlFlg[i + 8]){ ctrl[i + 8].load("./img/rect_1_on"); }
		else{ ctrl[i + 8].load("./img/rect_1"); }
	}
	//@comment lrボタン
	for (int i = 0; i < 2; i++){
		if (ctrlFlg[i + 10]){ ctrl[i + 10].load("./img/rect_2_on"); }
		else{ ctrl[i + 10].load("./img/rect_2"); }
	}

	for (int i = 0; i < 12; i++){
		ctrl[i].releaseHDC();
	}
}

/**
* WM_CREATEのメッセージクラッカー\n
* ウィンドウが生成される前にコールされる関数\n
* ここで生成したタイマーを利用し、TPIPとの通信、画面の描画のイベントを発生します
*
* @param[in]  hwnd            イベントが発生したウィンドウのハンドル
* @param[in]  lpCreateStruct  ウィンドウ作成時のパラメータ
*
* @retval 常にTRUE
*
* @see http://msdn.microsoft.com/en-us/library/ms632619(VS.85).aspx
*
*/
BOOL onCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct) {


	TPJT_set_ctrl(&mOutDt, sizeof(mOutDt));	// 制御出力データセット

	SetTimer(hwnd, ID_MYTIMER, 60, NULL);	// タイマーを生成する
	initCtrlGUI();
	return TRUE; //ここをFALSE(0)にするとメッセージでDestroyが呼ばれる
}


/**
* WM_ACTIVATEのメッセージクラッカー\n
* ウィンドウがアクティブ/非アクティブになる際にコールされる関数
*
* @param[in] hwnd          イベントが発生したウィンドウのハンドル
* @param[in] state         ウィンドウがアクティブ/非アクティブかの状態
* @param[in] hwndActDeact  ウィンドウのハンドル\n
*                            state == 0の場合は、新しくアクティブになったウィンドウのハンドル\n
*                            state != 0の場合は、それまでアクティブであったウィンドウのハンドル
* @param[in] fMinimized    ウィンドウが最小化されているかの判定フラグ\n
*                            0以外の値の場合はウィンドウは最小化されています\n
*                            0の場合はウィンドウは最小化されていません\n
*
* @see http://msdn.microsoft.com/ja-jp/library/ms646274(d=lightweight).aspx
*
*/
void onActivate(HWND hwnd, UINT state, HWND hwndActDeact, BOOL fMinimized) {
	return;
}



/**
* WM_CLOSEのメッセージクラッカー\n
* ウィンドウかアプリケーションが終了する際にコールされる関数\n
* 終了の確認を行い、YESならばウィンドウを破棄する。NOならば破棄しない
*
* @param[in] hwnd  イベントが発生したウィンドウのハンドル
*
* @see http://msdn.microsoft.com/en-us/library/ms632617(VS.85).aspx
*
*/
void onClose(HWND hwnd) {

	int ans = 0; // 戻り値取得用

	// メッセージダイアログを表示し、終了の確認をする
	ans = MessageBox(hwnd, TEXT("終了しますか？"), TEXT("終了確認"), MB_YESNO | MB_ICONEXCLAMATION);

	// YESが選択された場合はウィンドウを閉じる
	if (ans == IDYES) {
		DestroyWindow(hwnd); // ウインドウを閉じる関数
	}

	return;
}



/**
* WM_DESTROYのメッセージクラッカー\n
* ウィンドウが破棄される際にコールされる関数\n
* TPIPライブラリと生成したタイマーの解放を行う
*
* @param[in]  hwnd イベントが発生したウィンドウのハンドル
*
* @see http://msdn.microsoft.com/en-us/library/ms632620(VS.85).aspx
*
*/
void onDestroy(HWND hwnd) {

	// TPIPライブラリ群の解放
	TPGM_delete();
	TPGC_close();
	TPJT_close();

	//タイマー解放
	KillTimer(hwnd, ID_MYTIMER);
	PostQuitMessage(0);

	return;
}



/**
* WM_SIZEのメッセージクラッカー\n
* ウィンドウのサイズが変更された後にコールされる関数\n
* TPGMで使用しているサーフェイスを変更後のサイズで構成し直す
*
* @param[in]  hwnd  イベントが発生したウィンドウのハンドル
* @param[in]  state サイズ変更のタイプ
* @param[in]  cx    ウィンドウの横幅
* @param[in]  cy    ウィンドウの縦幅
*
* @see http://msdn.microsoft.com/en-us/library/ms632646(v=vs.85).aspx
*
*/
void onSize(HWND hwnd, UINT state, int cx, int cy) {

	// サーフェイスの再構成
	TPGM_delete();
	TPGM_create(hwnd, QVGA, NULL);

	return;
}



/**
* WM_TIMERのメッセージクラッカー\n
* タイマーが終了した際にコールされる関数\n
* ゲームパッドからの入力、TPIPとの通信、画面の描5画のイベントを発生する\n
* 制御データの加工等はTPJT_set_ctrl()を実行するまでに行うこと
*
* @param[in]  hwnd イベントが発生したウィンドウのハンドル1
* @param[in]  id   イベントを起こしたタイマーID
*
* @see http://msdn.microsoft.com/en-us/library/ms644902(VS.85).aspx
*
*/
void onTimer(HWND hwnd, UINT id) {
	if (id == ID_MYTIMER) {		// 予期しないタイマーからのイベントは無視する

		TPGC_get(&mPad);		// ゲームパッドからの入力を取得

		TPJT_get_sens(&mInpDt, sizeof(mInpDt));	// センサ入力を取得

		//@comment GUI上のコントローラ表示を変更
		//switchButtons();

		// R１ボタン入力
		//if (mPad.Button[5] == 128){
		//flag2 += 1;
		//Sleep(300);
		//if (flag2 == 3){
		//flag2 = 0;
		//}
		//}
		//@comment startボタン,selectボタンでカメラ切り替え

		if (mPad.Button[8] == 128){
			//if (cameraFlg){
			TPJT_chg_camera(0);
			//cameraFlg = false;
		}

		if (mPad.Button[9] == 128){
			TPJT_chg_camera(1);
			//cameraFlg = true;
		}

		//@comment アーム関節
		if (mPad.Button[6] == 128){
			if (mOutDt.PWM[0] >= 800)
			{
				mOutDt.PWM[0] = 800;
			}
			else
			{
				mOutDt.PWM[0] += 20;
			}
			TPJT_set_ctrl(&mOutDt, sizeof(mOutDt));	// 制御出力データセット
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
		//@comment カメラ角度
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
		//@comment モータPWM
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
		if (mPad.POV[0] == 0){    //上を入力
		flag = 1;
		mOutDt.d_out = 5;	// d_outのD1とD3に1出力
		TPJT_set_ctrl(&mOutDt, sizeof(mOutDt));	// 制御出力データセット
		}
		if (mPad.POV[0] == 18000){   //下を入力
		flag = 2;
		mOutDt.d_out = 10;	// d_outのD2とD4に1出力
		TPJT_set_ctrl(&mOutDt, sizeof(mOutDt));	// 制御出力データセット
		}
		if (mPad.POV[0] == 27000){    //左を入力
		flag = 3;
		mOutDt.d_out = 9;	// d_outのD1とD4に1出力
		TPJT_set_ctrl(&mOutDt, sizeof(mOutDt));	// 制御出力データセット
		}
		if (mPad.POV[0] == 9000){    //右を入力
		flag = 4;
		mOutDt.d_out = 6;	// d_outのD2とD3に1出力
		TPJT_set_ctrl(&mOutDt, sizeof(mOutDt));	// 制御出力データセット
		}
		if (mPad.POV[0] == -1){
		flag = 0;
		mOutDt.d_out = 0;
		}
		*/

		if ((mPad.axis[0] > AXIS_MIN / 2) && (mPad.axis[0] < AXIS_MAX / 2)){
			if ((mPad.axis[1] < AXIS_MIN / 2))
			{
				//上
				flag = 1;			//前進
				mOutDt.d_out = 5;	// d_outのD1とD3に1出力
				TPJT_set_ctrl(&mOutDt, sizeof(mOutDt));	// 制御出力データセット
			}
			if ((mPad.axis[1] > AXIS_MAX / 2))
			{
				//下
				flag = 2;
				mOutDt.d_out = 10;	// d_outのD2とD4に1出力
				TPJT_set_ctrl(&mOutDt, sizeof(mOutDt));	// 制御出力データセット
			}
		}
		if (mPad.axis[0] > AXIS_MAX / 2){
			if ((mPad.axis[1] > AXIS_MIN / 2) && (mPad.axis[1] < AXIS_MAX / 2))
			{
				//右
				flag = 4;
				mOutDt.d_out = 6;	// d_outのD2とD3に1出力
				TPJT_set_ctrl(&mOutDt, sizeof(mOutDt));	// 制御出力データセット
			}
		}
		if (mPad.axis[0] < AXIS_MIN / 2){    //左を入力
			if ((mPad.axis[1] > AXIS_MIN / 2) && (mPad.axis[1] < AXIS_MAX / 2))
			{
				//左
				flag = 3;
				mOutDt.d_out = 9;	// d_outのD1とD4に1出力
				TPJT_set_ctrl(&mOutDt, sizeof(mOutDt));	// 制御出力データセット
			}
		}
		if ((mPad.axis[0] > AXIS_MIN / 2) && (mPad.axis[0] < AXIS_MAX / 2) &&
			(mPad.axis[1] > AXIS_MIN / 2) && (mPad.axis[1] < AXIS_MAX / 2))
		{
			//停止
			flag = 0;
			mOutDt.d_out = 0;
		}
		TPJT_set_ctrl(&mOutDt, sizeof(mOutDt));	// 制御出力データセット
	}
	/*
	画面描画更新の監視処理
	タイマーイベント期間内に画面更新が無かった場合WM_PAINTメッセージを送信を行う。
	*/
	if (hwnd != NULL) {		// ウィンドウが生成されているか？
		if (updatePaint) {	// onPaint 更新フラグが未更新か？
			InvalidateRect(hwnd, NULL, FALSE);	// WM_PAINTメッセージを送信
		}
		updatePaint = 1;	//  onPaint 更新フラグをRESET
	}
	return;
}


/**
* WM_KEYDOWNのメッセージクラッカー\n
* システムキー以外のキーが押された際にコールされる関数\n
* システムキーとはAltキーが押されていない状態のキーの事を言う
*
* @param[in]  hwnd    イベントが発生したウィンドウのハンドル
* @param[in]  vk      仮想キーコード
* @param[in]  fDown   常にTRUE
* @param[in]  cRepeat メッセージのリピート回数
* @param[in]  flags   lParamのHIWORDに定義されているフラグ
*
* @see http://msdn.microsoft.com/en-us/library/ms646280(VS.85).aspx
*
*/
void onKeydown(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags) {

	switch (vk) {
	case VK_ESCAPE: // ESCキー
	case VK_F12:    // F12
		onClose(hwnd);	// ウインドウを閉じる処理
		return;
	case VK_F1:
		TPJT_chg_camera(0);
		break;
	case VK_F2:
		TPJT_chg_camera(1);
		break;

	default: // 通常
		return;
	}

	return;
}

/**
* WM_KEYUPのメッセージクラッカー\n
* システムキー以外のキーが離された際にコールされる関数\n
* システムキーとはAltキーが押されていない状態のキーの事を言う
*
* @param[in]  hwnd    イベントが発生したウィンドウのハンドル
* @param[in]  vk      仮想キーコード
* @param[in]  fDown   常にFALSE
* @param[in]  cRepeat メッセージのリピート回数
* @param[in]  flags   lParamのHIWORDに定義されているフラグ
*
* @see http://msdn.microsoft.com/en-us/library/ms646281(VS.85).aspx
*
*/
void onKeyup(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags) {
	return;
}

/**
* WM_PAINTのメッセージクラッカー\n
* システム、または他のアプリケーションから画面の更新要求があった際にコールされる関数\n
* Jpegデータの取出し、画面描画を行う
*
* @param[in]  hwnd  イベントが発生したウィンドウのハンドル
*
* @see http://msdn.microsoft.com/en-us/library/dd145213(VS.85).aspx
*
*/

void onPaint(HWND hwnd) {
	//DWORD nBegin = ::GetTickCount();
	static int img_sz = 0; //画像取り込みサイズ  
	IplImage *tpipImage, *dst_img, *gray_img; //入力画像バッファ
	HDC   hdc;       // デバイスコンテキスト
	//RECT  dst, src = {0, 0, 640, 480};
	void* mJpegData;  // JPEGデータ格納変数
	int   mJpegSize;  // JPEGデータサイズ
	int connectId = TPJT_get_com_mode();
	updatePaint = 1;			// onPaint 更新フラグを更新済に
	//OpenCVの画像バッファの生成
	tpipImage = cvCreateImage(cvSize(320, 300), IPL_DEPTH_8U, 3);
	//tpipImageリサイズ用画像
	dst_img = cvCreateImage(cvSize(600, 600), IPL_DEPTH_8U, 3);
	gray_img = cvCreateImage(cvSize(600, 600), IPL_DEPTH_8U, 1);
	//Jpegデータの取り出し
	mJpegData = TPJT_get_jpeg_file(0, 0, &mJpegSize);	// JPEGデータの取出し



	if ((mJpegData) && (mJpegSize > 0)) {	// JPEGデータが有りの場合



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


		TPGM_decode(mJpegData, mJpegSize);	// JPEGデータをカメラ画像にデコードする
	}
	TPJT_free_jpeg_file();					// JPEGデータの解放
	cvReleaseImage(&tpipImage);
	cvReleaseImage(&dst_img);
	cvReleaseImage(&gray_img);

	TPGM_copy(100, 50);			// ウィンドウ座標(0,0)位置に固定サイズ(480x640)でカメラ映像を描画する 
	//TPGM_copy2(&src, &dst);	// サイズを変更してカメラ映像を描画する時に使用する。

	hdc = TPGM_getDC();			// デバイスコンテキストを取得する

	char msg[40], msg1[40], msg2[40], msg3[40], msg4[40], wifi[40], connect[40], axis1[20], axis2[40],
		axis3[40], axis4[40], axis5[40], axis6[40], axis7[40], axis8[40];	// 文字列格納変数定義
	char timer[40];
	char str[40] = "    ";
	LPTSTR lpt = NULL;
	SetBkColor(hdc, RGB(0, 0, 0));				// 文字背景色指定
	SetTextColor(hdc, RGB(255, 255, 255));		// 文字色指定（白）

	//////////////////////////////////////////////////////////////
	//@comment  モータの状態を表示
	//
	//////////////////////////////////////////////////////////////


	if (flag == 1){
		lpt = TEXT("前進");
		TextOut(hdc, 750, 180, lpt, lstrlen(lpt));
	}
	if (flag == 2){
		lpt = TEXT("後退");
		TextOut(hdc, 750, 180, lpt, lstrlen(lpt));
	}

	if (flag == 3){
		lpt = TEXT("左進");
		TextOut(hdc, 750, 180, lpt, lstrlen(lpt));
	}
	if (flag == 4){
		lpt = TEXT("右進");
		TextOut(hdc, 750, 180, lpt, lstrlen(lpt));
	}
	if (flag == 0){
		lpt = TEXT("停止");
		TextOut(hdc, 750, 180, lpt, lstrlen(lpt));
	}


	////////////////////////////////////////////////////////////////////
	//@comment　プログラム起動時からの経過時間を表示
	//
	////////////////////////////////////////////////////////////////////
	sprintf(msg, "Timer %3d. ", ((GetTickCount() - nBegin) / 1000) / 60);
	TextOut(hdc, 745, 0, (LPCSTR)msg, lstrlen((LPCSTR)msg));
	sprintf(msg, "%3d. ", ((GetTickCount() - nBegin) / 1000) % 60);
	TextOut(hdc, 810, 0, (LPCSTR)msg, lstrlen((LPCSTR)msg));
	sprintf(msg, "%d", (GetTickCount64() - nBegin) % 1000);
	TextOut(hdc, 840, 0, (LPCSTR)msg, lstrlen((LPCSTR)msg));



	////////////////////////////////////////////////////////////////////
	//@comment　各サーボの値を表示
	//
	////////////////////////////////////////////////////////////////////
	sprintf(msg1, "servo1 = %7d", mOutDt.PWM[0]);
	TextOut(hdc, 745, 250, (LPCSTR)msg1, lstrlen((LPCSTR)msg1));
	sprintf(msg2, "servo2 = %7d", mOutDt.PWM[1]);
	TextOut(hdc, 745, 300, (LPCSTR)msg2, lstrlen((LPCSTR)msg2));
	sprintf(msg4, "motor PWM = %7d", mOutDt.PWM[3]);
	TextOut(hdc, 745, 150, msg4, lstrlen(msg4));


	//////////////////////////////////////////////////////////////////////
	//@comment WiFiの電波強度を表示
	//
	//////////////////////////////////////////////////////////////////////
	sprintf(wifi, "WiFi = %d", TPJT_Get_Wlink());
	TextOut(hdc, 0, 200, (LPCSTR)wifi, lstrlen((LPCSTR)wifi));


	////////////////////////////////////////////////////////////////////
	//@comment 動画伝送の通信状態ID取り出し
	//
	////////////////////////////////////////////////////////////////////
	sprintf(connect, "connect = %d", connectId);
	TextOut(hdc, 0, 250, (LPCSTR)connect, lstrlen((LPCSTR)connect));

	//////////////////////////////////////////////////////////////////////
	//@comment 時間計測
	//　　　　　　　　　ダミアンの目の点滅
	//////////////////////////////////////////////////////////////////////

	if (mPad.Button[1] == 128){

		start = GetTickCount64();
		button_flag = 1;
	}
	if (mPad.Button[2] == 128){
		end = GetTickCount();
		if (button_flag){
			//表示の整形
			sprintf(timer, "Get Time %3d. ", (end - start) / 1000);
			TextOut(hdc, 750, 100, (LPCSTR)timer, lstrlen((LPCSTR)timer));
			sprintf(timer, "%2d", end - start);
			TextOut(hdc, 840, 100, (LPCSTR)timer, lstrlen((LPCSTR)timer));
		}
		button_flag = 0;
	}


	TPGM_releaseDC();			// デバイスコンテキストを解放
	TPGM_screen();				// スクリーンへ描画

	ValidateRect(hwnd, NULL);	// 画面更新を適用する

	return;
}


/**
* WM_LBUTTONDOWNのメッセージクラッカー\n
* ウィンドウ内でマウスの左ボタンを押し込んだ際にコールされる関数
*
* @param[in]  hwnd          イベントが発生したウィンドウのハンドル
* @param[in]  fDoubleClick  常にFALSE
* @param[in]  x             イベントが発生した際のマウスのX座標
* @param[in]  y             イベントが発生した際のマウスのY座標
* @param[in]  keyFlags      押されている仮想キーのフラグ
*
* @see http://msdn.microsoft.com/en-us/library/ms645607(VS.85).aspx
*
*/

void onLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags) {

}





/**
* WM_LBUTTONUPのメッセージクラッカー\n
* ウィンドウ内でマウスの左ボタンを離した際にコールされる関数
*
* @param[in]  hwnd      イベントが発生したウィンドウのハンドル
* @param[in]  x         イベントが発生した際のマウスのX座標
* @param[in]  y         イベントが発生した際のマウスのY座標
* @param[in]  keyFlags  押されている仮想キーのフラグ
*
* @see http://msdn.microsoft.com/en-us/library/ms645608(VS.85).aspx
*
*/
void onLButtonUp(HWND hwnd, int x, int y, UINT keyFlags) {

}



/**
* WM_LBUTTONDBLCLKのメッセージクラッカー\n
* ウィンドウ内でマウスの左ボタンをダブルクリックした際にコールされる関数
*
* @param[in]  hwnd          イベントが発生したウィンドウのハンドル
* @param[in]  fDoubleClick  常にTRUE
* @param[in]  x             イベントが発生した際のマウスのX座標
* @param[in]  y             イベントが発生した際のマウスのY座標
* @param[in]  keyFlags      押されている仮想キーのフラグ
*
* @see http://msdn.microsoft.com/en-us/library/ms645606(VS.85).aspx
*
*/
void onLButtonDblClk(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags) {
	return;
}



/**
* WM_LBUTTONDOWNのメッセージクラッカー\n
* ウィンドウ内でマウスの右ボタンを押し込んだ際にコールされる関数
*
* @param[in]  hwnd          イベントが発生したウィンドウのハンドル
* @param[in]  fDoubleClick  常にFALSE
* @param[in]  x             イベントが発生した際のマウスのX座標
* @param[in]  y             イベントが発生した際のマウスのY座標
* @param[in]  keyFlags      押されている仮想キーのフラグ
*
* @see http://msdn.microsoft.com/en-us/library/ms646242(VS.85).aspx
*
*/
void onRButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags) {

	return;
}



/**
* WM_RBUTTONUPのメッセージクラッカー\n
* ウィンドウ内でマウスの右ボタンを離した際にコールされる関数
*
* @param[in]  hwnd      イベントが発生したウィンドウのハンドル
* @param[in]  x         イベントが発生した際のマウスのX座標
* @param[in]  y         イベントが発生した際のマウスのY座標
* @param[in]  keyFlags  押されている仮想キーのフラグ
*
* @see http://msdn.microsoft.com/en-us/library/ms646243(VS.85).aspx
*
*/
void onRButtonUp(HWND hwnd, int x, int y, UINT keyFlags) {
	return;
}



/**
* WM_RBUTTONDOWNのメッセージクラッカー\n
* ウィンドウ内でマウスの右ボタンをダブルクリックした際にコールされる関数
*
* @param[in]  hwnd          イベントが発生したウィンドウのハンドル
* @param[in]  fDoubleClick  常にTRUE
* @param[in]  x             イベントが発生した際のマウスのX座標
* @param[in]  y             イベントが発生した際のマウスのY座標
* @param[in]  keyFlags      押されている仮想キーのフラグ
*
* @see http://msdn.microsoft.com/en-us/library/ms646241(VS.85).aspx
*
*/
void onRButtonDblClk(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags) {
	return;
}



/**
* WM_MOUSEMOVEのメッセージクラッカー\n
* ウィンドウ内でマウスが動いた際にコールされる関数
*
* @param[in]  hwnd      イベントが発生したウィンドウのハンドル
* @param[in]  x         イベントが発生した際のマウスのX座標
* @param[in]  y         イベントが発生した際のマウスのY座標
* @param[in]  keyFlags  押されている仮想キーのフラグ
*
* @see http://msdn.microsoft.com/en-us/library/ms645616(VS.85).aspx
*
*/
void onMouseMove(HWND hwnd, int x, int y, UINT keyFlags) {
	return;
}
