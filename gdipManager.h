#pragma once
#include "singletonBase.h"
#include "gdipImage.h"

class gdipManager : public singletonBase<gdipManager>
{
private:
	typedef map<string, gdipImage*> mapGdipImgList;				//������ ���� �̹������
	typedef map<string, gdipImage*>::iterator mapGdipImgIter;	//������ ���� �̹�������� �ݺ���

private:
	mapGdipImgList _mGdipImgList;								//���� �̹���Ŭ������ ���� ��

public:
	gdipManager() {}
	~gdipManager() {}

	HRESULT init();
	void release();

//========================================================================================================================================================
//	�̹����߰�
//========================================================================================================================================================
	gdipImage * addImage(string strKey, TCHAR * fileName, BOOL isTrans = false, COLORREF _transColor = RGB(0, 0, 0), RotateFlipType rotateFlipType = RotateNoneFlipNone);
	gdipImage * addImage(string strKey, TCHAR * fileName, int destX, int destY, BOOL isTrans = false, COLORREF _transColor = RGB(0, 0, 0), RotateFlipType rotateFlipType = RotateNoneFlipNone);
	gdipImage * addFrameImage(string strKey, TCHAR * fileName, int destX, int destY, int maxFrameX, int maxFrameY, BOOL isTrans = false, COLORREF transColor = RGB(0, 0, 0), RotateFlipType rotateFlipType = RotateNoneFlipNone);

//========================================================================================================================================================
//	�̹��� ã��
//========================================================================================================================================================
	gdipImage * findImage(string strKey);

//========================================================================================================================================================
//	�̹��� ����
//========================================================================================================================================================
	BOOL deleteAll();

//========================================================================================================================================================
//	�̹��� ����
//========================================================================================================================================================
	void gdiRender(string strKey, HDC hdc, int angle = 0);
	void gdiRender(string strKey, HDC hdc, int destX, int destY, int angle = 0);
	void gdiRender(string strKey, HDC hdc, int destX, int destY, int width, int height, int angle = 0);
	void gdiRender(string strKey, HDC hdc, int destX, int destY, float wRatio, float hRatio, int angle = 0);
	void gdiRender(string strKey, HDC hdc, int destX, int destY, float wRatio, float hRatio, InterpolationMode _imode, int angle = 0);
	void gdiRender(string strKey, HDC hdc, int destX, int destY, Point* ptDest, int angle = 0);
	void gdiRender(string strKey, HDC hdc, int destX, int destY, int srcX, int srcY, int srcWidth, int srcHeight, int angle = 0);

//========================================================================================================================================================
//	������ �̹��� ����
//========================================================================================================================================================
	void gdiFrameRender(string strKey, HDC hdc, int angle = 0);
	void gdiFrameRender(string strKey, HDC hdc, int destX, int destY, int angle = 0);
	void gdiFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, int angle = 0);
	void gdiFrameRender(string strKey, HDC hdc, int destX, int destY, int width, int height, int currentFrameX, int currentFrameY, int angle = 0);
	void gdiFrameRender(string strKey, HDC hdc, int destX, int destY, float wRatio, float hRatio, int currentFrameX, int currentFrameY, int angle = 0);
	void gdiFrameRender(string strKey, HDC hdc, int destX, int destY, float wRatio, float hRatio, int currentFrameX, int currentFrameY, InterpolationMode _imode, int angle = 0);

//========================================================================================================================================================
//	���ķ���
//========================================================================================================================================================
	void gdiAlphaRender(string strKey, HDC hdc, float alpha, int angle = 0);
	void gdiAlphaRender(string strKey, HDC hdc, int destX, int destY, float alpha, int angle = 0);
	void gdiAlphaFrameRender(string strKey, HDC hdc, float alpha, int angle = 0);
	void gdiAlphaFrameRender(string strKey, HDC hdc, int destX, int destY, float alpha, int angle = 0);

//========================================================================================================================================================
//	Threshold ����
//========================================================================================================================================================
	void gdiThresholdRender(string strKey, HDC hdc, float value, int angle = 0);
	void gdiThresholdRender(string strKey, HDC hdc, int destX, int destY, float value, int angle = 0);
	void gdiThresholdFrameRender(string strKey, HDC hdc, float value, int angle = 0);
	void gdiThresholdFrameRender(string strKey, HDC hdc, int destX, int destY, float value, int angle = 0);

//========================================================================================================================================================
//	Gamma ����
//========================================================================================================================================================
	void gdiGammaRender(string strKey, HDC hdc, float value, int angle = 0);
	void gdiGammaRender(string strKey, HDC hdc, int destX, int destY, float value, int angle = 0);
	void gdiGammaFrameRender(string strKey, HDC hdc, float value, int angle = 0);
	void gdiGammaFrameRender(string strKey, HDC hdc, int destX, int destY, float value, int angle = 0);

//========================================================================================================================================================
//	Lighten ����
//========================================================================================================================================================
	void gdiLightenRender(string strKey, HDC hdc, float value, int angle = 0);
	void gdiLightenRender(string strKey, HDC hdc, int destX, int destY, float value, int angle = 0);
	void gdiLightenFrameRender(string strKey, HDC hdc, float value, int angle = 0);
	void gdiLightenFrameRender(string strKey, HDC hdc, int destX, int destY, float value, int angle = 0);

//========================================================================================================================================================
//	Negative ����
//========================================================================================================================================================
	void gdiNegativeRender(string strKey, HDC hdc, int angle = 0);
	void gdiNegativeRender(string strKey, HDC hdc, int destX, int destY, int angle = 0);
	void gdiNegativeFrameRender(string strKey, HDC hdc, int angle = 0);
	void gdiNegativeFrameRender(string strKey, HDC hdc, int destX, int destY, int angle = 0);
};

