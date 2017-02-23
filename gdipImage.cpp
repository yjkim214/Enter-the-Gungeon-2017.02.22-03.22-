#include "stdafx.h"
#include "gdipImage.h"
#include <atlconv.h>

//========================================================================================================================================================
//	�ʱ�ȭ
//========================================================================================================================================================
HRESULT gdipImage::init(char* fileName, bool isTrans, COLORREF color, RotateFlipType rotateFlipType)
{
	USES_CONVERSION;

	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ��������� ���ٰ�!
	if (_gdiInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ���� ���� �� �ʱ�ȭ�ϱ�
	_gdiInfo = new GDI_INFO;

	WCHAR* wstr = A2W(fileName);
	_gdiImg = new Image(wstr);

	//�̹��� ���� ���� ���� �� �ʱ�ȭ�ϱ�
	_gdiInfo = new GDI_INFO;
	_gdiImg->RotateFlip(rotateFlipType);
	_gdiInfo->width = _gdiImg->GetWidth();
	_gdiInfo->height = _gdiImg->GetHeight();

	_isTrans = isTrans;
	_transColor = color;

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT gdipImage::init(char * fileName, int destX, int destY, bool isTrans, COLORREF color, RotateFlipType rotateFlipType)
{
	USES_CONVERSION;

	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ��������� ���ٰ�!
	if (_gdiInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ���� ���� �� �ʱ�ȭ�ϱ�
	_gdiInfo = new GDI_INFO;

	//_gdiImg = new Image(ConvertCtoWC(fileName));
	WCHAR* wstr = A2W(fileName);
	_gdiImg = new Image(wstr);


	//�̹��� ���� ���� ���� �� �ʱ�ȭ�ϱ�
	_gdiInfo = new GDI_INFO;
	_gdiInfo->x = destX;
	_gdiInfo->y = destY;
	_gdiImg->RotateFlip(rotateFlipType);
	_gdiInfo->width = _gdiImg->GetWidth();
	_gdiInfo->height = _gdiImg->GetHeight();

	_isTrans = isTrans;
	_transColor = color;

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT gdipImage::init(char * fileName, int destX, int destY, int maxFrameX, int maxFrameY, bool isTrans, COLORREF color, RotateFlipType rotateFlipType)
{
	USES_CONVERSION;

	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ��������� ���ٰ�!
	if (_gdiInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ���� ���� �� �ʱ�ȭ�ϱ�
	_gdiInfo = new GDI_INFO;

	WCHAR* wstr = A2W(fileName);
	_gdiImg = new Image(wstr);

	//�̹��� ���� ���� ���� �� �ʱ�ȭ�ϱ�
	_gdiInfo = new GDI_INFO;
	_gdiInfo->x = destX;
	_gdiInfo->y = destY;
	_gdiInfo->width = _gdiImg->GetWidth();
	_gdiInfo->height = _gdiImg->GetHeight();
	_gdiInfo->currentFrameX = 0;
	_gdiInfo->currentFrameY = 0;
	_gdiInfo->maxFrameX = maxFrameX - 1;
	_gdiInfo->maxFrameY = maxFrameY - 1;
	_gdiInfo->frameWidth = _gdiImg->GetWidth() / maxFrameX;
	_gdiInfo->frameHeight = _gdiImg->GetHeight() / maxFrameY;
	_gdiImg->RotateFlip(rotateFlipType);

	_isTrans = isTrans;
	_transColor = color;

	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

void gdipImage::release(void)
{
	if (_gdiInfo)
	{
		DeleteDC(_gdiInfo->hMemDC);
		SAFE_DELETE(_gdiInfo);
		SAFE_DELETE(_gdiImg);
	}
}


//========================================================================================================================================================
//	�̹��� ����
//========================================================================================================================================================
void gdipImage::gdiRender(HDC hdc, int angle)
{
	ImageAttributes imageAttr;
	if (_isTrans) imageAttr.SetColorKey(_transColor, _transColor);

	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(_gdiInfo->x), float(_gdiInfo->y)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->DrawImage(_gdiImg, Rect(_gdiInfo->x, _gdiInfo->y, _gdiInfo->width, _gdiInfo->height), 0, 0, _gdiInfo->width, _gdiInfo->height, UnitPixel, &imageAttr);

	SAFE_DELETE(_gdiRender);
}

void gdipImage::gdiRender(HDC hdc, int destX, int destY, int angle)
{
	ImageAttributes imageAttr;
	if (_isTrans) imageAttr.SetColorKey(_transColor, _transColor);

	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(destX), float(destY)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->DrawImage(_gdiImg, Rect(destX, destY, _gdiInfo->width, _gdiInfo->height), 0, 0, _gdiInfo->width, _gdiInfo->height, UnitPixel, &imageAttr);
	SAFE_DELETE(_gdiRender);
}

void gdipImage::gdiRender(HDC hdc, int destX, int destY, int width, int height, int angle)
{
	ImageAttributes imageAttr;
	if (_isTrans) imageAttr.SetColorKey(_transColor, _transColor);

	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(destX), float(destY)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->DrawImage(_gdiImg, Rect(destX, destY, width, height), 0, 0, _gdiInfo->width, _gdiInfo->height, UnitPixel, &imageAttr);
	SAFE_DELETE(_gdiRender);
}

void gdipImage::gdiRender(HDC hdc, int destX, int destY, float wRatio, float hRatio, int angle)
{
	ImageAttributes imageAttr;
	if (_isTrans) imageAttr.SetColorKey(_transColor, _transColor);

	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(destX), float(destY)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->DrawImage(_gdiImg, Rect(destX, destY, _gdiInfo->width*wRatio, _gdiInfo->height*hRatio), 0, 0, _gdiInfo->width, _gdiInfo->height, UnitPixel, &imageAttr);
	SAFE_DELETE(_gdiRender);
}

void gdipImage::gdiRender(HDC hdc, int destX, int destY, float wRatio, float hRatio, InterpolationMode _imode, int angle)
{
	InterpolationMode imode = _imode;

	ImageAttributes imageAttr;
	if (_isTrans) imageAttr.SetColorKey(_transColor, _transColor);

	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(destX), float(destY)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->SetInterpolationMode(imode);
	_gdiRender->DrawImage(_gdiImg, Rect(destX, destY, _gdiInfo->width*wRatio, _gdiInfo->height*hRatio), 0, 0, _gdiInfo->width, _gdiInfo->height, UnitPixel, &imageAttr);
	SAFE_DELETE(_gdiRender);
}

void gdipImage::gdiRender(HDC hdc, int destX, int destY, Point * ptDest, int angle)
{
	ImageAttributes imageAttr;
	if (_isTrans) imageAttr.SetColorKey(_transColor, _transColor);

	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(destX), float(destY)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->DrawImage(_gdiImg, ptDest, 3, 0, 0, _gdiInfo->width, _gdiInfo->height, UnitPixel, &imageAttr);
	SAFE_DELETE(_gdiRender);
}

void gdipImage::gdiRender(HDC hdc, int destX, int destY, int srcX, int srcY, int srcWidth, int srcHeight, int angle)
{
	ImageAttributes imageAttr;
	if (_isTrans) imageAttr.SetColorKey(_transColor, _transColor);

	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(destX), float(destY)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->DrawImage(_gdiImg, Rect(destX, destY, srcWidth, srcHeight), srcX, srcY, srcWidth, srcHeight, UnitPixel, &imageAttr);
	SAFE_DELETE(_gdiRender);
}


//========================================================================================================================================================
//	�������̹��� ����
//========================================================================================================================================================
void gdipImage::gdiFrameRender(HDC hdc, int angle)
{
	if (_gdiInfo->currentFrameX > _gdiInfo->maxFrameX)
	{
		_gdiInfo->currentFrameX = _gdiInfo->maxFrameX;
	}
	if (_gdiInfo->currentFrameY > _gdiInfo->maxFrameY)
	{
		_gdiInfo->currentFrameY = _gdiInfo->maxFrameY;
	}


	ImageAttributes imageAttr;
	if (_isTrans) imageAttr.SetColorKey(_transColor, _transColor);

	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(_gdiInfo->x), float(_gdiInfo->y)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->DrawImage(_gdiImg,
		Rect(
			_gdiInfo->x,
			_gdiInfo->y,
			_gdiInfo->frameWidth, _gdiInfo->frameHeight),
		_gdiInfo->currentFrameX * _gdiInfo->frameWidth,
		_gdiInfo->currentFrameY * _gdiInfo->frameHeight,
		_gdiInfo->frameWidth, _gdiInfo->frameHeight,
		UnitPixel, &imageAttr);
	SAFE_DELETE(_gdiRender);
}

void gdipImage::gdiFrameRender(HDC hdc, int destX, int destY, int angle)
{
	if (_gdiInfo->currentFrameX > _gdiInfo->maxFrameX)
	{
		_gdiInfo->currentFrameX = _gdiInfo->maxFrameX;
	}
	if (_gdiInfo->currentFrameY > _gdiInfo->maxFrameY)
	{
		_gdiInfo->currentFrameY = _gdiInfo->maxFrameY;
	}

	ImageAttributes imageAttr;
	if (_isTrans) imageAttr.SetColorKey(_transColor, _transColor);

	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(destX), float(destY)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->DrawImage(_gdiImg,
		Rect(
			destX,
			destY,
			_gdiInfo->frameWidth, _gdiInfo->frameHeight),
		_gdiInfo->currentFrameX * _gdiInfo->frameWidth,
		_gdiInfo->currentFrameY * _gdiInfo->frameHeight,
		_gdiInfo->frameWidth, _gdiInfo->frameHeight,
		UnitPixel, &imageAttr);
	SAFE_DELETE(_gdiRender);
}

void gdipImage::gdiFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, int angle)
{
	//�̹��� ����ó�� - �Է� ���� ������ ������ �ִ� ������ �������� Ŭ �� �۵���
	_gdiInfo->currentFrameX = currentFrameX;
	_gdiInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _gdiInfo->maxFrameX)
	{
		_gdiInfo->currentFrameX = _gdiInfo->maxFrameX;
	}
	if (currentFrameY > _gdiInfo->maxFrameY)
	{
		_gdiInfo->currentFrameY = _gdiInfo->maxFrameY;
	}

	ImageAttributes imageAttr;
	if (_isTrans) imageAttr.SetColorKey(_transColor, _transColor);

	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(destX), float(destY)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->DrawImage(_gdiImg,
		Rect(
			destX,
			destY,
			_gdiInfo->frameWidth, _gdiInfo->frameHeight),
		_gdiInfo->currentFrameX * _gdiInfo->frameWidth,
		_gdiInfo->currentFrameY * _gdiInfo->frameHeight,
		_gdiInfo->frameWidth, _gdiInfo->frameHeight,
		UnitPixel, &imageAttr);
	SAFE_DELETE(_gdiRender);
}

void gdipImage::gdiFrameRender(HDC hdc, int destX, int destY, int width, int height, int currentFrameX, int currentFrameY, int angle)
{
	_gdiInfo->currentFrameX = currentFrameX;
	_gdiInfo->currentFrameY = currentFrameY;
	if (_gdiInfo->currentFrameX > _gdiInfo->maxFrameX)
	{
		_gdiInfo->currentFrameX = _gdiInfo->maxFrameX;
	}
	if (_gdiInfo->currentFrameY > _gdiInfo->maxFrameY)
	{
		_gdiInfo->currentFrameY = _gdiInfo->maxFrameY;
	}

	ImageAttributes imageAttr;
	if (_isTrans) imageAttr.SetColorKey(_transColor, _transColor);

	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(destX), float(destY)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->DrawImage(_gdiImg,
		Rect(
			destX,
			destY,
			width, height),
		_gdiInfo->currentFrameX * _gdiInfo->frameWidth,
		_gdiInfo->currentFrameY * _gdiInfo->frameHeight,
		_gdiInfo->frameWidth, _gdiInfo->frameHeight,
		UnitPixel, &imageAttr);
	SAFE_DELETE(_gdiRender);
}

void gdipImage::gdiFrameRender(HDC hdc, int destX, int destY, float wRatio, float hRatio, int currentFrameX, int currentFrameY, int angle)
{
	_gdiInfo->currentFrameX = currentFrameX;
	_gdiInfo->currentFrameY = currentFrameY;
	if (_gdiInfo->currentFrameX > _gdiInfo->maxFrameX)
	{
		_gdiInfo->currentFrameX = _gdiInfo->maxFrameX;
	}
	if (_gdiInfo->currentFrameY > _gdiInfo->maxFrameY)
	{
		_gdiInfo->currentFrameY = _gdiInfo->maxFrameY;
	}

	ImageAttributes imageAttr;
	if (_isTrans) imageAttr.SetColorKey(_transColor, _transColor);

	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(destX), float(destY)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->DrawImage(_gdiImg,
		Rect(
			destX,
			destY,
			_gdiInfo->frameWidth * wRatio, _gdiInfo->frameHeight* hRatio),
		_gdiInfo->currentFrameX * _gdiInfo->frameWidth,
		_gdiInfo->currentFrameY * _gdiInfo->frameHeight,
		_gdiInfo->frameWidth, _gdiInfo->frameHeight,
		UnitPixel, &imageAttr);
	SAFE_DELETE(_gdiRender);
}

void gdipImage::gdiFrameRender(HDC hdc, int destX, int destY, float wRatio, float hRatio, int currentFrameX, int currentFrameY, InterpolationMode _imode, int angle)
{
	InterpolationMode imode = _imode;

	_gdiInfo->currentFrameX = currentFrameX;
	_gdiInfo->currentFrameY = currentFrameY;
	if (_gdiInfo->currentFrameX > _gdiInfo->maxFrameX)
	{
		_gdiInfo->currentFrameX = _gdiInfo->maxFrameX;
	}
	if (_gdiInfo->currentFrameY > _gdiInfo->maxFrameY)
	{
		_gdiInfo->currentFrameY = _gdiInfo->maxFrameY;
	}

	ImageAttributes imageAttr;
	if (_isTrans) imageAttr.SetColorKey(_transColor, _transColor);

	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(destX), float(destY)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->SetInterpolationMode(imode);
	_gdiRender->DrawImage(_gdiImg,
		Rect(
			destX,
			destY,
			_gdiInfo->frameWidth * wRatio, _gdiInfo->frameHeight* hRatio),
		_gdiInfo->currentFrameX * _gdiInfo->frameWidth,
		_gdiInfo->currentFrameY * _gdiInfo->frameHeight,
		_gdiInfo->frameWidth, _gdiInfo->frameHeight,
		UnitPixel, &imageAttr);
	SAFE_DELETE(_gdiRender);
}


//========================================================================================================================================================
//	�̹��� ���ķ���
//========================================================================================================================================================
void gdipImage::gdiAlphaRender(HDC hdc, float alpha, int angle)
{
	if (_gdiInfo->currentFrameX > _gdiInfo->maxFrameX)
	{
		_gdiInfo->currentFrameX = _gdiInfo->maxFrameX;
	}
	if (_gdiInfo->currentFrameY > _gdiInfo->maxFrameY)
	{
		_gdiInfo->currentFrameY = _gdiInfo->maxFrameY;
	}

	// ���� ��
	REAL rTransparency = alpha;    // 0.1f ~ 1.0f

	ColorMatrix colorMatrix = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, rTransparency, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 1.0f };


	ImageAttributes imageAtt;
	imageAtt.SetColorMatrix(&colorMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);

	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(_gdiInfo->x), float(_gdiInfo->y)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->DrawImage(_gdiImg, Rect(0, 0, _gdiInfo->width, _gdiInfo->height), 0, 0, _gdiInfo->width, _gdiInfo->height, UnitPixel, &imageAtt);
	SAFE_DELETE(_gdiRender);
}

void gdipImage::gdiAlphaRender(HDC hdc, int destX, int destY, float alpha, int angle)
{
	// ���� ��
	REAL rTransparency = alpha;    // 0.1f ~ 1.0f

	ColorMatrix colorMatrix = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, rTransparency, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 1.0f };


	ImageAttributes imageAtt;
	imageAtt.SetColorMatrix(&colorMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);

	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(destX), float(destY)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->DrawImage(_gdiImg, Rect(destX, destY, _gdiInfo->width, _gdiInfo->height), 0, 0, _gdiInfo->width, _gdiInfo->height, UnitPixel, &imageAtt);
	SAFE_DELETE(_gdiRender);
}

void gdipImage::gdiAlphaFrameRender(HDC hdc, float alpha, int angle)
{
	// ���� ��
	REAL rTransparency = alpha;    // 0.1f ~ 1.0f

	ColorMatrix colorMatrix = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, rTransparency, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 1.0f };


	ImageAttributes imageAtt;
	imageAtt.SetColorMatrix(&colorMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);

	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(_gdiInfo->x), float(_gdiInfo->y)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->DrawImage(_gdiImg, Rect(_gdiInfo->x, _gdiInfo->y, _gdiInfo->frameWidth, _gdiInfo->frameHeight),
		_gdiInfo->currentFrameX * _gdiInfo->frameWidth,
		_gdiInfo->currentFrameY * _gdiInfo->frameHeight,
		_gdiInfo->frameWidth, _gdiInfo->frameHeight, UnitPixel, &imageAtt);
	SAFE_DELETE(_gdiRender);
}

void gdipImage::gdiAlphaFrameRender(HDC hdc, int destX, int destY, float alpha, int angle)
{
	// ���� ��
	REAL rTransparency = alpha;    // 0.1f ~ 1.0f

	ColorMatrix colorMatrix = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, rTransparency, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 1.0f };


	ImageAttributes imageAtt;
	imageAtt.SetColorMatrix(&colorMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);

	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(destX), float(destY)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->DrawImage(_gdiImg, Rect(destX, destY, _gdiInfo->frameWidth, _gdiInfo->frameHeight),
		_gdiInfo->currentFrameX * _gdiInfo->frameWidth,
		_gdiInfo->currentFrameY * _gdiInfo->frameHeight,
		_gdiInfo->frameWidth, _gdiInfo->frameHeight, UnitPixel, &imageAtt);
	SAFE_DELETE(_gdiRender);
}


