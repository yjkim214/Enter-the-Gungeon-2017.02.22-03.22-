#pragma once
#include "singletonBase.h"

class movieManager : public singletonBase<movieManager>
{
private:
	movieManager(const movieManager&);

public:
	void play(const char* filePath, int x = 0, int y = 0, int width = 0, int height = 0);

	movieManager() {}
	~movieManager() {}
};