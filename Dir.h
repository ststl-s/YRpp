#pragma once

enum class DirType : unsigned char;

// North -> 0x0000
// South -> 0x8000
// ...
// Just a very simple BAM
struct DirStruct
{
public:
	explicit DirStruct() noexcept : Raw { 0 } { }
	explicit DirStruct(int raw) noexcept : Raw { static_cast<unsigned short>(raw) } { }
	explicit DirStruct(const DirType dir) noexcept { Set_Dir(dir); }
	explicit DirStruct(const noinit_t& noinit) noexcept { }

	bool operator==(const DirStruct& another) const
	{
		return Raw == another.Raw;
	}
	bool operator!=(const DirStruct& another) const
	{
		return !(*this == another);
	}

	void Set_Dir(DirType dir)
	{
		Raw = static_cast<unsigned short>(static_cast<unsigned char>(dir) * 256);
	}

	DirType Get_Dir() const
	{
		return static_cast<DirType>(Raw / 256);
	}

	// If you want to divide it into 32 facings, as 32 has 5 bits
	// then you should type <5> here.
	// So does the others.
	template<size_t Bits>
	unsigned int Value(size_t offset = 0) const
	{
		return TranslateFixedPoint<16, Bits>(Raw, offset);
	}

	template<size_t Bits>
	void Value(size_t value, size_t offset = 0) const
	{
		Raw = static_cast<unsigned short>(TranslateFixedPoint<Bits, 16>(value, offset));
	}

private:
	template<size_t BitsFrom, size_t BitsTo>
	constexpr static unsigned int TranslateFixedPoint(size_t value, size_t offset = 0)
	{
		constexpr size_t MaskIn = ((1u << BitsFrom) - 1);
		constexpr size_t MaskOut = ((1u << BitsTo) - 1);

		if constexpr (BitsFrom > BitsTo)
			return (((((value & MaskIn) >> (BitsFrom - BitsTo - 1)) + 1) >> 1) + offset) & MaskOut;
		else if constexpr (BitsFrom < BitsTo)
			return (((value - offset) & MaskIn) << (BitsTo - BitsFrom)) & MaskOut;
		else
			return value & MaskOut;
	}

public:
	unsigned short Raw;
private:
	unsigned short Padding;
};

static_assert(sizeof(DirStruct) == 4);
