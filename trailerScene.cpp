#include "stdafx.h"
#include "trailerScene.h"

HRESULT trailerScene::init(void)
{
	MOVIEMANAGER->play("movie/trailer/trailer.wmv");
	return S_OK;
}

void trailerScene::release(void)
{

}

void trailerScene::update(void)
{
}

void trailerScene::render(void)
{

}