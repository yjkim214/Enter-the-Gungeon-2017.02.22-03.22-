#pragma once
#include "gameNode.h"
#define MAX_INTRO_SIZE 140

class introScene : public gameNode
{
private:
	int _timer;	// 시간
	int _count;	// 몇 번째 그림을 그릴 것인지

private:
	vector<string> _strKeyList; //이미지의 키 값들을 가지고 있음

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	introScene() {}
	~introScene() {}
};

