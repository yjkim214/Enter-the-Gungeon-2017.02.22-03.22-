#include "stdafx.h"
#include "tankGameScene.h"

HRESULT tankGameScene::init(void)
{
	//타일이미지
	IMAGEMANAGER->addFrameImage("tilemap", "tilemap.bmp", 640, 256, 20, 8);

	//탱크맵 클래스 생성
	_tankMap = new tankMap;
	_tankMap->init();

	//탱크 클래스 생성
	_tank = new tank;
	_tank->init();
	_tank->setTankMapLink(_tankMap);
	_tank->setTankPosition(0);

	return S_OK;
}

void tankGameScene::release(void)
{
	SAFE_DELETE(_tankMap);
	SAFE_DELETE(_tank);
}

void tankGameScene::update(void)
{
	_tankMap->update();
	_tank->update();
}

void tankGameScene::render(void)
{
	_tankMap->render();
	_tank->render();
}
