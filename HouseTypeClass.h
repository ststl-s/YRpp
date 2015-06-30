/*
	ObjectTypes are initialized by INI files.
*/

#pragma once

#include <AbstractTypeClass.h>
#include <Helpers\String.h>

class AircraftTypeClass;
class InfantryTypeClass;
class UnitTypeClass;

class NOVTABLE HouseTypeClass : public AbstractTypeClass
{
public:
	static const AbstractType AbsID = AbstractType::HouseType;

	//Array
	ABSTRACTTYPE_ARRAY(HouseTypeClass);

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm,BOOL fClearDirty) R0;

	//Destructor
	virtual ~HouseTypeClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int	Size() const R0;

	//Constructor
	HouseTypeClass(const char* pID) : AbstractTypeClass(false)
		{ JMP_THIS(0x5113F0); }

	static signed int __fastcall FindIndexOfName(const char *name)
		{ JMP_STD(0x5117D0); }

protected:
	HouseTypeClass() : AbstractTypeClass(false) { }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	FixedString<25> ParentCountry;
	PROTECTED_PROPERTY(BYTE, align_B1[3]);
	int            ArrayIndex;
	int            ArrayIndex2; //dunno why
	int            SideIndex;
	int            ColorSchemeIndex;
	PROTECTED_PROPERTY(DWORD, align_C4);

	//are these unused TS leftovers?
	double         FirepowerMult;
	double         GroundspeedMult;
	double         AirspeedMult;
	double         ArmorMult;
	double         ROFMult;
	double         CostMult;
	double         BuildtimeMult;
	//---

	float          ArmorInfantryMult;
	float          ArmorUnitsMult;
	float          ArmorAircraftMult;
	float          ArmorBuildingsMult;
	float          ArmorDefensesMult;

	float          CostInfantryMult;
	float          CostUnitsMult;
	float          CostAircraftMult;
	float          CostBuildingsMult;
	float          CostDefensesMult;

	float          SpeedInfantryMult;
	float          SpeedUnitsMult;
	float          SpeedAircraftMult;

	float          BuildtimeInfantryMult;
	float          BuildtimeUnitsMult;
	float          BuildtimeAircraftMult;
	float          BuildtimeBuildingsMult;
	float          BuildtimeDefensesMult;

	float          IncomeMult;

	TypeList<InfantryTypeClass*> VeteranInfantry;
	TypeList<UnitTypeClass*> VeteranUnits;
	TypeList<AircraftTypeClass*> VeteranAircraft;

	char Suffix [4];

	char           Prefix;
	bool           Multiplay;
	bool           MultiplayPassive;
	bool           WallOwner;
	bool           SmartAI; //"smart"?
	PROTECTED_PROPERTY(BYTE, padding_1A9[7]);
};
