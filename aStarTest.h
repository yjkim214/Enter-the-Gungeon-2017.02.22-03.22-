#pragma once
#include "gameNode.h"
#include "tile.h"

#define TILEWIDTH 32
#define TILEHEIGHT 32

#define TILENUMX ((int)(WINSIZEX / TILEWIDTH))
#define TILENUMY ((int)(WINSIZEY / TILEHEIGHT))

class aStarTest : public gameNode
{
private:
	//��üŸ�Ϻ���
	vector<tile*> _vTotalList;
	vector<tile*>::iterator _viTotalList;

	//�����ִ±� �־�� ����
	vector<tile*> _vOpenList;
	vector<tile*>::iterator _viOpenList;

	//�����±� �־�� ����
	vector<tile*> _vCloseList;
	vector<tile*>::iterator _viCloseList;

	tile* _startTile;		//����Ÿ��
	tile* _endTile;			//����Ÿ��
	tile* _currentTile; 	//����Ÿ��

	bool _isStart;
	int _count;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//Ÿ�� �����ϱ�
	void setTiles(void);

	//��ã�� �Լ�
	void pathFinder(tile* currentTile);

	//���� �켱 Ž���� Ȱ���ؼ� ������ Ÿ���� ã�Ƽ� ���ͷ� ��ȯ���� �Ծ�
	vector<tile*> addOpenList(tile* currentTile);

	aStarTest() {}
	~aStarTest() {}
};