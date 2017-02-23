#include "stdafx.h"
#include "aStarScene.h"


HRESULT aStarScene::init(void)
{
	IMAGEMANAGER->addImage("1", "1.bmp", 32, 32, true, RGB(255, 0, 255));

	//���̽�Ÿ Ŭ���� �ʱ�ȭ
	_aStar = new aStar;
	_aStar->init();

	return S_OK;
}

void aStarScene::release(void)
{
	//���̽�Ÿ Ŭ���� ����
	SAFE_DELETE(_aStar);
}

void aStarScene::update(void)
{
	//���̽�Ÿ Ŭ���� ������Ʈ
	_aStar->update();
}

void aStarScene::render(void)
{
	//���̽�Ÿ Ŭ���� ����
	_aStar->render();
}
