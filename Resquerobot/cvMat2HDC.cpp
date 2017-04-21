#include "cvMat2HDC.h"
#include "TPIP3.h"  
//@comment　デバッグ用のHBITMAP保存関数
BOOL funcSaveRect(LPCTSTR lpFname, HDC hDC, LONG cx, LONG cy, LONG sx, LONG sy)
{
	HANDLE hFile = CreateFile(lpFname, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile != INVALID_HANDLE_VALUE){
		LONG    lHeadSize = (sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFO));
		LONG    lWidthSize = (sx * sizeof(DWORD));
		LONG    lImageSize = (lWidthSize * sy);
		DWORD   dwSize;

		// BITMAPFILEHEADERの初期化
		BITMAPFILEHEADER bmpHead = { 0 };
		bmpHead.bfType = 0x4D42;       // 識別子(BM)
		bmpHead.bfSize = lHeadSize + lImageSize;
		bmpHead.bfReserved1 = 0;
		bmpHead.bfReserved2 = 0;
		bmpHead.bfOffBits = lHeadSize;

		// BITMAPINFOの初期化
		BITMAPINFO bmpInfo = { 0 };
		bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmpInfo.bmiHeader.biWidth = sx;
		bmpInfo.bmiHeader.biHeight = sy;
		bmpInfo.bmiHeader.biPlanes = 1;
		bmpInfo.bmiHeader.biBitCount = 32;
		bmpInfo.bmiHeader.biCompression = BI_RGB;
		bmpInfo.bmiHeader.biSizeImage = 0;
		bmpInfo.bmiHeader.biXPelsPerMeter = 0;
		bmpInfo.bmiHeader.biYPelsPerMeter = 0;
		bmpInfo.bmiHeader.biClrUsed = 0;
		bmpInfo.bmiHeader.biClrImportant = 0;

		// DIBセクションの作成
		LPDWORD     lpPixel;    // ピクセル配列
		HBITMAP     hBitmap;    // ビットマップ
		HDC         hSaveDC;    // 保存スクリーン
		hBitmap = CreateDIBSection(NULL, &bmpInfo, DIB_RGB_COLORS, (LPVOID*)&lpPixel, NULL, 0);
		hSaveDC = CreateCompatibleDC(hDC);
		SelectObject(hSaveDC, hBitmap);

		// 保存領域のコピー
		BitBlt(hSaveDC, 0, 0, sx, sy, hDC, cx, cy, SRCCOPY);

		// ファイルに書き込む
		WriteFile(hFile, &bmpHead, sizeof(BITMAPFILEHEADER), &dwSize, NULL);
		WriteFile(hFile, &bmpInfo, sizeof(BITMAPINFO), &dwSize, NULL);
		WriteFile(hFile, lpPixel, lImageSize, &dwSize, NULL);

		// DIBセクションの破棄
		DeleteDC(hSaveDC);
		DeleteObject(hBitmap);
		CloseHandle(hFile);
		return TRUE;
	}
	return FALSE;
}

cvMat2HDC::cvMat2HDC()
{
	mat = cv::Mat();
	setRendPos(0, 0);
}

cvMat2HDC::cvMat2HDC(IplImage* src, HDC h)
{
	setMat(src);
	setHDC(h);
	setRendPos(0, 0);
}

cvMat2HDC::cvMat2HDC(cv::Mat& m, HDC h)
{
	setMat(m);
	setHDC(h);
	setRendPos(0, 0);
}

cvMat2HDC::~cvMat2HDC()
{
	DeleteDC(hdc);
}

void cvMat2HDC::setMat(IplImage* src)
{
	mat = cv::Mat(src);
}

void cvMat2HDC::setMat(cv::Mat& m)
{
	mat = m;
}

void cvMat2HDC::setHDC()
{
	hdc = TPGM_getDC();;
}

void cvMat2HDC::setHDC(HDC h)
{
	hdc = h;
}

void cvMat2HDC::setRendPos(int x, int y)
{
	posx = x;
	posy = y;
}

void cvMat2HDC::scale(const int s)
{
	//cv::resize(mat, mat, cv::Size(), s, s);
}

void cvMat2HDC::flip()
{
	cv::flip(mat, mat, 1);
}

void cvMat2HDC::save(const std::string& name)
{
	//@comment　imwriteを使用するとプログラムが停止する
	IplImage tmp = mat;
	std::string file = name + ".bmp";
	cvSaveImage(file.c_str(), &tmp);
}

//@dubug　SetDIBits(MatとHBITMAPの変換)がうまくいかない
void cvMat2HDC::convert()
{
	//@comment　画像データがなければ
	if (mat.data == NULL){
		return;
	}
	BITMAPINFO hInfo;
	HBITMAP hbmp;

	const int x = mat.cols;
	const int y = mat.rows;

	hInfo.bmiHeader.biWidth = x;
	hInfo.bmiHeader.biHeight = y;
	hInfo.bmiHeader.biBitCount = mat.channels() * 8;

	/******HERE is something wrong*******/
	hbmp = CreateCompatibleBitmap(hdc, x, y);
	SetDIBits(hdc, hbmp, 0, y, mat.data, &hInfo, DIB_RGB_COLORS);
	/******HERE is something wrong*******/

	HDC hdc2 = CreateCompatibleDC(hdc);
	SelectObject(hdc2, hbmp);
	BitBlt(hdc, posx, posy, x, y, hdc2, 0, 0, SRCCOPY);
	//StretchBlt(hdc, 0, 0, x, y, hdc2, 0, 0, x, y, SRCCOPY);
	funcSaveRect(TEXT("test.bmp"), hdc, 0, 0, x, y);

	DeleteDC(hdc2);
	DeleteObject(hbmp);
}

void cvMat2HDC::load(const std::string& name)
{
	HBITMAP hbmp;
	BITMAP bmp;
	HDC hdc2;
	std::string file = name + ".bmp";
	hbmp = (HBITMAP)LoadImage(NULL, (LPCTSTR
		)file.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	//@comment 取得したビットマップ情報を取得
	GetObject(hbmp, sizeof(bmp), &bmp);

	hdc2 = CreateCompatibleDC(hdc);
	SelectObject(hdc2, hbmp);
	BitBlt(hdc, posx, posy, bmp.bmWidth, bmp.bmHeight, hdc2, 0, 0, SRCCOPY);
	DeleteDC(hdc2);
	DeleteObject(hbmp);
}

cv::Mat cvMat2HDC::getMat() const
{
	return mat;
}

HDC cvMat2HDC::getHDC() const
{
	return hdc;
}

void cvMat2HDC::releaseHDC()
{
	TPGM_releaseDC();			// デバイスコンテキストを解放
}
