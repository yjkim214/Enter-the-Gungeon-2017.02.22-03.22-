#pragma once
#include "gameNode.h"

enum TILE_STATE			//Enum to display tile status
{
	TILE_EMPTY,			//The tile is an empty tile
	TILE_START,			//The tile is an start tile
	TILE_END,			//The tile is an end tile
	TILE_WALL			//The tile is an wall tile
};

class aTile : public gameNode
{
private:
	POINT _center;			//Center value to draw rectangle
	RECT _rc;				//RECT
	aTile* _parentNode;		//Variable to store parent tile address value
	COLORREF _color;		//Square color

	int _idX;				//tile index x
	int _idY;				//tile index y
	int _G;					//tile G value (Cost from start to current location)
	int _H;					//tile H value (Cost from current location to target location)
	int _F;					//tile F value (G + H)

	TILE_STATE tileState;	//tile state
	bool _isListOn;			//Is it added to an open list?
	bool _isOpen;			//Whether you can pass?

public:
	explicit aTile() :_parentNode(NULL), _idX(0), _idY(0), _G(0), _H(0), _F(0), tileState(TILE_EMPTY), _isListOn(false), _isOpen(true) {}
	~aTile() {}

	HRESULT init(int idX, int idY, int tileWidth, int tileHeight, int startX = 200, int startY = 0);
	void release() {}
	void update() {}
	void render();

	//==============================================================================
	//Accessor,Mutator Function
	//==============================================================================

	//Tile state
	TILE_STATE getTileState()const { return this->tileState; }
	void setTileState(TILE_STATE tileState) { this->tileState = tileState; }

	//G
	inline int getG()const { return this->_G; }
	inline void setG(int G) { this->_G = G; }

	//H
	inline int getH()const { return this->_H; }
	inline void setH(int H) { this->_H = H; }

	//F
	inline int getF()const { return this->_F; }
	inline void setF(int F) { this->_F = F; }

	//IsListOn
	inline bool getIsListOn()const { return this->_isListOn; }
	inline void setIsListOn(bool is) { this->_isListOn = is; }

	//ParentNode
	inline aTile* getParentNode()const { return this->_parentNode; }
	inline void setParentNode(aTile* t) { this->_parentNode = t; }

	//IdX
	inline int getIdX()const { return this->_idX; }

	//IdY
	inline int getIdY()const { return this->_idY; }

	//IsOpen
	inline bool getIsOpen()const { return this->_isOpen; }
	inline void setIsOpen(bool isOpen) { this->_isOpen = isOpen; }

	//Rect
	inline RECT getRect()const { return this->_rc; }

	//Color
	inline void setColor(COLORREF color) { this->_color = color; }

};

