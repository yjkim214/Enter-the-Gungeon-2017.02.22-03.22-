#include "stdafx.h"
#include "movieManager.h"

void movieManager::play(const char * filePath, int x, int y, int width, int height)
{
	if (!_isMoviePlay) { _isMoviePlay = true; }
	if (width == 0) { width = WINSIZEX; }
	if (height == 0) { height = WINSIZEY; }

	if (_hWndMovie)
	{
		MCIWndClose(_hWndMovie);
		MCIWndDestroy(_hWndMovie);
		_hWndMovie = 0;
	}

	_hWndMovie = MCIWndCreate(_hWnd,
		_hInstance,
		MCIWNDF_NOTIFYMODE | MCIWNDF_NOPLAYBAR |
		MCIWNDF_NOMENU,
		filePath);

	if (_hWndMovie)
	{
		SetWindowPos(_hWndMovie, NULL, x, y, width, height, SWP_NOZORDER);
		MCIWndPlay(_hWndMovie);
	}
}