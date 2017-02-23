#include "stdafx.h"
#include "menuScene.h"

HRESULT menuScene::init(void)
{
	_bgMenuImg = IMAGEMANAGER->findImage("bgMenuAnim");
	_timer = 0;
	_currentFrameX = 0;


	return S_OK;
}

void menuScene::release(void)
{
}

void menuScene::update(void)
{
	_timer++;
	if (_timer % 10 == 0)
	{
		_currentFrameX++;
		if (_currentFrameX > _bgMenuImg->getMaxFrameX())
		{
			_currentFrameX = 0;
		}
		_timer = 0;
	}
}

void menuScene::render(void)
{
	_bgMenuImg->frameRender(getMemDC(), 0, 0, _currentFrameX, 0);
}