//========================================================================================================================================================
//	Threshold ����
//========================================================================================================================================================
void gdipImage::gdiThresholdRender(HDC hdc, float value, int angle)
{
	ImageAttributes   IA;
	IA.SetThreshold(value, ColorAdjustTypeDefault);
	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(_gdiInfo->x), float(_gdiInfo->y)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->DrawImage(_gdiImg, Rect(_gdiInfo->x, _gdiInfo->y, _gdiInfo->width, _gdiInfo->height),
		0, 0, _gdiInfo->width, _gdiInfo->height, UnitPixel, &IA);
}

void gdipImage::gdiThresholdRender(HDC hdc, int destX, int destY, float value, int angle)
{
	ImageAttributes   IA;
	IA.SetThreshold(value, ColorAdjustTypeDefault);
	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(destX), float(destY)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->DrawImage(_gdiImg, Rect(destX, destY, _gdiInfo->width, _gdiInfo->height),
		0, 0, _gdiInfo->width, _gdiInfo->height, UnitPixel, &IA);
}

void gdipImage::gdiThresholdFrameRender(HDC hdc, float value, int angle)
{
	if (_gdiInfo->currentFrameX > _gdiInfo->maxFrameX)
	{
		_gdiInfo->currentFrameX = _gdiInfo->maxFrameX;
	}
	if (_gdiInfo->currentFrameY > _gdiInfo->maxFrameY)
	{
		_gdiInfo->currentFrameY = _gdiInfo->maxFrameY;
	}

	ImageAttributes   IA;
	IA.SetThreshold(value, ColorAdjustTypeDefault);
	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(_gdiInfo->x), float(_gdiInfo->y)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->DrawImage(_gdiImg, Rect(_gdiInfo->x, _gdiInfo->y, _gdiInfo->frameWidth, _gdiInfo->frameHeight),
		_gdiInfo->currentFrameX * _gdiInfo->frameWidth,
		_gdiInfo->currentFrameY *_gdiInfo->frameHeight,
		_gdiInfo->frameWidth, _gdiInfo->frameHeight, UnitPixel, &IA);
}

