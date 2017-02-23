#pragma once
#include "gameNode.h"
#include "aTile.h"

#define TILEWIDTH	32		//Tile width length
#define TILEHEIGHT	32		//Tile height length
#define TILENUMX		30		//Width tile number
#define TILENUMY		30		//Height tile number
#define BIGNUM		5000	//Cost comparison value
#define SLASH		14		//Diagonal cost
#define BEELINE		10		//Straight cost

enum ASTAR_STATE			//Astar state
{
	ASTAR_SEARCHING,		//Searching
	ASTAR_FOUND,			//Discover route
	ASTAR_NOWAY,			//There is no route
	ASTAR_UNPREPARE,		//Tile placement imperfect
};

enum MOUSE_STATE		//Mouse state
{
	EMPTY,				//Empty
	START,				//Starting point
	END,				//Target point
	WALL				//Wall
};

class aStar : public gameNode
{
private:
	aStar(const aStar&);					//Copy constructor Prevention
	const aStar operator=(const aStar&);	//Assignment operator Prevention

private:
	vector<vector<aTile*>> _tile;	//Tile size(Dynamic allocation)
	MOUSE_STATE mouseState;			//Mouse state

	bool _isStartSetting;			//Whether start location is set
	bool _isEndSetting;				//Whether target location is set

	vector<aTile*> _openList;		//Open list
	vector<aTile*> _closeList;		//Closed list
	int _lastIndex;					//Index of the most recently added closed list

	int LastIdX;					//The last added closed list x
	int LastIdY;					//The last added closed list y
	int LastG;						//The last added closed list G(Cost from start position to current position)

	ASTAR_STATE astarState;			//Show the status of the Astar

	int _startX, _startY;			//Starting point coordinates(x,y)
	int _endX, _endY;				//Target point coordinates(x,y)

public:
	explicit aStar() :mouseState(EMPTY), _isStartSetting(false), _isEndSetting(false), _lastIndex(0),
		LastIdX(0), LastIdY(0), LastG(0), astarState(ASTAR_UNPREPARE), _startX(0), _startY(0), _endX(0), _endY(0) {}
	~aStar() {}

	HRESULT init();
	void release();
	void update();
	void render();

	void astarReset();			//Astar reset

	void textPrint();			//Text print
	void selectMouseState();	//Mouse state set
	void tileSetting();			//Tile setting

	void tileClick();			//Tile click
	void astarStart();			//Astar start

	void openListCheck();		//Openlist calculate
	void calculateH();			//Calculate the H value of tiles within an openlist
	void calculateF();			//Calculate the F value of tiles within an openlist
	void closeListCheck();		//Closedlist calcuate
	void arriveCheck();			//Arrival?
	void showWay(aTile* tile);	//A function that shows the route from the start point to the arrival point after arrival


								//Public variables for example
public:
	int px, py;					//Player coordinates
	int plSpeed;				//Player speed
	int timeCount;				//Player movement time variable1
	int count;					//Player movement time variable2

	vector<aTile*> _roadList;	//Road list
	bool isFind;				//Whether the directions are complete
	int i;						//Variables for traversing the road list vector

	void plInit();				//Player variable initialization
	void plPosInit();			//Player positioning
	void plMove();				//Player movement processing function
};

