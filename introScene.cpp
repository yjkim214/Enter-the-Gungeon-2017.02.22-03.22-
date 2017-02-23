#include "stdafx.h"
#include "introScene.h"

HRESULT introScene::init(void)
{
	//타이머와 카운트를 0으로 초기화
	_timer = 0;
	_count = 0;

	//총 인트로 이미지의 개수만큼 반복문을 실행
	for (int i = 0; i < MAX_INTRO_SIZE; i++)
	{
		//이미지의 키값 초기화
		char strKey[128] = { 0 };
		sprintf(strKey, "intro%d", i);
		_strKeyList.push_back(strKey);	//초기화된 이미지의 키 값을 저장

										//파일 이름 초기화
		char filePath[128] = { 0 };
		sprintf(filePath, "image/intro/intro%d.bmp", i);

		//이미지를 로드시킴
		IMAGEMANAGER->addImage(strKey, filePath, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	}

	return S_OK;
}

void introScene::release(void)
{
}

void introScene::update(void)
{
	//타이머 증가
	_timer++;
	if (_timer % 5 == 0)
	{
		//카운트를 증가
		_count++;
		if (_count > MAX_INTRO_SIZE - 1)
		{
			//넘어감
			SCENEMANAGER->changeScene("로딩화면");
		}
		//타이머 초기화
		_timer = 0;
	}

	//매크로
	if (KEYMANAGER->isOnceKeyDown('Y'))
	{
		SCENEMANAGER->changeScene("로딩화면");
	}
}

void introScene::render(void)
{
	//이미지의 키값을 찾아서 랜더를 시킴
	IMAGEMANAGER->findImage(_strKeyList[_count])->render(getMemDC());
}