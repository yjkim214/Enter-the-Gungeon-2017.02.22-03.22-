// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>
#include <windows.h>
//디버깅용 (주석치면 콘솔창이 사라진다)
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
// C++ 런타임 헤더 파일입니다.
#include <iostream>
using namespace std;
// 자주사용하는 STL
#include <string>
#include <vector>
#include <map>
//GDI+
#include <ole2.h>
#include <gdiplus.h>
#pragma comment(lib,"gdiplus")
using namespace Gdiplus;
//MCI
#include <vfw.h>
#pragma comment(lib,"vfw32.lib")

//====================================================================
//			## 내가 만든 헤더파일을 이곳에 추가한다 ##
//====================================================================
#include "commonMacroFunction.h"
#include "keyManager.h"
#include "randomFunction.h"
#include "imageManager.h"
#include "util.h"
using namespace MY_UTIL;
#include "playerData.h"
#include "txtData.h"
#include "iniData.h"
#include "sceneManager.h"
#include "timeManager.h"
#include "soundManager.h"
#include "gdipManager.h"
#include "movieManager.h"

//====================================================================
//			## 싱글톤을 이곳에 추가한다 ##
//====================================================================
#define KEYMANAGER keyManager::getSingleton()
#define RND randomFunction::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define PLAYERDATA playerData::getSingleton()
#define TXTDATA	txtData::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define INIDATA iniData::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define GDIPLUS	gdipManager::getSingleton()
#define MOVIEMANAGER movieManager::getSingleton()

//====================================================================
//			## 디파인문 - 메크로 ## (윈도우창 초기화)
//====================================================================
#define WINNAME (LPTSTR)(TEXT("Enter the Gungeon"))
#define WINSTARTX	0
#define WINSTARTY	0
#define WINSIZEX	1080
#define WINSIZEY	675
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

//====================================================================
//			## 메크로함수 ## (클래스 동적할당된 부분 해제)
//====================================================================
#define SAFE_DELETE(p)			{if(p) {delete(p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)		{if(p) {delete[] (p); (p) = NULL;}}

//====================================================================
//			## 전역변수 ## 
//====================================================================
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;

//Movie관련 변수
extern HWND _hWndMovie;
extern BOOL _isMoviePlay;