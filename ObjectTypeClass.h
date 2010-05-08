/*
	ObjectTypes are initialized by INI files.
*/

#ifndef OBJTYPE_H
#define OBJTYPE_H

#include <AbstractTypeClass.h>
#include <FileSystem.h>

//forward declarations
class TechnoTypeClass;
class HouseTypeClass;
class ObjectClass;
class BuildingTypeClass;

class ObjectTypeClass : public AbstractTypeClass
{
public:
	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;
	virtual HRESULT __stdcall GetSizeMax(ULARGE_INTEGER* pcbSize) R0;

	//Destructor
	virtual ~ObjectTypeClass() RX;

	//ObjectTypeClass
	virtual CoordStruct* vt_entry_6C(CoordStruct* pDest, CoordStruct* pSrc) R0;
	virtual DWORD GetOwners() R0;
	virtual int GetPipMax() R0;
	virtual void vt_entry_78(DWORD dwUnk) RX;
	virtual void vt_entry_7C(DWORD dwUnk) RX;
	virtual bool SpawnAtMapCoords(CellStruct* pMapCoords, HouseClass* pOwner) = 0;
	virtual int GetActualCost(HouseClass* pHouse) R0;
	virtual int GetBuildSpeed() R0;
	virtual ObjectClass* CreateObject(HouseClass* pOwner) = 0;
	virtual void vt_entry_90(DWORD dwUnk) RX;
	virtual BuildingTypeClass* GetFactoryType(bool OverridePrereqs, bool OverridePower, bool OverrideBuildLimit,
		HouseClass *House) R0;
	virtual SHPStruct* GetCameo() R0;
	virtual SHPStruct* GetImage() R0;

	//Constructor
	ObjectTypeClass(const char* pID) : AbstractTypeClass(false)
		{ JMP_THIS(0x5F7090); }

protected:
	ObjectTypeClass() : AbstractTypeClass(false) { }
	ObjectTypeClass(bool) : AbstractTypeClass(false) { };

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	ColorStruct RadialColor;
	BYTE          unused_9B;
	int           Armor;
	int           Strength;
	SHPStruct*    Image;
	bool          IsImageAllocated;
	bool          unused_A9;
	bool          unused_AA;
	bool          unused_AB;
	SHPStruct*    AlphaImage;
	VoxelStruct MainVoxel;
	VoxelStruct TurretVoxel; //also used for WO voxels
	VoxelStruct BarrelVoxel;

	VoxelStruct ChargerTurrets [0x12];
	VoxelStruct ChargerBarrels [0x12];

	bool          NoSpawnAlt;
	BYTE          unused_1E9;
	BYTE          unused_1EA;
	BYTE          unused_1EB;
	int           MaxDimension;
	int           CrushSound; //index
	int           AmbientSound; //index

	char ImageFile [0x19];

	bool           AlternateArcticArt;
	bool           ArcticArtInUse; //not read from ini

	char AlphaImageFile [0x19];

	bool           Theater;
	bool           Crushable;
	bool           Bombable;
	bool           RadarInvisible;
	bool           Selectable;
	bool           LegalTarget;
	bool           Insignificant;
	bool           Immune;
	bool           Voxel;
	bool           NewTheater;
	bool           HasRadialIndicator;
	bool           IgnoresFirestorm;
	bool           UseLineTrail;
	ColorStruct LineTrailColor;
	BYTE           unused_23E;
	BYTE           unused_23F;
	int            LineTrailColorDecrement;

	SomeVoxelCache VoxelCaches [4]; //These don't even seem to be of any use...
};

#endif
