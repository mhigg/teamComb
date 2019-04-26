// 画像の読み込み

#pragma once
#include <mutex>
#include <vector>
#include <map>

class VECTOR2;
using VEC_INT = std::vector<int>;

//短縮定義
#define lpImageMng ImageMng::GetInstance()
#define IMAGE_ID(X) (ImageMng::GetInstance().GetID(X))

class ImageMng
{
public:
	static ImageMng &GetInstance(void)
	{
		static ImageMng s_instance;
		return s_instance;
	}

	//LoadGraph用
	const VEC_INT& GetID(std::string f_name);
	//LoadDivGraph対応
	const VEC_INT& GetID(std::string f_name, VECTOR2 divSize, VECTOR2 divCnt);


private:
	ImageMng();
	~ImageMng();

	std::map<std::string, VEC_INT> imageMap;
};

