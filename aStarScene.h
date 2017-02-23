#pragma once
#include "gameNode.h"
#include "aStar.h"

class aStarScene : public gameNode
{
private:
	aStar* _aStar; //에이스타 클래스

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	aStarScene() {}
	~aStarScene() {}
};

