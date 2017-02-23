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
	//전체타일벡터
	vector<tile*> _vTotalList;
	vector<tile*>::iterator _viTotalList;

	//갈수있는길 넣어둘 벡터
	vector<tile*> _vOpenList;
	vector<tile*>::iterator _viOpenList;

	//못가는길 넣어둘 벡터
	vector<tile*> _vCloseList;
	vector<tile*>::iterator _viCloseList;

	tile* _startTile;		//시작타일
	tile* _endTile;			//종료타일
	tile* _currentTile; 	//현재타일

	bool _isStart;
	int _count;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//타일 셋팅하기
	void setTiles(void);

	//길찾기 함수
	void pathFinder(tile* currentTile);

	//넓이 우선 탐색을 활용해서 가야할 타일을 찾아서 벡터로 반환해줄 함쑤
	vector<tile*> addOpenList(tile* currentTile);

	aStarTest() {}
	~aStarTest() {}
};