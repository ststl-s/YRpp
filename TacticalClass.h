#pragma once

#include <GeneralDefinitions.h>
#include <GeneralStructures.h>
#include <AbstractClass.h>
#include <ColorScheme.h>
#include <CellClass.h>

struct TacticalSelectableStruct
{
	TechnoClass* Techno;
	int X;
	int Y;
};

class NOVTABLE TacticalClass : public AbstractClass
{
public:
	static TacticalClass* Global()
		{ return *reinterpret_cast<TacticalClass**>(0x887324); }

	static TacticalClass * &Instance;

	Point2D* CoordsToClient(CoordStruct* pCoords, Point2D* pDest)
		{ JMP_THIS(0x6D2140); }
	/*
	static Point2D* CoordsToClient(CoordStruct* pCrd, Point2D* pPoint)
	{
		void* pTactical;
		MEM_READ32(pTactical, TACTICAL_MAP_PTR);
		PUSH_VAR32(pPoint);
		PUSH_VAR32(pCrd);
		THISCALL_EX(pTactical, 0x6D2140);
	}*/

	Point2D* CoordsToScreen(Point2D* pDest, CoordStruct* pSource)
		{ JMP_THIS(0x6D1F10); }

	CoordStruct* ClientToCoords(Point2D* pClient, CoordStruct* pDest)
		{ JMP_THIS(0x6D2280); }
	/*
	static CoordStruct* ClientToCoords(Point2D* pPoint, CoordStruct* pCrd)
	{
		void* pTactical;
		MEM_READ32(pTactical, TACTICAL_MAP_PTR);
		PUSH_VAR32(pPoint);
		PUSH_VAR32(pCrd);
		THISCALL_EX(pTactical, 0x6D2280);
	}*/

	char GetOcclusion(const CellStruct& cell, bool fog) const
		{ JMP_THIS(0x6D8700); }

	Point2D * AdjustForZShapeMove(Point2D* pDest, Point2D* pClient)
		{ JMP_THIS(0x6D1FE0); }

	// convert xyz height to xy height?
	static int __fastcall AdjustForZ(int Height)
		{ JMP_STD(0x6D20E0); }

	void FocusOn(CoordStruct* pDest, int Velocity)
		{ JMP_THIS(0x6D2420); }


	// called when area needs to be marked for redrawing due to external factors
	// - alpha lights, terrain changes like cliff destruction, etc
	void RegisterDirtyArea(RectangleStruct Area, bool bUnk)
		{ JMP_THIS(0x6D2790); }

	void RegisterCellAsVisible(CellClass* pCell)
		{ JMP_THIS(0x6DA7D0) };

	static int DrawTimer(int index, ColorScheme *Scheme, int Time, wchar_t *Text, Point2D *someXY1, Point2D *someXY2)
		{ JMP_STD(0x64DB50); }

public:
	__int16 __ScreenText[64];
	DWORD endgamegraphicsframeA4;
	DWORD LastAIFrame;
	bool byteAC;
	bool byteAD;
	BYTE byteAE;
	BYTE byteAF;
	Point2D TacticalPos0;
	Point2D field_B8;
	double ZoomFactor;
	Point2D point_C8;
	Point2D point_D0;
	float floatD8;
	float floatDC;
	DWORD VisibleCellCount;
	void* VisibleCells[800];
	Point2D TacticalCoord1;
	Point2D dwordD6C;
	Point2D TacticalCoord2;
	BYTE byteD7C;
	bool Redrawing; //TacticalPosUpdated;
	BYTE byteD7E;
	BYTE byteD7F;
	RectangleStruct rectD80;
	RECT Band;
	DWORD __TimerIncriment;
	TimerStruct StartTime;
	int SelectableCount;
	Matrix3DStruct unusedmatrix3d;
	Matrix3DStruct matrix3d_DE4;
	int field_E14;
};

static_assert(sizeof(TacticalClass) == 0x0E18, "Wrong size");