#pragma once
#include "gameNode.h"
#include "aStar.h"

class aStarScene : public gameNode
{
private:
	aStar* _aStar; //���̽�Ÿ Ŭ����

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	aStarScene() {}
	~aStarScene() {}
};

