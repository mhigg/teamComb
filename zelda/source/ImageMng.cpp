#include "DxLib.h"
#include "VECTOR2.h"
#include "ImageMng.h"


ImageMng::ImageMng()
{
}


ImageMng::~ImageMng()
{
}

//loadGraph�p
const VEC_INT& ImageMng::GetID(std::string f_name)
{
	//end(�I�[)�܂�find(����)���Ă�������Ȃ��Ƃ�
	if (imageMap.find(f_name) == imageMap.end())
	{
		imageMap[f_name].resize(1);
		//f_name��۰�ނ��ĕۑ�
		imageMap[f_name][0] = LoadGraph(f_name.c_str(), false);
	}
	return imageMap[f_name];
}

//divGraph�p
const VEC_INT & ImageMng::GetID(std::string f_name, VECTOR2 divSize, VECTOR2 divCnt)
{
	if (imageMap.find(f_name) == imageMap.end())
	{
		imageMap[f_name].resize(divCnt.x * divCnt.y);
		LoadDivGraph(
			f_name.c_str(),
			divCnt.x * divCnt.y,
			divCnt.x,
			divCnt.y,
			divSize.x,
			divSize.y,
			&imageMap[f_name][0],
			true
		);
	}
	return imageMap[f_name];

}