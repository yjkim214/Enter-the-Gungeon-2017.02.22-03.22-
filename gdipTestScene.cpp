#include "stdafx.h"
#include "gdipTestScene.h"

HRESULT gdipTestScene::init()
{
	//png, jpg�� �̹��� ���� �� ���� �� ����
	//png���Ϻ��� jpg������ ������ ���ϱ� �� �ϴ�
	//�׷��� ������ ������ png���� �̴� �˾Ƽ��� �ϸ� �ȴ�
	GDIPLUS->addImage("ȿ����", "pngImage/ȿ��.png");
	//GDIPLUS->addImage("ȿ����", "pngImage/ȿ��.jpg");

	return S_OK;
}

void gdipTestScene::release()
{
}

void gdipTestScene::update()
{
}

void gdipTestScene::render()
{
	//���� �׽�Ʈ �� �غ���
	GDIPLUS->gdiRender("ȿ����", getMemDC());
	GDIPLUS->gdiRender("ȿ����", getMemDC(), 200, 200, 200, 200, 200, 200, 45);
}
