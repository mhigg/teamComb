#pragma once
#include <list>
#include <memory>

class Obj;

// using uniqueObj		= std::unique_ptr<Obj>;
// using uniqueObjList	= std::list<uniqueObj>;
using sharedObj = std::shared_ptr<Obj>;			// シェアードポインタ
using sharedList = std::list<sharedObj>;
using sharedListObj = std::shared_ptr<sharedList>;
using weekListObj = std::weak_ptr<sharedList>;	// ウィークポインタ
using ListObj_itr = sharedList::iterator;


struct AddObjList
{
	ListObj_itr operator()(weekListObj objList, sharedObj objPtr)
	{
		objList.lock()->push_back(std::move(objPtr)); // moveでスマートポインタを譲渡
		ListObj_itr itr = objList.lock()->end();
		itr--;
		return itr;
	}
};