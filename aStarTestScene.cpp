#include "stdafx.h"
#include "aStarTestScene.h"

HRESULT aStarTestScene::init(void)
{
	//���̽�Ÿ Ŭ���� �ʱ�ȭ
	_aStar = new aStarTest;
	_aStar->init();

	return S_OK;
}

void aStarTestScene::release(void)
{
	//���̽�Ÿ Ŭ���� ����
	SAFE_DELETE(_aStar);
}

void aStarTestScene::update(void)
{
	//���̽�Ÿ Ŭ���� ������Ʈ
	_aStar->update();
}

void aStarTestScene::render(void)
{
	//���̽�Ÿ Ŭ���� ����
	_aStar->render();
}
