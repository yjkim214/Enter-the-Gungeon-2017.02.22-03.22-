#include "stdafx.h"
#include "aStar.h"

HRESULT aStar::init(void)
{
	this->tileSetting();		//Tile setup and initialization
	this->plInit();				//Player initialization
	return S_OK;
}

void aStar::release()
{
	//Release all dynamically allocated tiles
	for (int y = 0; y < TILENUMY; y++)
	{
		for (int x = 0; x < TILENUMX; x++)
		{
			delete _tile[y][x];
		}
	}
}

void aStar::update(void)
{
	this->astarReset();					//Restart astar

	if (astarState == ASTAR_UNPREPARE)	//If the astar is not ready
	{
		this->selectMouseState();		//Mouse state settings
		this->tileClick();				//Tile click (set)
		this->astarStart();				//Astar start
		this->plPosInit();				//Player positioning
	}

	this->plMove();						//Player movement processing

	if (astarState == ASTAR_UNPREPARE ||		//The astar is not ready
		astarState == ASTAR_FOUND ||			//Found the way.
		astarState == ASTAR_NOWAY)				//Without a way
		return;									//Just get out of the update function

	this->openListCheck();		//Openlist calculate
	this->calculateH();			//Openlist H value calculate
	this->calculateF();			//Openlist F value calculate
	this->closeListCheck();		//Closedlist calculate
	this->arriveCheck();		//Arrival?
}

void aStar::render(void)
{
	this->textPrint();			//Text print

	for (int i = 0; i < TILENUMY; i++)
	{
		for (int j = 0; j < TILENUMX; j++)
		{
			_tile[i][j]->render();
		}
	}

	if (_isStartSetting)
		IMAGEMANAGER->findImage("1")->render(getMemDC(), px, py);
}

void aStar::tileSetting()
{
	//Dynamic allocation of tiles
	_tile.assign(TILENUMY, vector<aTile*>(TILENUMX));

	for (int y = 0; y < TILENUMY; y++)
	{
		for (int x = 0; x < TILENUMX; x++)
		{
			_tile[y][x] = new aTile;
			_tile[y][x]->init(x, y, TILEWIDTH, TILEHEIGHT);
		}
	}

	_isStartSetting = false;		//Start position setting : false
	_isEndSetting = false;			//Target position setting : false

	LastIdX = 0;					//Closed list last index x = 0
	LastIdY = 0;					//Closed list last index y = 0
	LastG = 0;						//Closed list G value = 0

	_startX = 0, _startY = 0;		//Start location index = 0
	_endX = 0, _endY = 0;			//Target location index = 0

	astarState = ASTAR_UNPREPARE;	//Set astar state not ready
}

