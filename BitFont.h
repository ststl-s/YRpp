#pragma once

#include <YRPP.h>

class NOVTABLE BitFont
{
public:
	static constexpr reference<BitFont*, 0x89C4D0> Instance {};

private:
	BitFont(const char* pFileName) { JMP_THIS(0x433880); }
public:
	virtual ~BitFont() RX;

	bool GetTextDimension(const wchar_t* pText, int& Width, int& Height, int nMaxWidth) { JMP_THIS(0x433CF0); }

	void SetBounds(RectangleStruct* pRect)
	{
		// JMP_THIS(0x433CA0);
		if (pRect)
		{
			this->Bounds = *pRect;
		}
		else
		{
			this->Bounds.X = 0;
			this->Bounds.Y = 0;
			this->Bounds.Width = 0;
			this->Bounds.Height = 0;
		}
	}
	void SetColor(WORD nColor)
	{ 
		this->Color = nColor; 
	}
	
	void SetField41(char flag) 
	{ 
		this->field_41 = flag;
	}

	/// Properties
	struct InternalData
	{
		int FontWidth;
		int Stride;
		int FontHeight;
		int Lines;
		int Count;
		int SymbolDataSize;
		short* SymbolTable;
		char* Bitmaps;
		int ValidSymbolCount;
	};

	static InternalData* __fastcall LoadInternalData(const char* pFileName)
		{ JMP_STD(0x433990); }

	InternalData* InternalPTR;
	void* Pointer_8;
	short* pGraphBuffer;
	int PitchDiv2;
	int Unknown_14;
	wchar_t* field_18;
	int field_1C;
	int field_20;
	WORD Color;
	short DefaultColor2;
	int Unknown_28;
	int State_2C;
	RectangleStruct Bounds;
	bool Bool_40;
	bool field_41;
	bool field_42;
	bool field_43;
};