void gdipImage::gdiThresholdFrameRender(HDC hdc, int destX, int destY, float value, int angle)
{
	if (_gdiInfo->currentFrameX > _gdiInfo->maxFrameX)
	{
		_gdiInfo->currentFrameX = _gdiInfo->maxFrameX;
	}
	if (_gdiInfo->currentFrameY > _gdiInfo->maxFrameY)
	{
		_gdiInfo->currentFrameY = _gdiInfo->maxFrameY;
	}

	ImageAttributes   IA;
	IA.SetThreshold(value, ColorAdjustTypeDefault);
	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(destX), float(destY)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->DrawImage(_gdiImg, Rect(_gdiInfo->x, _gdiInfo->y, _gdiInfo->frameWidth, _gdiInfo->frameHeight),
		_gdiInfo->currentFrameX * _gdiInfo->frameWidth,
		_gdiInfo->currentFrameY *_gdiInfo->frameHeight,
		_gdiInfo->frameWidth, _gdiInfo->frameHeight, UnitPixel, &IA);
}


//========================================================================================================================================================
//	Gamma ����
//========================================================================================================================================================
void gdipImage::gdiGammaRender(HDC hdc, float value, int angle)
{
	ImageAttributes   IA;
	IA.SetGamma(value, ColorAdjustTypeDefault);
	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(_gdiInfo->x), float(_gdiInfo->y)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->DrawImage(_gdiImg, Rect(_gdiInfo->x, _gdiInfo->y, _gdiInfo->width, _gdiInfo->height),
		0, 0, _gdiInfo->width, _gdiInfo->height, UnitPixel, &IA);
}

