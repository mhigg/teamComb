#pragma once
#include "BaseScene.h"
class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	uniqueBase UpDate(						// �X�V
		uniqueBase own,					// ���݂̼��
		const GameCtrl &controller		// ���擾
	);
private:
	void TitleDraw(void);	// �`��
	bool FadeOut(void);		// ̪��ޱ�ėp�֐�
	int Init(void);			// ������
	int cnt;				// �_�Ŷ���

	int fadeOutCnt;			// ̪��ޱ�ėp����
	int scenecnt;			// ��ݐ؂�ւ��p����
	bool sceneflag;			// ��݂��؂�ւ���׸�};