void aStar::openListCheck()
{
	LastIdX = _closeList[_lastIndex]->getIdX();     //The last added closed list x
	LastIdY = _closeList[_lastIndex]->getIdY();     //The last added closed list y
	LastG = _closeList[_lastIndex]->getG();         //The last added closed list G

													//If it is not the 0th line, calculate the top line
	if (LastIdY != 0)
	{
		//Top
		if (_tile[LastIdY - 1][LastIdX]->getIsOpen())	//If the tile can be passed
		{
			//If the tile has not been added to the open list
			if (!_tile[LastIdY - 1][LastIdX]->getIsListOn())
			{
				_tile[LastIdY - 1][LastIdX]->setIsListOn(true);
				_tile[LastIdY - 1][LastIdX]->setColor(RGB(128, 64, 28));
				_tile[LastIdY - 1][LastIdX]->setG(LastG + BEELINE);
				_tile[LastIdY - 1][LastIdX]->setParentNode(_closeList[_lastIndex]);
				_openList.push_back(_tile[LastIdY - 1][LastIdX]);
			}
			else //If the tile already exists in the open list
			{
				//If the newly calculated G value is smaller than the existing G value
				if (LastG + BEELINE < _tile[LastIdY - 1][LastIdX]->getG())
				{
					_tile[LastIdY - 1][LastIdX]->setG(LastG + BEELINE);					//Calculate new G value
					_tile[LastIdY - 1][LastIdX]->setParentNode(_closeList[_lastIndex]);	//Reset tile parent to last added tile in closed list
				}
			}
		}

		//Top left
		if (LastIdX != 0)
		{
			if (_tile[LastIdY - 1][LastIdX - 1]->getIsOpen() && _tile[LastIdY][LastIdX - 1]->getIsOpen() && _tile[LastIdY - 1][LastIdX]->getIsOpen())
			{
				if (!_tile[LastIdY - 1][LastIdX - 1]->getIsListOn())
				{
					_tile[LastIdY - 1][LastIdX - 1]->setIsListOn(true);
					_tile[LastIdY - 1][LastIdX - 1]->setColor(RGB(128, 64, 28));
					_tile[LastIdY - 1][LastIdX - 1]->setG(LastG + SLASH);
					_tile[LastIdY - 1][LastIdX - 1]->setParentNode(_closeList[_lastIndex]);
					_openList.push_back(_tile[LastIdY - 1][LastIdX - 1]);
				}
				else
				{
					if (LastG + SLASH < _tile[LastIdY - 1][LastIdX - 1]->getG())
					{
						_tile[LastIdY - 1][LastIdX - 1]->setG(LastG + SLASH);
						_tile[LastIdY - 1][LastIdX - 1]->setParentNode(_closeList[_lastIndex]);
					}
				}
			}
		}

		//Top right
		if (LastIdX != TILENUMX - 1)
		{
			if (_tile[LastIdY - 1][LastIdX + 1]->getIsOpen() && _tile[LastIdY][LastIdX + 1]->getIsOpen() && _tile[LastIdY - 1][LastIdX]->getIsOpen())
			{
				if (!_tile[LastIdY - 1][LastIdX + 1]->getIsListOn())
				{
					_tile[LastIdY - 1][LastIdX + 1]->setIsListOn(true);
					_tile[LastIdY - 1][LastIdX + 1]->setColor(RGB(128, 64, 28));
					_tile[LastIdY - 1][LastIdX + 1]->setG(LastG + SLASH);
					_tile[LastIdY - 1][LastIdX + 1]->setParentNode(_closeList[_lastIndex]);
					_openList.push_back(_tile[LastIdY - 1][LastIdX + 1]);
				}
				else
				{
					if (LastG + SLASH < _tile[LastIdY - 1][LastIdX + 1]->getG())
					{
						_tile[LastIdY - 1][LastIdX + 1]->setG(LastG + SLASH);
						_tile[LastIdY - 1][LastIdX + 1]->setParentNode(_closeList[_lastIndex]);
					}
				}
			}
		}
	}

	//If not the last line, calculate the bottom line
	if (LastIdY != TILENUMY - 1)
	{
		//Bottom
		if (_tile[LastIdY + 1][LastIdX]->getIsOpen())
		{
			if (!_tile[LastIdY + 1][LastIdX]->getIsListOn())
			{
				_tile[LastIdY + 1][LastIdX]->setIsListOn(true);
				_tile[LastIdY + 1][LastIdX]->setColor(RGB(128, 64, 28));
				_tile[LastIdY + 1][LastIdX]->setG(LastG + BEELINE);
				_tile[LastIdY + 1][LastIdX]->setParentNode(_closeList[_lastIndex]);
				_openList.push_back(_tile[LastIdY + 1][LastIdX]);
			}
			else
			{
				if (LastG + BEELINE < _tile[LastIdY + 1][LastIdX]->getG())
				{
					_tile[LastIdY + 1][LastIdX]->setG(LastG + BEELINE);
					_tile[LastIdY + 1][LastIdX]->setParentNode(_closeList[_lastIndex]);
				}
			}
		}

		//Bottom left
		if (LastIdX != 0)
		{
			if (_tile[LastIdY + 1][LastIdX - 1]->getIsOpen() && _tile[LastIdY + 1][LastIdX]->getIsOpen() && _tile[LastIdY][LastIdX - 1]->getIsOpen())
			{
				if (!_tile[LastIdY + 1][LastIdX - 1]->getIsListOn())
				{
					_tile[LastIdY + 1][LastIdX - 1]->setIsListOn(true);
					_tile[LastIdY + 1][LastIdX - 1]->setColor(RGB(128, 64, 28));
					_tile[LastIdY + 1][LastIdX - 1]->setG(LastG + SLASH);
					_tile[LastIdY + 1][LastIdX - 1]->setParentNode(_closeList[_lastIndex]);
					_openList.push_back(_tile[LastIdY + 1][LastIdX - 1]);
				}
				else
				{
					if (LastG + SLASH < _tile[LastIdY + 1][LastIdX - 1]->getG())
					{
						_tile[LastIdY + 1][LastIdX - 1]->setG(LastG + SLASH);
						_tile[LastIdY + 1][LastIdX - 1]->setParentNode(_closeList[_lastIndex]);
					}
				}
			}
		}

		//Bottom right
		if (LastIdX != TILENUMX - 1)
		{
			if (_tile[LastIdY + 1][LastIdX + 1]->getIsOpen() && _tile[LastIdY + 1][LastIdX]->getIsOpen() && _tile[LastIdY][LastIdX + 1]->getIsOpen())
			{
				if (!_tile[LastIdY + 1][LastIdX + 1]->getIsListOn())
				{
					_tile[LastIdY + 1][LastIdX + 1]->setIsListOn(true);
					_tile[LastIdY + 1][LastIdX + 1]->setColor(RGB(128, 64, 28));
					_tile[LastIdY + 1][LastIdX + 1]->setG(LastG + SLASH);
					_tile[LastIdY + 1][LastIdX + 1]->setParentNode(_closeList[_lastIndex]);
					_openList.push_back(_tile[LastIdY + 1][LastIdX + 1]);
				}
				else
				{
					if (LastG + SLASH < _tile[LastIdY + 1][LastIdX + 1]->getG())
					{
						_tile[LastIdY + 1][LastIdX + 1]->setG(LastG + SLASH);
						_tile[LastIdY + 1][LastIdX + 1]->setParentNode(_closeList[_lastIndex]);
					}
				}
			}
		}
	}

	//Left
	if (LastIdX != 0)
	{
		if (_tile[LastIdY][LastIdX - 1]->getIsOpen())
		{
			if (!_tile[LastIdY][LastIdX - 1]->getIsListOn())
			{
				_tile[LastIdY][LastIdX - 1]->setIsListOn(true);
				_tile[LastIdY][LastIdX - 1]->setColor(RGB(128, 64, 28));
				_tile[LastIdY][LastIdX - 1]->setG(LastG + BEELINE);
				_tile[LastIdY][LastIdX - 1]->setParentNode(_closeList[_lastIndex]);
				_openList.push_back(_tile[LastIdY][LastIdX - 1]);
			}
			else
			{
				if (LastG + BEELINE < _tile[LastIdY][LastIdX - 1]->getG())
				{
					_tile[LastIdY][LastIdX - 1]->setG(LastG + BEELINE);
					_tile[LastIdY][LastIdX - 1]->setParentNode(_closeList[_lastIndex]);
				}
			}
		}
	}

	//Right
	if (LastIdX != TILENUMX - 1)
	{
		if (_tile[LastIdY][LastIdX + 1]->getIsOpen())
		{
			if (!_tile[LastIdY][LastIdX + 1]->getIsListOn())
			{
				_tile[LastIdY][LastIdX + 1]->setIsListOn(true);
				_tile[LastIdY][LastIdX + 1]->setColor(RGB(128, 64, 28));
				_tile[LastIdY][LastIdX + 1]->setG(LastG + BEELINE);
				_tile[LastIdY][LastIdX + 1]->setParentNode(_closeList[_lastIndex]);
				_openList.push_back(_tile[LastIdY][LastIdX + 1]);
			}
			else
			{
				if (LastG + BEELINE < _tile[LastIdY][LastIdX + 1]->getG())
				{
					_tile[LastIdY][LastIdX + 1]->setG(LastG + BEELINE);
					_tile[LastIdY][LastIdX + 1]->setParentNode(_closeList[_lastIndex]);
				}
			}
		}
	}
}

