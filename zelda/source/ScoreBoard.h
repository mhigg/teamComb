#pragma once
#include "Obj.h"

class ScoreBoard 
{
public:
	static ScoreBoard &GetInstance(void)
	{
		static ScoreBoard s_Instance;
		return s_Instance;
	}
	void Draw(void);		// •`‰æ
private:
	ScoreBoard();
	~ScoreBoard();
};

