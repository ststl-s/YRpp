/*
	TaskForces as in the AI inis
*/

#ifndef TASKFORCE_H
#define TASKFORCE_H

#include <AbstractTypeClass.h>

//forward declarations
class TechnoTypeClass;

struct TaskForceEntryStruct
{
	TechnoTypeClass* Type;
	int Amount;
};

class TaskForceClass : public AbstractTypeClass
{
public:
	enum {AbsID = abs_TaskForce};

	//Array
	ABSTRACTTYPE_ARRAY(TaskForceClass);

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~TaskForceClass() RX;

	//AbstractClass
	virtual eAbstractType WhatAmI() R0;
	virtual int Size() R0;

	//Constructor
	TaskForceClass(const char* pID) : AbstractTypeClass(false)
		{ JMP_THIS(0x6E7E80); }

protected:
	TaskForceClass() : AbstractTypeClass(false) { }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	int     Group;
	int     CountEntries;
	TaskForceEntryStruct Entries [0x6];
};

#endif
