#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init(void)
{
	//로딩클래스 생성 및 초기화
	_loading = new loading;
	_loading->init();

	//이미지 및 사운드 로딩
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release(void)
{
	//로딩클래스 해제
	SAFE_DELETE(_loading);
}

void loadingScene::update(void)
{
	//로딩클래스 업데이트
	_loading->update();

	if (_loading->loadingDone())
	{
		//로딩이 완료 됐으니 씬변경
		SCENEMANAGER->changeScene("트레일러화면");
	}
}

void loadingScene::render(void)
{
	//로딩클래스 렌더
	_loading->render();
}

//로딩이미지 함수(이곳에 이미지를 전부 넣어라)
void loadingScene::loadingImage(void)
{
	//_loading->loadImage();
	//_loading->loadFrameImage();

	//로딩이 너무 빠르게 진행되서 천천히 돌아가도록 테스트용으로 만들어 놓자
	
	//백그라운드 이미지
	//_loading->loadImage("백그라운드", "background.bmp", WINSIZEX, WINSIZEY);

	//메뉴 씬에서 사용될 이미지
	_loading->loadFrameImage("bgMenuAnim", "image/menu/bgMenuAnim.bmp", 6480, 675, 6, 1, true, RGB(255, 0, 255));
}
//로딩사운드 함수(이곳에 사운드를 전부 넣어라)
void loadingScene::loadingSound(void)
{
	//_loading->loadSound("사운드1", "Sleep Away.mp3");
	//_loading->loadSound("사운드2", "Kalimba.mp3");
}
