#include "stdafx.h"
#include "aStarTest.h"

HRESULT aStarTest::init(void)
{
	//타일 셋팅하기
	setTiles();

	_count = 0;
	_isStart = false;

	return S_OK;
}

void aStarTest::release(void)
{
}

void aStarTest::update(void)
{
	//S키 누르면 시작한다
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_isStart = true;

		//길찾기 함수
		pathFinder(_currentTile);
	}

	//길찾기를 카운터에 따라 조금씩 보여주기
	if (_isStart)
	{
		_count++;
		if (_count % 20 == 0)
		{
			_count = 0;
			//길찾기 함수
			pathFinder(_currentTile);
		}
	}

	//장애물 세팅하기
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _vTotalList.size(); i++)
		{
			if (PtInRect(&_vTotalList[i]->getRect(), _ptMouse))
			{
				//시작, 종료타일은 건너뛰고 장애물을 세팅하기
				if (_vTotalList[i]->getAttribute() == "start") continue;
				if (_vTotalList[i]->getAttribute() == "end") continue;

				_vTotalList[i]->setIsOpen(false);
				_vTotalList[i]->setAttribute("wall");
				_vTotalList[i]->setColor(RGB(230, 140, 200));
				break;
			}
		}
	}
}

void aStarTest::render(void)
{
	//타일 전체 렌더
	for (int i = 0; i < _vTotalList.size(); i++)
	{
		_vTotalList[i]->render();
	}
}

//타일 셋팅하기
void aStarTest::setTiles(void)
{
	//시작타일 초기화
	_startTile = new tile;
	_startTile->init(4, 12);			//시작 좌표위치 X 4 y 12
	_startTile->setAttribute("start");

	//종료타일 초기화
	_endTile = new tile;
	_endTile->init(20, 12);
	_endTile->setAttribute("end");		//종료 좌표위치 x 20, y 12

										//현재 타일을 시작타일로 설정
	_currentTile = _startTile;

	//타일 초기화
	for (int i = 0; i < TILENUMY; i++)
	{
		for (int j = 0; j < TILENUMX; j++)
		{
			//시작타일
			if (j == _startTile->getIdX() && i == _startTile->getIdY())
			{
				_startTile->setColor(RGB(0, 255, 255));
				_vTotalList.push_back(_startTile);
				continue;
			}

			//종료타일
			if (j == _endTile->getIdX() && i == _endTile->getIdY())
			{
				_endTile->setColor(RGB(10, 120, 55));
				_vTotalList.push_back(_endTile);
				continue;
			}

			//타일을 새로 생성해서 전체타일벡터에 넣어두기
			tile* node = new tile;
			node->init(j, i);
			_vTotalList.push_back(node);
		}
	}
}

//넓이 우선 탐색을 활용해 가야할 타일을 찾아서 벡터로 반환해줄 함쑤
vector<tile*> aStarTest::addOpenList(tile* currentTile)
{
	int startX = currentTile->getIdX() - 1;
	int startY = currentTile->getIdY() - 1;

	//현재 노드에서 주변을 확장하며 검사
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			tile* node = _vTotalList[(startY * TILENUMX) + startX + j + (i * TILENUMX)];
			if (!node->getIsOpen()) continue;
			if (node->getAttribute() == "start") continue;
			if (node->getAttribute() == "wall") continue;

			node->setParentNode(_currentTile);

			bool addObj = true;

			//갈쑤 있는 길은 모두 오픈리스트에 넣어준다
			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				if (*_viOpenList == node)
				{
					addObj = false;
					break;
				}
			}

			//검색할 타일의 색상을 바꾼다
			if (node->getAttribute() != "end") node->setColor(RGB(128, 64, 28));

			if (!addObj) continue;
			_vOpenList.push_back(node);
		}
	}

	return _vOpenList;
}

//길찾기 함쑤
void aStarTest::pathFinder(tile* currentTile)
{
	//비용거리를 비교할 대상이 필요(토탈코스트가 적으면 길찾는도중 뻥난다)
	float tempTotalCost = 10000;
	tile* tempTile;

	for (int i = 0; i < addOpenList(currentTile).size(); i++)
	{
		//현재 노드부터 끝점까지의 경로 비용
		_vOpenList[i]->setCostToGoal((abs(_endTile->getIdX() - _vOpenList[i]->getIdX()) +
			abs(_endTile->getIdY() - _vOpenList[i]->getIdY())) * 10);

		//시작점부터 현재 노드까지의 경로 비용
		POINT center1 = _vOpenList[i]->getParentNode()->getCenter();
		POINT center2 = _vOpenList[i]->getCenter();
		_vOpenList[i]->setCostFromStart((getDistance(center1.x, center1.y, center2.x, center2.y) > TILEWIDTH) ? 14 : 10);

		//총 비용 계솬
		_vOpenList[i]->setTotalCost(_vOpenList[i]->getCostToGoal() +
			_vOpenList[i]->getCostFromStart());

		//가장 저렴한 비용 색출
		if (tempTotalCost > _vOpenList[i]->getTotalCost())
		{
			tempTotalCost = _vOpenList[i]->getTotalCost();
			tempTile = _vOpenList[i];
		}

		//갈수 있는 길은 또 모두 오픈리스트에 담아준돠
		bool addObj = true;
		for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		{
			if (*_viOpenList == tempTile)
			{
				addObj = false;
				break;
			}
		}

		_vOpenList[i]->setIsOpen(false);
		if (!addObj) continue;
		_vOpenList.push_back(tempTile);
	}

	//목적지에 다 왔다! 그럼 리턴!
	if (tempTile->getAttribute() == "end")
	{
		while (_currentTile->getParentNode() != NULL)
		{
			_currentTile->setColor(RGB(22, 14, 128));
			_currentTile = _currentTile->getParentNode();
		}

		return;
	}

	//현재 타일(지나온 곳)은 클로즈 리스트에 넣어준다
	_vCloseList.push_back(tempTile);

	//다음 노드로 설정된 타일을 오픈리스트에서 또 제거해준다
	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	{
		if (*_viOpenList == tempTile)
		{
			_viOpenList = _vOpenList.erase(_viOpenList);
			break;
		}
	}

	//템프 타일을 현재 타일에 넣는다!(제일 가까운 길로 선정된 타일이니까 == 이동해야지)
	_currentTile = tempTile;

	//재귀재귀재귀
	//pathFinder(_currentTile);
}