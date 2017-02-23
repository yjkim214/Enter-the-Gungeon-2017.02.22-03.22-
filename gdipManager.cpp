#include "stdafx.h"
#include "gdipManager.h"

HRESULT gdipManager::init(void)
{
	return S_OK;
}

void gdipManager::release(void)
{
	this->deleteAll();
}

gdipImage * gdipManager::addImage(string strKey, TCHAR* fileName, BOOL isTrans, COLORREF _transColor, RotateFlipType rotateFlipType)
{
	//�߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	gdipImage* gdiImg = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� ���� �Ѵٸ� ���� ������ �ʰ� �ٷ� ����
	if (gdiImg) return gdiImg;

	//������ �̹��� ���� ����
	gdiImg = new gdipImage;
	if (FAILED(gdiImg->init(fileName, (bool)isTrans, _transColor, rotateFlipType)))
	{
		SAFE_DELETE(gdiImg);
		return NULL;
	}
	_mGdipImgList.insert(make_pair(strKey, gdiImg));

	return gdiImg;
}

gdipImage * gdipManager::addImage(string strKey, TCHAR * fileName, int destX, int destY, BOOL isTrans, COLORREF _transColor, RotateFlipType rotateFlipType)
{
	//�߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	gdipImage* gdiImg = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� ���� �Ѵٸ� ���� ������ �ʰ� �ٷ� ����
	if (gdiImg) return gdiImg;

	//������ �̹��� ���� ����
	gdiImg = new gdipImage;
	if (FAILED(gdiImg->init(fileName, destX, destY, (bool)isTrans, _transColor, rotateFlipType)))
	{
		SAFE_DELETE(gdiImg);
		return NULL;
	}
	_mGdipImgList.insert(make_pair(strKey, gdiImg));

	return gdiImg;
}

gdipImage * gdipManager::addFrameImage(string strKey, TCHAR * fileName, int destX, int destY, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor, RotateFlipType rotateFlipType)
{
	//�߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	gdipImage* gdiImg = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� ���� �Ѵٸ� ���� ������ �ʰ� �ٷ� ����
	if (gdiImg) return gdiImg;

	//������ �̹��� ���� ����
	gdiImg = new gdipImage;
	if (FAILED(gdiImg->init(fileName, destX, destY, maxFrameX, maxFrameY, isTrans, transColor, rotateFlipType)))
	{
		SAFE_DELETE(gdiImg);
		return NULL;
	}

	/*STL �ʿ� ����*/
	_mGdipImgList.insert(make_pair(strKey, gdiImg));

	return gdiImg;
}

gdipImage * gdipManager::findImage(string strKey)
{
	//�ش�Ű �˻�
	mapGdipImgIter key = _mGdipImgList.find(strKey);

	//�˻��� Ű�� ã��
	if (key != _mGdipImgList.end())
	{
		//�� ��ȯ
		return key->second;
	}

	//�˻��� Ű�� �̹����� ��ã�Ҵٸ� NULL
	return NULL;
}

//����
BOOL gdipManager::deleteAll()
{
	//�� ��ü�� ���鼭 �����
	mapGdipImgIter iter = _mGdipImgList.begin();
	//for(;;)  == while(true)
	for (; iter != _mGdipImgList.end();)
	{
		//�̹����� ������
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mGdipImgList.erase(iter);
		}
		else //������
		{
			++iter;
		}
	}

	//�� ��ü�� ����
	_mGdipImgList.clear();

	return TRUE;
}

//========================================================================================================================================================
//	�̹��� ����
//========================================================================================================================================================
void gdipManager::gdiRender(string strKey, HDC hdc, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiRender(hdc, angle);
}

void gdipManager::gdiRender(string strKey, HDC hdc, int destX, int destY, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiRender(hdc, destX, destY, angle);
}

void gdipManager::gdiRender(string strKey, HDC hdc, int destX, int destY, int width, int height, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiRender(hdc, destX, destY, width, height, angle);
}

void gdipManager::gdiRender(string strKey, HDC hdc, int destX, int destY, float wRatio, float hRatio, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiRender(hdc, destX, destY, wRatio, hRatio, angle);
}

void gdipManager::gdiRender(string strKey, HDC hdc, int destX, int destY, float wRatio, float hRatio, InterpolationMode _imode, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiRender(hdc, destX, destY, wRatio, hRatio, _imode, angle);
}

void gdipManager::gdiRender(string strKey, HDC hdc, int destX, int destY, Point * ptDest, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiRender(hdc, destX, destY, ptDest, angle);
}

void gdipManager::gdiRender(string strKey, HDC hdc, int destX, int destY, int srcX, int srcY, int srcWidth, int srcHeight, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiRender(hdc, destX, destY, srcX, srcY, srcWidth, srcHeight, angle);
}


//========================================================================================================================================================
//	������ �̹��� ����
//========================================================================================================================================================
void gdipManager::gdiFrameRender(string strKey, HDC hdc, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiFrameRender(hdc, angle);
}

