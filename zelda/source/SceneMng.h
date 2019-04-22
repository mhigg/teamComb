#pragma once
class SceneMng
{
public:
	static SceneMng	GetInstance(void)
	{
		static SceneMng s_instance;
		return s_instance;
	}

	~SceneMng();
};

