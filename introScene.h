#pragma once
#include "gameNode.h"
#define MAX_INTRO_SIZE 140

class introScene : public gameNode
{
private:
	int _timer;	// �ð�
	int _count;	// �� ��° �׸��� �׸� ������

private:
	vector<string> _strKeyList; //�̹����� Ű ������ ������ ����

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	introScene() {}
	~introScene() {}
};

