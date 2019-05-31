#pragma once
#include <array>
#include "BaseScene.h"

constexpr int BOX_SIZE_X	= 460;
constexpr int BOX_SIZE_Y	= 90;			// �ς��Ȃ��Ă�������
constexpr int PUSH_SIZE		= 40;			// �I�𒆂��ƭ��ް�̵̾��

enum MODE {
	MODE_MALTI,		// ���Ӱ��
	MODE_SINGLE,	// �ݸ��Ӱ��
	MODE_HOWTO,		// ������@���
	MODE_MAX
};

using BOX_ARRAY = std::array< VECTOR2, MODE_MAX >;
using MOVE_FLAG = std::array< bool, MODE_MAX >;
using SELECT_POINT = std::array< int, MODE_MAX >;

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
	int Init(void);				// ������
	BOX_ARRAY movePos;			// Box�̍��W�����z��
	MOVE_FLAG moveFlag;			// Box�̈ړ�����p�z��
	SELECT_POINT selectPoint;	// �I��ł���z�̉��Z�l
	MODE nowMode;				// �ǂ�Ӱ�ނ�I�����Ă��邩
	bool descriptionFlag;	    // ����
	bool pushFlag;

	unsigned int count;			// MenuScene���̶���
	double add;					// �ƭ��ް�̉��Z�l
	VECTOR2 size;				// Box�̻���
};

