#pragma once
#include "gameNode.h"
class trailerScene : public gameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	trailerScene() {}
	~trailerScene() {}
};