// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>
#include <windows.h>
//������ (�ּ�ġ�� �ܼ�â�� �������)
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
// C++ ��Ÿ�� ��� �����Դϴ�.
#include <iostream>
using namespace std;
// ���ֻ���ϴ� STL
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
//			## ���� ���� ��������� �̰��� �߰��Ѵ� ##
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
//			## �̱����� �̰��� �߰��Ѵ� ##
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
//			## �����ι� - ��ũ�� ## (������â �ʱ�ȭ)
//====================================================================
#define WINNAME (LPTSTR)(TEXT("Enter the Gungeon"))
#define WINSTARTX	0
#define WINSTARTY	0
#define WINSIZEX	1080
#define WINSIZEY	675
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

//====================================================================
//			## ��ũ���Լ� ## (Ŭ���� �����Ҵ�� �κ� ����)
//====================================================================
#define SAFE_DELETE(p)			{if(p) {delete(p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)		{if(p) {delete[] (p); (p) = NULL;}}

//====================================================================
//			## �������� ## 
//====================================================================
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;

//Movie���� ����
extern HWND _hWndMovie;
extern BOOL _isMoviePlay;