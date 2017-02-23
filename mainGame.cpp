#include "stdafx.h"
#include "mainGame.h"
//=============================================================
//	## init(void) ## �ʱ�ȭ
//=============================================================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	
	//������ ���ΰ��� Ŭ���� �ȿ����� ���鸸 �����Ѵ�
	//�׸��� ������ ������ ���ΰ��ӿ����� �ϸ� �ȴ�
	/*���߰�*/
	SCENEMANAGER->addScene("���׽�Ʈ", new sceneTest);
	SCENEMANAGER->addScene("�ȼ��浹", new pixelCollision);
	SCENEMANAGER->addScene("ini", new iniTestScene);
	SCENEMANAGER->addScene("����", new soundTestScene);
	//SCENEMANAGER->addScene("��ũ����", new tankGameScene);
	//SCENEMANAGER->addScene("����", new maptoolScene);
	SCENEMANAGER->addScene("���̼Ҹ�Ʈ��", new isometricScene);
	SCENEMANAGER->addScene("���̼�", new isometric);
	SCENEMANAGER->addScene("���̽�Ÿ����", new aStarTestScene);
	//���̽�Ÿ���� => ȭ��ũ�⸦ 1200 * 1000���� �����ϱ�
	SCENEMANAGER->addScene("���̽�Ÿ����", new aStarScene);
	SCENEMANAGER->addScene("GDIPLUS", new gdipTestScene);

	//Enter the Gungeon Scene
	SCENEMANAGER->addScene("��Ʈ��ȭ��", new introScene);
	SCENEMANAGER->addScene("�ε�ȭ��", new loadingScene);
	SCENEMANAGER->addScene("Ʈ���Ϸ�ȭ��", new trailerScene);
	SCENEMANAGER->addScene("�޴�ȭ��", new menuScene);

	/*����� ����*/
	SCENEMANAGER->changeScene("��Ʈ��ȭ��");

	return S_OK;
}
//=============================================================
//	## release(void) ## ����
//=============================================================
void mainGame::release(void)
{
	gameNode::release();
}
//=============================================================
//	## update(void) ## ������Ʈ
//=============================================================
void mainGame::update(void)
{
	gameNode::update();

	//���Ŵ��� ������Ʈ
	SCENEMANAGER->update();
	SOUNDMANAGER->update();
}
//=============================================================
//	## render(void) ## ����
//=============================================================
void mainGame::render(void)
{
	//��� �� ��Ʈ�� (������ �׳� �״�� �Ѱ�!!)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
//=============================================================
	
	//���Ŵ��� ����
	SCENEMANAGER->render();

	//Ÿ�ӸŴ��� ����
	TIMEMANAGER->render(getMemDC());

//=============================================================
	//������� ������ HDC�� �׸��� (������ �״�� �Ѱ�!!)
	this->getBackBuffer()->render(getHDC());
}