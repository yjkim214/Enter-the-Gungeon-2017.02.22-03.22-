#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init(void)
{
	//�ε�Ŭ���� ���� �� �ʱ�ȭ
	_loading = new loading;
	_loading->init();

	//�̹��� �� ���� �ε�
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release(void)
{
	//�ε�Ŭ���� ����
	SAFE_DELETE(_loading);
}

void loadingScene::update(void)
{
	//�ε�Ŭ���� ������Ʈ
	_loading->update();

	if (_loading->loadingDone())
	{
		//�ε��� �Ϸ� ������ ������
		SCENEMANAGER->changeScene("Ʈ���Ϸ�ȭ��");
	}
}

void loadingScene::render(void)
{
	//�ε�Ŭ���� ����
	_loading->render();
}

//�ε��̹��� �Լ�(�̰��� �̹����� ���� �־��)
void loadingScene::loadingImage(void)
{
	//_loading->loadImage();
	//_loading->loadFrameImage();

	//�ε��� �ʹ� ������ ����Ǽ� õõ�� ���ư����� �׽�Ʈ������ ����� ����
	
	//��׶��� �̹���
	//_loading->loadImage("��׶���", "background.bmp", WINSIZEX, WINSIZEY);

	//�޴� ������ ���� �̹���
	_loading->loadFrameImage("bgMenuAnim", "image/menu/bgMenuAnim.bmp", 6480, 675, 6, 1, true, RGB(255, 0, 255));
}
//�ε����� �Լ�(�̰��� ���带 ���� �־��)
void loadingScene::loadingSound(void)
{
	//_loading->loadSound("����1", "Sleep Away.mp3");
	//_loading->loadSound("����2", "Kalimba.mp3");
}