void gdipImage::gdiGammaRender(HDC hdc, int destX, int destY, float value, int angle)
{
	ImageAttributes   IA;
	IA.SetGamma(value, ColorAdjustTypeDefault);
	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(destX), float(destY)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->DrawImage(_gdiImg, Rect(destX, destY, _gdiInfo->width, _gdiInfo->height),
		0, 0, _gdiInfo->width, _gdiInfo->height, UnitPixel, &IA);
}

void gdipImage::gdiGammaFrameRender(HDC hdc, float value, int angle)
{
	if (_gdiInfo->currentFrameX > _gdiInfo->maxFrameX)
	{
		_gdiInfo->currentFrameX = _gdiInfo->maxFrameX;
	}
	if (_gdiInfo->currentFrameY > _gdiInfo->maxFrameY)
	{
		_gdiInfo->currentFrameY = _gdiInfo->maxFrameY;
	}

	ImageAttributes   IA;
	IA.SetGamma(value, ColorAdjustTypeDefault);
	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(_gdiInfo->x), float(_gdiInfo->y)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->DrawImage(_gdiImg, Rect(_gdiInfo->x, _gdiInfo->y, _gdiInfo->frameWidth, _gdiInfo->frameHeight),
		_gdiInfo->currentFrameX * _gdiInfo->frameWidth,
		_gdiInfo->currentFrameY *_gdiInfo->frameHeight,
		_gdiInfo->frameWidth, _gdiInfo->frameHeight, UnitPixel, &IA);
}