void aStar::tileClick()
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < TILENUMY; i++)
		{
			for (int j = 0; j < TILENUMX; j++)
			{
				switch (mouseState)
				{
				case EMPTY:
					if (PtInRect(&_tile[i][j]->getRect(), _ptMouse))
					{
						if (_tile[i][j]->getTileState() == TILE_START)
						{
							_startX = _startY = 0;
							_isStartSetting = false;
							_closeList.clear();
							vector<aTile*>().swap(_closeList);
						}
						if (_tile[i][j]->getTileState() == TILE_END)
						{
							_endX = _endY = 0;
							_isEndSetting = false;
						}
						_tile[i][j]->setIsOpen(true);
						_tile[i][j]->setTileState(TILE_EMPTY);
						_tile[i][j]->setColor(RGB(250, 150, 0));
					}
					break;
				case START:
					if (PtInRect(&_tile[i][j]->getRect(), _ptMouse) && !_isStartSetting)
					{
						_startX = j;	//Start point x Save index
						_startY = i;	//Start point y Save index
						_tile[i][j]->setIsOpen(false);					//Can not pass
						_tile[i][j]->setIsListOn(true);					//Add to open list
						_tile[i][j]->setTileState(TILE_START);			//Set tile state to start tile
						_tile[i][j]->setColor(RGB(0, 255, 255));		//Color is light blue
						_isStartSetting = true;							//Set start location
						_closeList.push_back(_tile[i][j]);				//Add to closed list
					}
					break;
				case END:
					if (PtInRect(&_tile[i][j]->getRect(), _ptMouse) && !_isEndSetting)
					{
						_endX = j;		//Target point x Save index
						_endY = i;		//Target point y Save index
						_tile[i][j]->setIsOpen(true);					//Can pass
						_tile[i][j]->setIsListOn(false);				//Do not add to open list
						_tile[i][j]->setTileState(TILE_END);			//Set tile state to target tile
						_tile[i][j]->setColor(RGB(10, 120, 55));		//The color is dark green
						_isEndSetting = true;							//Set goal location
					}
					break;
				case WALL:
					if (PtInRect(&_tile[i][j]->getRect(), _ptMouse))
					{
						if (_tile[i][j]->getTileState() == TILE_START) continue;
						if (_tile[i][j]->getTileState() == TILE_END) continue;

						_tile[i][j]->setIsOpen(false);
						_tile[i][j]->setTileState(TILE_WALL);
						_tile[i][j]->setColor(RGB(230, 140, 200));
					}
					break;
				}
			}
		}
	}
}

