#pragma once
#include <list>
#include <array>
#include "Obj.h"
#include "ClassObj.h"

class EditScene :
	public BaseScene
{
public:
	EditScene();
	~EditScene();
	uniqueBase Update(						// XV
		uniqueBase own,					// Œ»İ‚Ì¼°İ
		const GameCtrl &controler		// ·°æ“¾
	);
	bool menuFlag;							// ÒÆ­°‰æ–Ê‚Ì^‹U
private:
	sharedListObj objList;					// ¼ª±ÄŞÎß²İÀ°
	int Init(void);							// ºİ½Ä×¸À‚Æ‚È‚é
	bool EditDraw(void);					// •`‰æ
};

