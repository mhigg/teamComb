#pragma once
#include "BaseScene.h"
#include <array>

constexpr auto MENU_NUM		= 3;
constexpr auto BOX_SIZE_X	= 460;
constexpr auto SIZE_Y			= 90;			// �ς��Ȃ��Ă�������
constexpr auto PUSH_SIZE		= 40;			// �I�𒆂��ƭ��ް�̵̾��


using BOX_ARRAY = std::array< VECTOR2 , MENU_NUM >;
using MOVE_FLAG = std::array<   bool  , MENU_NUM >;
using SELECT_POINT = std::array<   int, MENU_NUM >;

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
	void MenuDraw(void);		// �`��
	int Init(void);						// ������

	BOX_ARRAY movePos;		// Box�̍��W�����z��
	MOVE_FLAG moveFlag;		// Box�̈ړ�����p�z��
	SELECT_POINT selectPoint; // �I��ł���z�̉��Z�l
	int nowSelect;					 // �ǂ̃��[�h��I�����Ă��邩
	bool pushFlag;

	unsigned int count;				// MenuScene���̶���
	double add;						// �ƭ��ް�̉��Z�l
	VECTOR2 size;					// Box�̻���
};

