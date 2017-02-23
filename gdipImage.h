#pragma once

class gdipImage
{
public:
	typedef struct tagGDI
	{
		HDC			hMemDC;				//�޸� DC
		HBITMAP		hBit;				//��Ʈ��
		HBITMAP		hOBit;				//�õ��Ʈ��
		float		x;					//�̹��� x��ǥ(����Ʈ)
		float		y;					//�̹��� y��ǥ(ž)
		int			width;				//�̹��� ����ũ��
		int			height;				//�̹��� ����ũ��
		int			currentFrameX;		//���������� x��ǥ
		int			currentFrameY;		//���������� y��ǥ
		int			maxFrameX;			//�ִ������� x����
		int			maxFrameY;			//�ִ������� y����
		int			frameWidth;			//1������ ����ũ��
		int			frameHeight;		//1������ ����ũ��

		tagGDI()
		{
			hMemDC = nullptr;
			hBit = nullptr;
			hOBit = nullptr;
			x = y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
		}
	}GDI_INFO, *LPGDI_INFO;

private:
	LPGDI_INFO		_gdiInfo;		//GDI����
	CHAR*			_fileName;		//�̹��� �̸�
	BOOL			_isTrans;		//���� ���� ����(����� ����)
	COLORREF		_transColor;	//���� ���� RGB��(����Ÿ = RGB(255, 0, 255))
	Graphics*		_gdi;
	Graphics*		_gdiRender;
	Image*			_gdiImg;

public:
	gdipImage() : _gdiInfo(nullptr), _fileName(nullptr), _isTrans(false), _transColor(RGB(0, 0, 0)) {}
	~gdipImage() {}
	void release();


//========================================================================================================================================================
//	�ʱ�ȭ
//========================================================================================================================================================
	HRESULT init(char* fileName, bool isTrans, COLORREF color = RGB(0, 0, 0), RotateFlipType rotateFlipType = RotateNoneFlipNone);
	HRESULT init(char* fileName, int destX, int destY, bool isTrans, COLORREF color = RGB(0, 0, 0), RotateFlipType rotateFlipType = RotateNoneFlipNone);
	HRESULT init(char* fileName, int destX, int destY, int maxFrameX, int maxFrameY, bool isTrans, COLORREF color = RGB(0, 0, 0), RotateFlipType rotateFlipType = RotateNoneFlipNone);

//========================================================================================================================================================
//	�̹��� ����
//========================================================================================================================================================
	void gdiRender(HDC hdc, int angle = 0);																				//����
	void gdiRender(HDC hdc, int destX, int destY, int angle = 0);														//���ϴ� ��ġ ����
	void gdiRender(HDC hdc, int destX, int destY, int width, int height, int angle = 0);								//���� Ȯ����� ����
	void gdiRender(HDC hdc, int destX, int destY, float wRatio, float hRatio, int angle = 0);								//���� Ȯ����� ����
	void gdiRender(HDC hdc, int destX, int destY, float wRatio, float hRatio, InterpolationMode _imode, int angle = 0);	//����(�̹����� Ȯ���ϰų� ����� ���� �߰��� �ȼ��� ���Եǰų� �������µ� �̶� ����Ǵ� �˰���) ��� 
	void gdiRender(HDC hdc, int destX, int destY, Point* ptDest, int angle = 0);										//����纯���� ����
	void gdiRender(HDC hdc, int destX, int destY, int srcX, int srcY, int srcWidth, int srcHeight, int angle = 0);		//���ϴ� �κ� ����

//========================================================================================================================================================
//	�������̹��� ����
//========================================================================================================================================================
	void gdiFrameRender(HDC hdc, int angle = 0);
	void gdiFrameRender(HDC hdc, int destX, int destY, int angle = 0);
	void gdiFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, int angle = 0);
	void gdiFrameRender(HDC hdc, int destX, int destY, int width, int height, int currentFrameX, int currentFrameY, int angle = 0);
	void gdiFrameRender(HDC hdc, int destX, int destY, float wRatio, float hRatio, int currentFrameX, int currentFrameY, int angle = 0);
	void gdiFrameRender(HDC hdc, int destX, int destY, float wRatio, float hRatio, int currentFrameX, int currentFrameY, InterpolationMode _imode, int angle = 0);

//========================================================================================================================================================
//	�̹��� ���ķ���
//========================================================================================================================================================
	void gdiAlphaRender(HDC hdc, float alpha, int angle = 0);
	void gdiAlphaRender(HDC hdc, int destX, int destY, float alpha, int angle = 0);
	void gdiAlphaFrameRender(HDC hdc, float alpha, int angle = 0);
	void gdiAlphaFrameRender(HDC hdc, int destX, int destY, float alpha, int angle = 0);

//========================================================================================================================================================
//	Threshold ����
//========================================================================================================================================================
	void gdiThresholdRender(HDC hdc, float value, int angle = 0);
	void gdiThresholdRender(HDC hdc, int destX, int destY, float value, int angle = 0);
	void gdiThresholdFrameRender(HDC hdc, float value, int angle = 0);
	void gdiThresholdFrameRender(HDC hdc, int destX, int destY, float value, int angle = 0);

//========================================================================================================================================================
//	Gamma ����
//========================================================================================================================================================
	void gdiGammaRender(HDC hdc, float value, int angle = 0);
	void gdiGammaRender(HDC hdc, int destX, int destY, float value, int angle = 0);
	void gdiGammaFrameRender(HDC hdc, float value, int angle = 0);
	void gdiGammaFrameRender(HDC hdc, int destX, int destY, float value, int angle = 0);

//========================================================================================================================================================
//	Lighten ����
//========================================================================================================================================================
	void gdiLightenRender(HDC hdc, float value, int angle = 0);
	void gdiLightenRender(HDC hdc, int destX, int destY, float value, int angle = 0);
	void gdiLightenFrameRender(HDC hdc, float value, int angle = 0);
	void gdiLightenFrameRender(HDC hdc, int destX, int destY, float value, int angle = 0);

//========================================================================================================================================================
//	Negative ����
//========================================================================================================================================================
	void gdiNegativeRender(HDC hdc, int angle = 0);
	void gdiNegativeRender(HDC hdc, int destX, int destY, int angle = 0);
	void gdiNegativeFrameRender(HDC hdc, int angle = 0);
	void gdiNegativeFrameRender(HDC hdc, int destX, int destY, int angle = 0);

//========================================================================================================================================================
//	������,������
//========================================================================================================================================================
	inline int getFrameX()const { return _gdiInfo->currentFrameX; }
	inline void setFrameX(int frameX) { _gdiInfo->currentFrameX = frameX; }
	inline int getFrameY()const { return _gdiInfo->currentFrameY; }
	inline void setFrameY(int frameY) { _gdiInfo->currentFrameY = frameY; }
};