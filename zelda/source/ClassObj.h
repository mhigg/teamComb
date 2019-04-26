#pragma once
#include <list>
#include <memory>

class Obj;

using sharedObj = std::shared_ptr<Obj>;			// �V�F�A�[�h�|�C���^
using sharedList = std::list<sharedObj>;
using sharedListObj = std::shared_ptr<sharedList>;
using weakListObj = std::weak_ptr<sharedList>;	// �E�B�[�N�|�C���^
using ListObj_itr = sharedList::iterator;


struct AddObjList
{
	ListObj_itr operator()(weakListObj objList, sharedObj objPtr)
	{
		objList.lock()->push_back(std::move(objPtr)); // move�ŃX�}�[�g�|�C���^�����n
		ListObj_itr itr = objList.lock()->end();
		itr--;
		return itr;
	}
};