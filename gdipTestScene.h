#pragma once
#include "gameNode.h"

class gdipTestScene : public gameNode
{
public:
	HRESULT init();
	void release();
	void update();
	void render();

	gdipTestScene() {}
	~gdipTestScene() {}
};