void aStar::astarStart()
{
	//Start point, Destination point is installed, press space to initialize the tile
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && _isStartSetting && _isEndSetting && astarState == ASTAR_UNPREPARE)
	{
		astarState = ASTAR_SEARCHING;
		_lastIndex = 0;
	}
}


void aStar::calculateH()
{
	for (int i = 0; i < _openList.size(); i++)
	{
		int v = (_endX - _openList[i]->getIdX()) * BEELINE;
		int h = (_endY - _openList[i]->getIdY()) * BEELINE;

		_openList[i]->setH(abs(v) + abs(h));
	}
}

void aStar::calculateF()
{
	for (int i = 0; i < _openList.size(); i++)
	{	//F = G + H
		_openList[i]->setF(_openList[i]->getG() + _openList[i]->getH());
	}
}

void aStar::closeListCheck()
{
	//If the size of the openlist is zero even after searching, there is nothing to look for
	if (_openList.size() == 0)
	{
		astarState = ASTAR_NOWAY;	//There is no route
		return;						//Ignore jobs below
	}

	int index = 0;                 //The variable to hold the value of the smallest F in the open list (once set to 0)
	int lowest = BIGNUM;           //The variable to hold the smallest F value of the open list (once set to the maximum number of searches BIGNUM)
	for (int i = 0; i < _openList.size(); i++)
	{
		if (_openList[i]->getF() < lowest)
		{
			lowest = _openList[i]->getF();
			index = i;
		}
	}

	//The color of the tile to add to the closed list.
	_openList[index]->setColor(RGB(180, 180, 255));

	//Add to closed list
	_closeList.push_back(_openList[index]);

	//Exclude tiles added to closed list from open list
	_openList.erase(_openList.begin() + index);

	//Closed list index increment added most recently
	_lastIndex++;
}

