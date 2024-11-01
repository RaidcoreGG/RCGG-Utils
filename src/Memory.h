///----------------------------------------------------------------------------------------------------
/// Copyright (c) Raidcore.GG - All rights reserved.
///
/// Name         :  Memory.h
/// Description  :  Contains functions for memory related operations.
/// Authors      :  K. Bieniek
///----------------------------------------------------------------------------------------------------

#ifndef MEMORY_H
#define MEMORY_H

#include <Windows.h>
#include <exception>

#define MAX_PATTERN_LENGTH 128
#define CHAR_0             0x30 /* ascii value for '0' */
#define CHAR_9             0x39 /* ascii value for '9' */
#define CHAR_A             0x41 /* ascii value for 'A' */
#define CHAR_F             0x46 /* ascii value for 'F' */
#define HEXVAL_A           10   /* value of hex A */
#define HEXPOW_1           0x01 /* power of the first digit */
#define HEXPOW_2           0x10 /* power of the second digit */

///----------------------------------------------------------------------------------------------------
/// PatternByte Struct
///----------------------------------------------------------------------------------------------------
struct PatternByte
{
	bool          IsWildcard = false;
	unsigned char Value = 0;
};

///----------------------------------------------------------------------------------------------------
/// CMemoryPattern Class
///----------------------------------------------------------------------------------------------------
class CMemoryPattern
{
	public:
	///----------------------------------------------------------------------------------------------------
	/// ctor
	///----------------------------------------------------------------------------------------------------
	constexpr CMemoryPattern(const char* aPattern) : Data(), Size(0)
	{
		if (!aPattern) { throw std::exception("Pattern was nullptr."); }

		size_t len = 0; /* length of the pattern string */

		this->Size = 1; /* length of the actual byte pattern */

		while (aPattern[len])
		{
			if (aPattern[len] == ' ') { this->Size++; }
			len++;
		}

		if (this->Size > MAX_PATTERN_LENGTH)
		{
			this->Size = MAX_PATTERN_LENGTH;
		}

		size_t j = 0;

		for (size_t i = 0; i < len; i++)
		{
			/* space */
			if (aPattern[i] == ' ') { continue; }

			/* wildcard */
			if (aPattern[i] == '?')
			{
				this->Data[j] = PatternByte{ true };
				j++;

				/* advance one more if '??' instead of '?' */
				if (i + 1 < len && aPattern[i + 1] == '?')
				{
					i++;
				}

				continue;
			}

			/* byte */
			if ((aPattern[i] >= CHAR_0 && aPattern[i] <= CHAR_9) || (aPattern[i] >= CHAR_A && aPattern[i] <= CHAR_F))
			{
				unsigned char val = 0;

				/* advance one more if 'FF' instead of 'F' */
				if (i + 1 < len && (aPattern[i + 1] >= CHAR_0 && aPattern[i + 1] <= CHAR_9) || (aPattern[i + 1] >= CHAR_A && aPattern[i + 1] <= CHAR_F))
				{
					if (aPattern[i] <= CHAR_9)
					{
						val += (aPattern[i] - CHAR_0) * HEXPOW_2;
					}
					else
					{
						val += ((aPattern[i] - CHAR_A) + HEXVAL_A) * HEXPOW_2;
					}

					if (aPattern[i + 1] <= CHAR_9)
					{
						val += (aPattern[i + 1] - CHAR_0) * HEXPOW_1;
					}
					else
					{
						val += ((aPattern[i + 1] - CHAR_A) + HEXVAL_A) * HEXPOW_1;
					}

					i++;
				}
				else
				{
					if (aPattern[i] <= CHAR_9)
					{
						val += (aPattern[i] - CHAR_0) * HEXPOW_1;
					}
					else
					{
						val += ((aPattern[i] - CHAR_A) + HEXVAL_A) * HEXPOW_1;
					}
				}

				this->Data[j] = PatternByte{ false, val };
				j++;

				continue;
			}
			else
			{
				throw std::exception("Invalid hexadecimal.");
			}
		}
	}

	///----------------------------------------------------------------------------------------------------
	/// empty:
	/// 	Returns true if the pattern is empty.
	///----------------------------------------------------------------------------------------------------
	bool empty() const;

	///----------------------------------------------------------------------------------------------------
	/// size:
	/// 	Returns the size in bytes of the pattern.
	///----------------------------------------------------------------------------------------------------
	size_t size() const;

	///----------------------------------------------------------------------------------------------------
	/// match:
	/// 	Returns true if the pattern matches with the bytes at passed aData parameter.
	///----------------------------------------------------------------------------------------------------
	bool match(PBYTE aData, size_t aSize) const;

	private:
	PatternByte Data[128];
	size_t      Size;
};


///----------------------------------------------------------------------------------------------------
/// Memory Namespace
///----------------------------------------------------------------------------------------------------
namespace Memory
{
	///----------------------------------------------------------------------------------------------------
	/// Scan:
	/// 	Scans for a memory pattern and returns its pointer if found.
	///----------------------------------------------------------------------------------------------------
	void* Scan(CMemoryPattern aPattern);

	///----------------------------------------------------------------------------------------------------
	/// ScanFollow:
	/// 	Scans for a memory pattern, then follows the relative address at the offset.
	///----------------------------------------------------------------------------------------------------
	void* ScanFollow(CMemoryPattern aPattern, int aOffset = 0);

	///----------------------------------------------------------------------------------------------------
	/// FollowRelativeAddress:
	/// 	Follows a relative address. (Long jmp only.)
	///----------------------------------------------------------------------------------------------------
	void* FollowRelativeAddress(void* aAddress);

	///----------------------------------------------------------------------------------------------------
	/// FollowJmpChain:
	/// 	Follows the jmp chain of a pointer to get the address at the end of it.
	///----------------------------------------------------------------------------------------------------
	PBYTE FollowJmpChain(PBYTE aPointer);
}

#endif
