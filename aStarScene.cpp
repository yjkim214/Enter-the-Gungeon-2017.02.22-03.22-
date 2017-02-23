#include "stdafx.h"
#include "aStarScene.h"


HRESULT aStarScene::init(void)
{
	IMAGEMANAGER->addImage("1", "1.bmp", 32, 32, true, RGB(255, 0, 255));

	//에이스타 클래스 초기화
	_aStar = new aStar;
	_aStar->init();

	return S_OK;
}

void aStarScene::release(void)
{
	//에이스타 클래스 해제
	SAFE_DELETE(_aStar);
}

void aStarScene::update(void)
{
	//에이스타 클래스 업데이트
	_aStar->update();
}

void aStarScene::render(void)
{
	//에이스타 클래스 렌더
	_aStar->render();
}
