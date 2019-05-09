#pragma once
#include <string>
#include <map>
#include "VECTOR2.h"
#include "classObj.h"

enum ANIM_TBL {
	ANIM_TBL_START_ID,		// ｱﾆﾒｰｼｮﾝの開始
	ANIM_TBL_FRAME,			// ｱﾆﾒｰｼｮﾝのｺﾏ数
	ANIM_TBL_INV,			// ｺﾏごとの間隔
	ANIM_TBL_LOOP,			// ﾙｰﾌﾟするかどうか
	ANIM_TBL_MAX
};

enum DIR {
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_MAX
};

enum OBJ_TYPE {
	OBJ_PLAYER,
	OBJ_ENEMY,
	OBJ_BOMB,
	OBJ_EDIT_CURSOR,
	OBJ_MAX
};

class GameCtrl;

class Obj
{
public:
	Obj();

	// 受け取ったdrawOffsetを自分の持つdrawOffsetに入れる
	Obj(VECTOR2 drawOffset);
	virtual ~Obj();

	bool Init(
		std::string fileName,		// 画像のﾌｧｲﾙ名
		VECTOR2 divSize,			// 分割ｻｲｽﾞ
		VECTOR2 divCnt				// 分割数の初期化
	);
	bool Init(
		std::string fileName,		// 画像のﾌｧｲﾙ名
		VECTOR2 divSize,			// 分割ｻｲｽﾞ
		VECTOR2 divCnt,				// 分割数の初期化
		VECTOR2 pos					// 座標
	);

	virtual bool initAnim(void) { return true; };	// ｱﾆﾒｰｼｮﾝの設定　AddAnim関数に値を設定する
	void UpDate(
		const GameCtrl &controller,	// 情報更新
		weakListObj objList			// ｺﾝﾄﾛｰﾗｰ自体のﾎﾟｲﾝﾀを渡す
	);
	virtual bool CheckDeath(void) { return false; };	// 死亡判定　基本死んでなければfalse
	virtual bool CheckObjType(OBJ_TYPE type) = 0;		// 指定した値と同じ型が来たらtrueを返す
	virtual void Draw(void);		// 描画
	void Draw(unsigned int id);		// ID指定描画
	const VECTOR2 &GetPos(void);	// 座標取得関数

	bool AddAnim(
		std::string animName,		// ｱﾆﾒｰｼｮﾝの名前
		int id_x,					// 動き
		int id_y,					// 種別
		int frame,					// 総ｺﾏ数
		int inv,					// ｱﾆﾒｰｼｮﾝ1ｺﾏごとの間隔
		bool loop					// ｱﾆﾒｰｼｮﾝのﾙｰﾌﾟ有無(true:あり,false:なし)
	);

	// 同じ名前のｱﾆﾒｰｼｮﾝをｾｯﾄしたときはtrue
	// 存在しないｱﾆﾒｰｼｮﾝ名をｾｯﾄしたときはfalse
	// 別のｱﾆﾒｰｼｮﾝをｾｯﾄしたときはｱﾆﾒｰｼｮﾝ名を再設定し、ｺﾏ数のｶｳﾝﾄとanimEndFlagをﾘｾｯﾄする
	bool SetAnim(std::string animName);

	std::string GetAnim(void);	// 現在のｱﾆﾒｰｼｮﾝ名を取得する

private:
	virtual void SetMove(const GameCtrl &controller, weakListObj objList) = 0;

	std::string animName;	// 表示するｱﾆﾒｰｼｮﾝ名
	std::map<std::string, int[ANIM_TBL_MAX]> animTable;	// ｱﾆﾒｰｼｮﾝの設定を保存する配列

protected:
	void SetPos(VECTOR2 pos);	// 座標を設定

	VECTOR2 pos;				// 表示する座標
	const VECTOR2 drawOffset;	// 描画ｵﾌｾｯﾄ
	VECTOR2 scrollOffset;		// ｽｸﾛｰﾙによるｵﾌｾｯﾄ

	std::string imageName;	// 表示する画像のﾌｧｲﾙ名
	VECTOR2 divSize;		// 画像の分割ｻｲｽﾞ
	VECTOR2 divCnt;			// 画像の分割数

	OBJ_TYPE objType;		// ｵﾌﾞｼﾞｪｸﾄの種類

	DIR dir;				// ｵﾌﾞｼﾞｪｸﾄの向いている方向

	unsigned int animCnt;	// ｱﾆﾒｰｼｮﾝのｶｳﾝﾄ
	bool animEndFlag;		// ｱﾆﾒｰｼｮﾝの最終ｺﾏ到達ﾌﾗｸﾞ

	bool visible;
};