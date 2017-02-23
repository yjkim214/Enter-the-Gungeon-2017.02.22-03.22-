#include "stdafx.h"
#include "aStarTest.h"

HRESULT aStarTest::init(void)
{
	//Ÿ�� �����ϱ�
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
	//SŰ ������ �����Ѵ�
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_isStart = true;

		//��ã�� �Լ�
		pathFinder(_currentTile);
	}

	//��ã�⸦ ī���Ϳ� ���� ���ݾ� �����ֱ�
	if (_isStart)
	{
		_count++;
		if (_count % 20 == 0)
		{
			_count = 0;
			//��ã�� �Լ�
			pathFinder(_currentTile);
		}
	}

	//��ֹ� �����ϱ�
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _vTotalList.size(); i++)
		{
			if (PtInRect(&_vTotalList[i]->getRect(), _ptMouse))
			{
				//����, ����Ÿ���� �ǳʶٰ� ��ֹ��� �����ϱ�
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
	//Ÿ�� ��ü ����
	for (int i = 0; i < _vTotalList.size(); i++)
	{
		_vTotalList[i]->render();
	}
}

//Ÿ�� �����ϱ�
void aStarTest::setTiles(void)
{
	//����Ÿ�� �ʱ�ȭ
	_startTile = new tile;
	_startTile->init(4, 12);			//���� ��ǥ��ġ X 4 y 12
	_startTile->setAttribute("start");

	//����Ÿ�� �ʱ�ȭ
	_endTile = new tile;
	_endTile->init(20, 12);
	_endTile->setAttribute("end");		//���� ��ǥ��ġ x 20, y 12

										//���� Ÿ���� ����Ÿ�Ϸ� ����
	_currentTile = _startTile;

	//Ÿ�� �ʱ�ȭ
	for (int i = 0; i < TILENUMY; i++)
	{
		for (int j = 0; j < TILENUMX; j++)
		{
			//����Ÿ��
			if (j == _startTile->getIdX() && i == _startTile->getIdY())
			{
				_startTile->setColor(RGB(0, 255, 255));
				_vTotalList.push_back(_startTile);
				continue;
			}

			//����Ÿ��
			if (j == _endTile->getIdX() && i == _endTile->getIdY())
			{
				_endTile->setColor(RGB(10, 120, 55));
				_vTotalList.push_back(_endTile);
				continue;
			}

			//Ÿ���� ���� �����ؼ� ��üŸ�Ϻ��Ϳ� �־�α�
			tile* node = new tile;
			node->init(j, i);
			_vTotalList.push_back(node);
		}
	}
}

//���� �켱 Ž���� Ȱ���� ������ Ÿ���� ã�Ƽ� ���ͷ� ��ȯ���� �Ծ�
vector<tile*> aStarTest::addOpenList(tile* currentTile)
{
	int startX = currentTile->getIdX() - 1;
	int startY = currentTile->getIdY() - 1;

	//���� ��忡�� �ֺ��� Ȯ���ϸ� �˻�
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

			//���� �ִ� ���� ��� ���¸���Ʈ�� �־��ش�
			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				if (*_viOpenList == node)
				{
					addObj = false;
					break;
				}
			}

			//�˻��� Ÿ���� ������ �ٲ۴�
			if (node->getAttribute() != "end") node->setColor(RGB(128, 64, 28));

			if (!addObj) continue;
			_vOpenList.push_back(node);
		}
	}

	return _vOpenList;
}

//��ã�� �Ծ�
void aStarTest::pathFinder(tile* currentTile)
{
	//���Ÿ��� ���� ����� �ʿ�(��Ż�ڽ�Ʈ�� ������ ��ã�µ��� ������)
	float tempTotalCost = 10000;
	tile* tempTile;

	for (int i = 0; i < addOpenList(currentTile).size(); i++)
	{
		//���� ������ ���������� ��� ���
		_vOpenList[i]->setCostToGoal((abs(_endTile->getIdX() - _vOpenList[i]->getIdX()) +
			abs(_endTile->getIdY() - _vOpenList[i]->getIdY())) * 10);

		//���������� ���� �������� ��� ���
		POINT center1 = _vOpenList[i]->getParentNode()->getCenter();
		POINT center2 = _vOpenList[i]->getCenter();
		_vOpenList[i]->setCostFromStart((getDistance(center1.x, center1.y, center2.x, center2.y) > TILEWIDTH) ? 14 : 10);

		//�� ��� ���
		_vOpenList[i]->setTotalCost(_vOpenList[i]->getCostToGoal() +
			_vOpenList[i]->getCostFromStart());

		//���� ������ ��� ����
		if (tempTotalCost > _vOpenList[i]->getTotalCost())
		{
			tempTotalCost = _vOpenList[i]->getTotalCost();
			tempTile = _vOpenList[i];
		}

		//���� �ִ� ���� �� ��� ���¸���Ʈ�� ����ص�
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

	//�������� �� �Դ�! �׷� ����!
	if (tempTile->getAttribute() == "end")
	{
		while (_currentTile->getParentNode() != NULL)
		{
			_currentTile->setColor(RGB(22, 14, 128));
			_currentTile = _currentTile->getParentNode();
		}

		return;
	}

	//���� Ÿ��(������ ��)�� Ŭ���� ����Ʈ�� �־��ش�
	_vCloseList.push_back(tempTile);

	//���� ���� ������ Ÿ���� ���¸���Ʈ���� �� �������ش�
	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	{
		if (*_viOpenList == tempTile)
		{
			_viOpenList = _vOpenList.erase(_viOpenList);
			break;
		}
	}

	//���� Ÿ���� ���� Ÿ�Ͽ� �ִ´�!(���� ����� ��� ������ Ÿ���̴ϱ� == �̵��ؾ���)
	_currentTile = tempTile;

	//���������
	//pathFinder(_currentTile);
}