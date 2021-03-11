#pragma once

#include <AbstractClass.h>
class BuildingClass;
class BuildingTypeClass;

class NOVTABLE FoggedObjectClass : public AbstractClass
{
public:
	static const AbstractType AbsID = AbstractType::FoggedObject;

	static DynamicVectorClass<FoggedObjectClass*>* const Array;

	struct DrawRecord
	{
		union{
			ObjectTypeClass* ObjectType;
			BuildingTypeClass* BuildingType;
			TerrainTypeClass* TerrainType;
			AnimTypeClass* AnimType;
		};
		int FrameIndex;
		bool IsFireStormWall;
		int zAdjust;

		bool operator==(const DrawRecord&) const { return true; };
	};

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~FoggedObjectClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int	Size() const R0;

	virtual CellStruct* GetMapCoords(CellStruct* pUCell) const R0;

	CellStruct GetMapCoords() const {
		CellStruct ret;
		this->GetMapCoords(&ret);
		return ret;
	}

	//Constructor
	FoggedObjectClass() noexcept
		: FoggedObjectClass(noinit_t())
	{ JMP_THIS(0x4D08B0); }

	// for building
	FoggedObjectClass(BuildingClass* pBuilding, bool translucent) noexcept
		: FoggedObjectClass(noinit_t())
	{ 	JMP_THIS(0x4D0EF0); }

	// for terrain
	FoggedObjectClass(TerrainClass* pTerrain) noexcept
		: FoggedObjectClass(noinit_t())
	{ 	JMP_THIS(0x4D1370); }

	// for overlay
	FoggedObjectClass(const CoordStruct& location, int overlayIndex, int powerup) noexcept
		: FoggedObjectClass(noinit_t())
	{ JMP_THIS(0x4D0980); }

	// for smudge
	FoggedObjectClass(const CoordStruct* location, int smudgeIndex, int frameIdx) noexcept
		: FoggedObjectClass(noinit_t())
	{ JMP_THIS(0x4D0C40); }

	// helper
	FoggedObjectClass& operator=(FoggedObjectClass&& foggedObejct) noexcept
	{
		OverlayIndex = foggedObejct.OverlayIndex;
		Owner = foggedObejct.Owner;
		Powerup = foggedObejct.Powerup;
		CoveredAbstractType = foggedObejct.CoveredAbstractType;
		Location = foggedObejct.Location;
		Bound = foggedObejct.Bound;
		Level = foggedObejct.Level;
		SmudgeIndex = foggedObejct.SmudgeIndex;
		SmudgeFrameIndex = foggedObejct.SmudgeFrameIndex;
		Translucent = foggedObejct.Translucent;
		DrawRecords.Swap(foggedObejct.DrawRecords);

		return *this;
	}

	FoggedObjectClass(const FoggedObjectClass& foggedObejct) noexcept
	{
		*this = foggedObejct;
	}
	FoggedObjectClass& operator=(const FoggedObjectClass& foggedObejct) noexcept
	{
		OverlayIndex = foggedObejct.OverlayIndex;
		Owner = foggedObejct.Owner;
		Powerup = foggedObejct.Powerup;
		CoveredAbstractType = foggedObejct.CoveredAbstractType;
		Location = foggedObejct.Location;
		Bound = foggedObejct.Bound;
		Level = foggedObejct.Level;
		SmudgeIndex = foggedObejct.SmudgeIndex;
		SmudgeFrameIndex = foggedObejct.SmudgeFrameIndex;
		Translucent = foggedObejct.Translucent;
		DrawRecords = foggedObejct.DrawRecords;
		return *this;
	}

protected:
	explicit __forceinline FoggedObjectClass(noinit_t) noexcept
		: AbstractClass(noinit_t())
	{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
public:
	int OverlayIndex;
	HouseClass* Owner;
	int Powerup;
	AbstractType CoveredAbstractType;
	CoordStruct Location;
	RectangleStruct Bound;
	int Level;
	int SmudgeIndex;
	int SmudgeFrameIndex;
	DynamicVectorClass<DrawRecord> DrawRecords;
	char Translucent;
	// never used in YR
	char field_75;
	char field_76;
	char field_77;

};