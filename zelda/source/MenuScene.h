#pragma once
#include "BaseScene.h"
#include <array>

constexpr auto MENU_NUM	= 4;
constexpr auto BOX_SIZE	= 400;


using BOX_ARRAY = std::array< VECTOR2 , MENU_NUM >;
using MOVE_FLAG = std::array<   bool  , MENU_NUM >;

class MenuScene :
	public BaseScene
{
public:
	MenuScene();
	~MenuScene();
	uniqueBase UpDate(					// �X�V
		uniqueBase own,					// ���݂̼��
		const GameCtrl &controller		// ���擾
	);
private:
	void MenuDraw(void);	// �`��
	int Init(void);			// ������

	BOX_ARRAY movePos;		// Box�̍��W�����z��
	MOVE_FLAG moveFlag;		// Box�̈ړ�����p�z��
};

