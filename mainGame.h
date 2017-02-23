#pragma once
#include "gameNode.h"
/*앞으로는 씬 헤더파일만 추가해준다*/
#include "pixelCollision.h"
#include "sceneTest.h"
#include "iniTestScene.h"
#include "loadingScene.h"
#include "soundTestScene.h"
#include "tankGameScene.h"
#include "maptoolScene.h"
#include "isometricScene.h"
#include "isometric.h"
#include "aStarTestScene.h"		//A* 길찾기테스트 씬 추가 (버그찾기)
#include "aStarScene.h"			//A* 길찾기테스트 씬 추가 (버그수정)
#include "gdipTestScene.h"		//GDIPlus 테스트 씬 추가

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