void gdipImage::gdiGammaFrameRender(HDC hdc, int destX, int destY, float value, int angle)
{
	if (_gdiInfo->currentFrameX > _gdiInfo->maxFrameX)
	{
		_gdiInfo->currentFrameX = _gdiInfo->maxFrameX;
	}
	if (_gdiInfo->currentFrameY > _gdiInfo->maxFrameY)
	{
		_gdiInfo->currentFrameY = _gdiInfo->maxFrameY;
	}

	ImageAttributes   IA;
	IA.SetGamma(value, ColorAdjustTypeDefault);
	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(destX), float(destY)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->DrawImage(_gdiImg, Rect(_gdiInfo->x, _gdiInfo->y, _gdiInfo->frameWidth, _gdiInfo->frameHeight),
		_gdiInfo->currentFrameX * _gdiInfo->frameWidth,
		_gdiInfo->currentFrameY *_gdiInfo->frameHeight,
		_gdiInfo->frameWidth, _gdiInfo->frameHeight, UnitPixel, &IA);
}

//========================================================================================================================================================
//	Lighten ����
//========================================================================================================================================================
void gdipImage::gdiLightenRender(HDC hdc, float value, int angle)
{
	ImageAttributes   IA;

	ColorMatrix matrix = {
		1.0f,   0.0f,   0.0f,   0.0f,  0.0f,
		0.0f,   1.0f,   0.0f,   0.0f,  0.0f,
		0.0f,   0.0f,   1.0f,   0.0f,  0.0f,
		0.0f,   0.0f,   0.0f,   1.0f,  0.0f,
		value,     value,     value,     0.0f,   1.0f
	};

	IA.SetColorMatrix(&matrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(_gdiInfo->x), float(_gdiInfo->y)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->DrawImage(_gdiImg, Rect(_gdiInfo->x, _gdiInfo->y, _gdiInfo->width, _gdiInfo->height),
		0, 0, _gdiInfo->width, _gdiInfo->height, UnitPixel, &IA);
}

void gdipImage::gdiLightenRender(HDC hdc, int destX, int destY, float value, int angle)
{
	ImageAttributes   IA;

	ColorMatrix matrix = {
		1.0f,   0.0f,   0.0f,   0.0f,  0.0f,
		0.0f,   1.0f,   0.0f,   0.0f,  0.0f,
		0.0f,   0.0f,   1.0f,   0.0f,  0.0f,
		0.0f,   0.0f,   0.0f,   1.0f,  0.0f,
		value,     value,     value,     0.0f,   1.0f
	};

	IA.SetColorMatrix(&matrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(destX), float(destY)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->DrawImage(_gdiImg, Rect(destX, destY, _gdiInfo->width, _gdiInfo->height),
		0, 0, _gdiInfo->width, _gdiInfo->height, UnitPixel, &IA);
}

void gdipImage::gdiLightenFrameRender(HDC hdc, float value, int angle)
{
	if (_gdiInfo->currentFrameX > _gdiInfo->maxFrameX)
	{
		_gdiInfo->currentFrameX = _gdiInfo->maxFrameX;
	}
	if (_gdiInfo->currentFrameY > _gdiInfo->maxFrameY)
	{
		_gdiInfo->currentFrameY = _gdiInfo->maxFrameY;
	}

	ImageAttributes   IA;

	ColorMatrix matrix = {
		1.0f,   0.0f,   0.0f,   0.0f,  0.0f,
		0.0f,   1.0f,   0.0f,   0.0f,  0.0f,
		0.0f,   0.0f,   1.0f,   0.0f,  0.0f,
		0.0f,   0.0f,   0.0f,   1.0f,  0.0f,
		value,     value,     value,     0.0f,   1.0f
	};

	IA.SetColorMatrix(&matrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(_gdiInfo->x), float(_gdiInfo->y)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->DrawImage(_gdiImg, Rect(_gdiInfo->x, _gdiInfo->y, _gdiInfo->frameWidth, _gdiInfo->frameHeight),
		_gdiInfo->currentFrameX * _gdiInfo->frameWidth,
		_gdiInfo->currentFrameY *_gdiInfo->frameHeight,
		_gdiInfo->frameWidth, _gdiInfo->frameHeight, UnitPixel, &IA);
}

void gdipImage::gdiLightenFrameRender(HDC hdc, int destX, int destY, float value, int angle)
{
	if (_gdiInfo->currentFrameX > _gdiInfo->maxFrameX)
	{
		_gdiInfo->currentFrameX = _gdiInfo->maxFrameX;
	}
	if (_gdiInfo->currentFrameY > _gdiInfo->maxFrameY)
	{
		_gdiInfo->currentFrameY = _gdiInfo->maxFrameY;
	}

	ImageAttributes   IA;

	ColorMatrix matrix = {
		1.0f,   0.0f,   0.0f,   0.0f,  0.0f,
		0.0f,   1.0f,   0.0f,   0.0f,  0.0f,
		0.0f,   0.0f,   1.0f,   0.0f,  0.0f,
		0.0f,   0.0f,   0.0f,   1.0f,  0.0f,
		value,     value,     value,     0.0f,   1.0f
	};

	IA.SetColorMatrix(&matrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(destX), float(destY)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->DrawImage(_gdiImg, Rect(_gdiInfo->x, _gdiInfo->y, _gdiInfo->frameWidth, _gdiInfo->frameHeight),
		_gdiInfo->currentFrameX * _gdiInfo->frameWidth,
		_gdiInfo->currentFrameY *_gdiInfo->frameHeight,
		_gdiInfo->frameWidth, _gdiInfo->frameHeight, UnitPixel, &IA);
}


//========================================================================================================================================================
//	Negative ����
//========================================================================================================================================================
void gdipImage::gdiNegativeRender(HDC hdc, int angle)
{
	ImageAttributes   IA;

	ColorMatrix matrix = {
		-1.0f, 0.0f,   0.0f,   0.0f,  0.0f,
		0.0f,   -1.0f, 0.0f,   0.0f,  0.0f,
		0.0f,   0.0f,   -1.0f, 0.0f,  0.0f,
		0.0f,   0.0f,   0.0f,   1.0f,  0.0f,
		1.0f,   1.0f,   1.0f,   0.0f,  1.0f
	};

	IA.SetColorMatrix(&matrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(_gdiInfo->x), float(_gdiInfo->y)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->DrawImage(_gdiImg, Rect(_gdiInfo->x, _gdiInfo->y, _gdiInfo->width, _gdiInfo->height),
		0, 0, _gdiInfo->width, _gdiInfo->height, UnitPixel, &IA);
}

void gdipImage::gdiNegativeRender(HDC hdc, int destX, int destY, int angle)
{
	ImageAttributes   IA;

	ColorMatrix matrix = {
		-1.0f, 0.0f,   0.0f,   0.0f,  0.0f,
		0.0f,   -1.0f, 0.0f,   0.0f,  0.0f,
		0.0f,   0.0f,   -1.0f, 0.0f,  0.0f,
		0.0f,   0.0f,   0.0f,   1.0f,  0.0f,
		1.0f,   1.0f,   1.0f,   0.0f,  1.0f
	};

	IA.SetColorMatrix(&matrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(destX), float(destY)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->DrawImage(_gdiImg, Rect(destX, destY, _gdiInfo->width, _gdiInfo->height),
		0, 0, _gdiInfo->width, _gdiInfo->height, UnitPixel, &IA);
}

void gdipImage::gdiNegativeFrameRender(HDC hdc, int angle)
{
	if (_gdiInfo->currentFrameX > _gdiInfo->maxFrameX)
	{
		_gdiInfo->currentFrameX = _gdiInfo->maxFrameX;
	}
	if (_gdiInfo->currentFrameY > _gdiInfo->maxFrameY)
	{
		_gdiInfo->currentFrameY = _gdiInfo->maxFrameY;
	}

	ImageAttributes   IA;

	ColorMatrix matrix = {
		-1.0f, 0.0f,   0.0f,   0.0f,  0.0f,
		0.0f,   -1.0f, 0.0f,   0.0f,  0.0f,
		0.0f,   0.0f,   -1.0f, 0.0f,  0.0f,
		0.0f,   0.0f,   0.0f,   1.0f,  0.0f,
		1.0f,   1.0f,   1.0f,   0.0f,  1.0f
	};

	IA.SetColorMatrix(&matrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(_gdiInfo->x), float(_gdiInfo->y)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->DrawImage(_gdiImg, Rect(_gdiInfo->x, _gdiInfo->y, _gdiInfo->frameWidth, _gdiInfo->frameHeight),
		_gdiInfo->currentFrameX * _gdiInfo->frameWidth,
		_gdiInfo->currentFrameY *_gdiInfo->frameHeight,
		_gdiInfo->frameWidth, _gdiInfo->frameHeight, UnitPixel, &IA);
}

void gdipImage::gdiNegativeFrameRender(HDC hdc, int destX, int destY, int angle)
{
	if (_gdiInfo->currentFrameX > _gdiInfo->maxFrameX)
	{
		_gdiInfo->currentFrameX = _gdiInfo->maxFrameX;
	}
	if (_gdiInfo->currentFrameY > _gdiInfo->maxFrameY)
	{
		_gdiInfo->currentFrameY = _gdiInfo->maxFrameY;
	}

	ImageAttributes   IA;

	ColorMatrix matrix = {
		-1.0f, 0.0f,   0.0f,   0.0f,  0.0f,
		0.0f,   -1.0f, 0.0f,   0.0f,  0.0f,
		0.0f,   0.0f,   -1.0f, 0.0f,  0.0f,
		0.0f,   0.0f,   0.0f,   1.0f,  0.0f,
		1.0f,   1.0f,   1.0f,   0.0f,  1.0f
	};

	IA.SetColorMatrix(&matrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
	_gdiRender = new Graphics(hdc);

	Matrix mat;
	mat.RotateAt(angle, PointF(float(destX), float(destY)));
	_gdiRender->SetTransform(&mat);

	_gdiRender->DrawImage(_gdiImg, Rect(destX, destY, _gdiInfo->frameWidth, _gdiInfo->frameHeight),
		_gdiInfo->currentFrameX * _gdiInfo->frameWidth,
		_gdiInfo->currentFrameY *_gdiInfo->frameHeight,
		_gdiInfo->frameWidth, _gdiInfo->frameHeight, UnitPixel, &IA);
}