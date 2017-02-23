#pragma once
#include "gameNode.h"

class menuScene : public gameNode
{
private:
	image* _bgMenuImg;
	int _timer;
	int _currentFrameX;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	menuScene() {}
	~menuScene() {}
};