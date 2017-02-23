#include "stdafx.h"
#include "introScene.h"

HRESULT introScene::init(void)
{
	//Ÿ�̸ӿ� ī��Ʈ�� 0���� �ʱ�ȭ
	_timer = 0;
	_count = 0;

	//�� ��Ʈ�� �̹����� ������ŭ �ݺ����� ����
	for (int i = 0; i < MAX_INTRO_SIZE; i++)
	{
		//�̹����� Ű�� �ʱ�ȭ
		char strKey[128] = { 0 };
		sprintf(strKey, "intro%d", i);
		_strKeyList.push_back(strKey);	//�ʱ�ȭ�� �̹����� Ű ���� ����

										//���� �̸� �ʱ�ȭ
		char filePath[128] = { 0 };
		sprintf(filePath, "image/intro/intro%d.bmp", i);

		//�̹����� �ε��Ŵ
		IMAGEMANAGER->addImage(strKey, filePath, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	}

	return S_OK;
}

void introScene::release(void)
{
}

void introScene::update(void)
{
	//Ÿ�̸� ����
	_timer++;
	if (_timer % 5 == 0)
	{
		//ī��Ʈ�� ����
		_count++;
		if (_count > MAX_INTRO_SIZE - 1)
		{
			//�Ѿ
			SCENEMANAGER->changeScene("�ε�ȭ��");
		}
		//Ÿ�̸� �ʱ�ȭ
		_timer = 0;
	}

	//��ũ��
	if (KEYMANAGER->isOnceKeyDown('Y'))
	{
		SCENEMANAGER->changeScene("�ε�ȭ��");
	}
}

void introScene::render(void)
{
	//�̹����� Ű���� ã�Ƽ� ������ ��Ŵ
	IMAGEMANAGER->findImage(_strKeyList[_count])->render(getMemDC());
}