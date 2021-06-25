/*
	Drawing related static class.
	This provides access to the game's Surfaces, color value conversion
	and text aligning helpers.
*/

#pragma once

#include <GeneralDefinitions.h>
#include "ColorScheme.h"
#include <Surface.h>

#include <Helpers/CompileTime.h>

struct DirtyAreaStruct
{
	RectangleStruct Rect;
	bool alphabool10;

	bool operator==(const DirtyAreaStruct& another) const { 
		return
			Rect.X == another.Rect.X &&
			Rect.Y == another.Rect.Y &&
			Rect.Width == another.Rect.Width &&
			Rect.Height == another.Rect.Height &&
			alphabool10 == another.alphabool10;
	};
};

class Drawing
{
public:
	constexpr static reference<DynamicVectorClass<DirtyAreaStruct>, 0xB0CE78> DirtyAreas{};
	constexpr static reference<RectangleStruct, 0x886FA0> SurfaceDimensions_Hidden {};
	constexpr static reference<ColorStruct, 0xB0FA1C> TooltipColor {};

	//TextBox dimensions for tooltip-style boxes
	static RectangleStruct GetTextBox(const wchar_t* pText, int nX, int nY, DWORD flags, int nMarginX, int nMarginY)
		{
			RectangleStruct box;
			RectangleStruct* p_box=&box;

			PUSH_VAR32(nMarginY);		//X Margin
			PUSH_VAR32(nMarginX);		//Y Margin - should add 2, because X margin adds to 2 internally!
			PUSH_VAR32(flags);
			PUSH_VAR32(nY);
			PUSH_VAR32(nX);
			SET_REG32(edx,pText);
			SET_REG32(ecx,p_box);
			CALL(0x4A59E0);

			return box;
		}

	static RectangleStruct GetTextBox(const wchar_t* pText, int nX, int nY, int nMargin)
		{ return GetTextBox(pText, nX, nY, 0, nMargin + 2, nMargin); }

	static RectangleStruct GetTextBox(const wchar_t* pText, int nX, int nY)
		{ return GetTextBox(pText, nX, nY, 2); }

	static RectangleStruct GetTextBox(const wchar_t* pText, Point2D* pPoint)
		{ return GetTextBox(pText, pPoint->X, pPoint->Y, 2); }

	static RectangleStruct GetTextBox(const wchar_t* pText, Point2D* pPoint, int nMargin)
		{ return GetTextBox(pText, pPoint->X, pPoint->Y, nMargin); }

	//TextDimensions for text aligning
	static RectangleStruct GetTextDimensions(const wchar_t* pText)
		{
			RectangleStruct dim=GetTextBox(pText,0,0,0);

			dim.X=0;
			dim.Y=0;
			dim.Width-=4;
			dim.Height-=2;

			return dim;
		}

	// Rectangles
	static RectangleStruct Intersect(RectangleStruct* rect1, RectangleStruct* rect2, int* delta_left, int* delta_top)
	{
			RectangleStruct box;
			RectangleStruct* p_box=&box;

			PUSH_VAR32(delta_top);
			PUSH_VAR32(delta_left);
			PUSH_VAR32(rect2);
			SET_REG32(edx,rect1);
			SET_REG32(ecx,p_box);
			CALL(0x421B60);

			return box;
	}

	//Stuff

	// Converts an RGB color to a 16bit color value.
	static WORD Color16bit(const ColorStruct& color) {
		return static_cast<WORD>((color.B >> 3) | ((color.G >> 2) << 5) | ((color.R >> 3) << 11));
	}

    static DWORD __fastcall RGB2DWORD(int red, int green, int blue)
        { JMP_STD(0x4355D0); }

    static DWORD RGB2DWORD(const ColorStruct Color) {
        return RGB2DWORD(Color.R, Color.G, Color.B);
    }

	// Converts a 16bit color to an RGB color.
	static ColorStruct WordColor(WORD bits) {
		ColorStruct color;
		color.R = static_cast<BYTE>(((bits & 0xF800) >> 11) << 3);
		color.G = static_cast<BYTE>(((bits & 0x07E0) >> 5) << 2);
		color.B = static_cast<BYTE>((bits & 0x001F) << 3);
		return color;
	}
};

//A few preset 16bit colors.
#define		COLOR_BLACK  0x0000
#define		COLOR_WHITE  0xFFFF

#define		COLOR_RED    0xF800
#define		COLOR_GREEN  0x07E0
#define		COLOR_BLUE   0x001F

#define		COLOR_PURPLE (COLOR_RED | COLOR_BLUE)

class NOVTABLE ABuffer
{
public:
	static constexpr reference<ABuffer*, 0x87E8A4> Instance {};

	ABuffer(RectangleStruct Rect) { JMP_THIS(0x410CE0); }
	bool BlitTo(Surface* pSurface, int X, int Y, int Offset, int Size) { JMP_THIS(0x410DC0); }
	void ReleaseSurface() { JMP_THIS(0x410E50); }
	void Blitter(unsigned short* Data, int Length, unsigned short Value) { JMP_THIS(0x410E70); }
	void BlitAt(int X, int Y, COLORREF Color) { JMP_THIS(0x410ED0); }
	bool Fill(unsigned short Color) { JMP_THIS(0x4112D0); }
	bool FillRect(unsigned short Color, RectangleStruct Rect) { JMP_THIS(0x411310); }
	void BlitRect(RectangleStruct Rect) { JMP_THIS(0x411330); }
	void* GetBuffer(int X, int Y) { JMP_THIS(0x4114B0); }

	RectangleStruct Bounds;
	int BufferPosition;
	BSurface* Surface;
	int BufferHead;
	int BufferTail;
	int BufferSize;
	int MaxValue;
	int Width;
	int Height;
};

class NOVTABLE ZBuffer
{
public:
	static constexpr reference<ZBuffer*, 0x887644> Instance {};

	ZBuffer(RectangleStruct Rect) { JMP_THIS(0x7BC970); }
	bool BlitTo(Surface* pSurface, int X, int Y, int Offset, int Size) { JMP_THIS(0x7BCA50); }
	void ReleaseSurface() { JMP_THIS(0x7BCAE0); }
	void Blitter(unsigned short* Data, int Length, unsigned short Value) { JMP_THIS(0x7BCAF0); }
	void BlitAt(int X, int Y, COLORREF Color) { JMP_THIS(0x7BCB50); }
	bool Fill(unsigned short Color) { JMP_THIS(0x7BCF50); }
	bool FillRect(unsigned short Color, RectangleStruct Rect) { JMP_THIS(0x7BCF90); }
	void BlitRect(RectangleStruct Rect) { JMP_THIS(0x7BCFB0); }
	void* GetBuffer(int X, int Y) { JMP_THIS(0x7BD130); }

	RectangleStruct Bounds;
	int BufferOffset;
	BSurface* Surface;
	int BufferHead;
	int BufferTail;
	int BufferSize;
	int MaxValue;
	int Width;
	int Height;
};