void gdipManager::gdiFrameRender(string strKey, HDC hdc, int destX, int destY, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiFrameRender(hdc, destX, destY, angle);
}

void gdipManager::gdiFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiFrameRender(hdc, destX, destY, currentFrameX, currentFrameY, angle);
}

void gdipManager::gdiFrameRender(string strKey, HDC hdc, int destX, int destY, int width, int height, int currentFrameX, int currentFrameY, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiFrameRender(hdc, destX, destY, width, height, currentFrameX, currentFrameY, angle);
}

void gdipManager::gdiFrameRender(string strKey, HDC hdc, int destX, int destY, float wRatio, float hRatio, int currentFrameX, int currentFrameY, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiFrameRender(hdc, destX, destY, wRatio, hRatio, currentFrameX, currentFrameY, angle);
}

void gdipManager::gdiFrameRender(string strKey, HDC hdc, int destX, int destY, float wRatio, float hRatio, int currentFrameX, int currentFrameY, InterpolationMode _imode, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiFrameRender(hdc, destX, destY, wRatio, hRatio, currentFrameX, currentFrameY, _imode, angle);
}


//========================================================================================================================================================
//	�̹��� ���ķ���
//========================================================================================================================================================
void gdipManager::gdiAlphaRender(string strKey, HDC hdc, float alpha, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiAlphaRender(hdc, alpha, angle);
}

void gdipManager::gdiAlphaRender(string strKey, HDC hdc, int destX, int destY, float alpha, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiAlphaRender(hdc, destX, destY, alpha, angle);
}

void gdipManager::gdiAlphaFrameRender(string strKey, HDC hdc, float alpha, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiAlphaFrameRender(hdc, alpha, angle);
}

void gdipManager::gdiAlphaFrameRender(string strKey, HDC hdc, int destX, int destY, float alpha, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiAlphaFrameRender(hdc, destX, destY, alpha, angle);
}


//========================================================================================================================================================
//	Threshold ����
//========================================================================================================================================================
void gdipManager::gdiThresholdRender(string strKey, HDC hdc, float value, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiThresholdRender(hdc, value, angle);
}

void gdipManager::gdiThresholdRender(string strKey, HDC hdc, int destX, int destY, float value, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiThresholdRender(hdc, destX, destY, value, angle);
}

void gdipManager::gdiThresholdFrameRender(string strKey, HDC hdc, float value, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiThresholdFrameRender(hdc, value, angle);
}

void gdipManager::gdiThresholdFrameRender(string strKey, HDC hdc, int destX, int destY, float value, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiThresholdFrameRender(hdc, value, destX, destY, angle);
}


//========================================================================================================================================================
//	Gamma ����
//========================================================================================================================================================
void gdipManager::gdiGammaRender(string strKey, HDC hdc, float value, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiGammaRender(hdc, value, angle);
}

void gdipManager::gdiGammaRender(string strKey, HDC hdc, int destX, int destY, float value, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiGammaRender(hdc, destX, destY, value, angle);
}

void gdipManager::gdiGammaFrameRender(string strKey, HDC hdc, float value, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiGammaFrameRender(hdc, value, angle);
}

void gdipManager::gdiGammaFrameRender(string strKey, HDC hdc, int destX, int destY, float value, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiGammaFrameRender(hdc, destX, destY, value, angle);
}


//========================================================================================================================================================
//	Lighten ����
//========================================================================================================================================================
void gdipManager::gdiLightenRender(string strKey, HDC hdc, float value, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiLightenRender(hdc, value, angle);
}

void gdipManager::gdiLightenRender(string strKey, HDC hdc, int destX, int destY, float value, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiLightenRender(hdc, destX, destY, value, angle);
}

void gdipManager::gdiLightenFrameRender(string strKey, HDC hdc, float value, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiLightenFrameRender(hdc, value, angle);
}

void gdipManager::gdiLightenFrameRender(string strKey, HDC hdc, int destX, int destY, float value, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiLightenFrameRender(hdc, destX, destY, value, angle);
}


//========================================================================================================================================================
//	Negative ����
//========================================================================================================================================================
void gdipManager::gdiNegativeRender(string strKey, HDC hdc, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiNegativeRender(hdc, angle);
}


void gdipManager::gdiNegativeRender(string strKey, HDC hdc, int destX, int destY, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiNegativeRender(hdc, destX, destY, angle);
}


void gdipManager::gdiNegativeFrameRender(string strKey, HDC hdc, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiNegativeFrameRender(hdc, angle);
}


void gdipManager::gdiNegativeFrameRender(string strKey, HDC hdc, int destX, int destY, int angle)
{
	gdipImage* gdiImg = findImage(strKey);
	if (gdiImg) gdiImg->gdiNegativeFrameRender(hdc, destX, destY, angle);
}