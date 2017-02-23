#include "stdafx.h"
#include "aStarTestScene.h"

HRESULT aStarTestScene::init(void)
{
	//에이스타 클래스 초기화
	_aStar = new aStarTest;
	_aStar->init();

	return S_OK;
}

void aStarTestScene::release(void)
{
	//에이스타 클래스 해제
	SAFE_DELETE(_aStar);
}

void aStarTestScene::update(void)
{
	//에이스타 클래스 업데이트
	_aStar->update();
}

void aStarTestScene::render(void)
{
	//에이스타 클래스 렌더
	_aStar->render();
}
