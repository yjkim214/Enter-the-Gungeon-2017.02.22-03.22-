#pragma once
#include "gameNode.h"
/*�����δ� �� ������ϸ� �߰����ش�*/
#include "pixelCollision.h"
#include "sceneTest.h"
#include "iniTestScene.h"
#include "loadingScene.h"
#include "soundTestScene.h"
#include "tankGameScene.h"
#include "maptoolScene.h"
#include "isometricScene.h"
#include "isometric.h"
#include "aStarTestScene.h"		//A* ��ã���׽�Ʈ �� �߰� (����ã��)
#include "aStarScene.h"			//A* ��ã���׽�Ʈ �� �߰� (���׼���)
#include "gdipTestScene.h"		//GDIPlus �׽�Ʈ �� �߰�

#include "introScene.h"
#include "loadingScene.h"
#include "trailerScene.h"
#include "menuScene.h"

class mainGame : public gameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	mainGame() {}
	~mainGame() {}
};