void aStar::arriveCheck()
{
	if (_closeList[_lastIndex]->getIdY() == _endY && _closeList[_lastIndex]->getIdX() == _endX)
	{
		astarState = ASTAR_FOUND;							//Found
		_closeList[_lastIndex]->setColor(RGB(10, 120, 55)); //Dark green
		showWay(_closeList[_lastIndex]);					//Show route
		isFind = true;
	}
}

void aStar::showWay(aTile* tile)
{
	//If it is not a destination
	if (!(tile->getIdY() == _endY && tile->getIdX() == _endX))
	{
		tile->setColor(RGB(22, 14, 128));	//Dark blue
	}

	_roadList.push_back(tile);
	tile = tile->getParentNode();

	if (tile->getParentNode() == NULL)		//If the parent of the tile is null, stop it
	{
		reverse(begin(_roadList), end(_roadList));
		return;
	}
	else
	{
		showWay(tile);         //showWay() Call again (from the arrival point to the starting point in reverse order)
	}
}


void aStar::plInit()
{
	px = py = 0;
	plSpeed = 0;
	timeCount = 10;
	count = 1;
	isFind = false;
	i = 0;
	plSpeed = 4;
}

void aStar::plPosInit()
{
	px = _startX * TILEWIDTH + 200;
	py = _startY * TILEHEIGHT;

}

void aStar::plMove()
{
	if (count++ % timeCount == 0)
	{
		if (isFind)
		{
			if (px != _roadList[i]->getRect().left)
				px = _roadList[i]->getRect().left;
			if (py != _roadList[i]->getRect().top)
				py = _roadList[i]->getRect().top;

			if (px == _roadList[i]->getRect().left && py == _roadList[i]->getRect().top)
			{
				if (i < _roadList.size() - 1) i++;
				else
				{
					isFind = false;
					_roadList.clear();
					vector<aTile*>().swap(_roadList);
					i = 0;
					count = 1;
				}
			}
		}
	}
}


void aStar::astarReset()
{
	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		_openList.clear();
		vector<aTile*>().swap(_openList);
		_closeList.clear();
		vector<aTile*>().swap(_closeList);

		this->init();
	}
}

void aStar::textPrint()
{
	TextOut(getMemDC(), 15, 15, "1 : EMTPY", strlen("1 : EMTPY"));
	TextOut(getMemDC(), 15, 35, "2 : START", strlen("2 : START"));
	TextOut(getMemDC(), 15, 55, "3 : END", strlen("3 : END"));
	TextOut(getMemDC(), 15, 75, "4 : WALL", strlen("4 : WALL"));
	TextOut(getMemDC(), 15, 95, "R : RESTART", strlen("R : RESTART"));
	TextOut(getMemDC(), 15, 115, "SPACE : START", strlen("SPACE : START"));

	switch (mouseState)
	{
	case EMPTY:
		sprintf(str, "MouseState: EMPTY");
		break;
	case START:
		sprintf(str, "MouseState: START");
		break;
	case END:
		sprintf(str, "MouseState: END");
		break;
	case WALL:
		sprintf(str, "MouseState: WALL");
		break;
	}
	TextOut(getMemDC(), 15, 135, str, strlen(str));

	sprintf(str, "시작위치 설정여부:%d", _isStartSetting);
	TextOut(getMemDC(), 15, 165, str, strlen(str));
	sprintf(str, "목표위치 설정여부:%d", _isEndSetting);
	TextOut(getMemDC(), 15, 185, str, strlen(str));

	switch (astarState)
	{
	case ASTAR_SEARCHING:
		sprintf(str, "에이스타 상태:  탐색중");
		break;
	case ASTAR_FOUND:
		sprintf(str, "에이스타 상태:  찾았다");
		break;
	case ASTAR_NOWAY:
		sprintf(str, "에이스타 상태:  길이 없다");
		break;
	case ASTAR_UNPREPARE:
		sprintf(str, "에이스타 상태:  준비중");
		break;
	}
	TextOut(getMemDC(), 15, 205, str, strlen(str));
}

void aStar::selectMouseState()
{
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		mouseState = EMPTY;
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		mouseState = START;
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		mouseState = END;
	}
	if (KEYMANAGER->isOnceKeyDown('4'))
	{
		mouseState = WALL;
	}
}
