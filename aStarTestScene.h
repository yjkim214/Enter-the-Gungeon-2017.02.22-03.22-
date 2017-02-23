#pragma once
#include "gameNode.h"
#include "aStarTest.h"

class aStarTestScene : public gameNode
{
private:
	aStarTest* _aStar; //���̽�Ÿ Ŭ����

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	aStarTestScene() {}
	~aStarTestScene() {}
};

