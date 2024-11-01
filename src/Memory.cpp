///----------------------------------------------------------------------------------------------------
/// Copyright (c) Raidcore.GG - All rights reserved.
///
/// Name         :  Memory.cpp
/// Description  :  Contains functions for memory related operations.
/// Authors      :  K. Bieniek
///----------------------------------------------------------------------------------------------------

#include "Memory.h"

bool CMemoryPattern::empty() const
{
	return !this->Size;
}

size_t CMemoryPattern::size() const
{
	return this->Size;
}

bool CMemoryPattern::match(PBYTE aData, size_t aSize) const
{
	if (aSize < this->Size) { return false; }

	for (size_t i = 0; i < this->Size; i++)
	{
		if (!this->Data[i].IsWildcard && this->Data[i].Value != aData[i])
		{
			return false;
		}
	}

	return true;
}

namespace Memory
{
	void* Scan(CMemoryPattern aPattern)
	{
		if (aPattern.empty()) { return nullptr; }

		PBYTE addr = 0;
		MEMORY_BASIC_INFORMATION mbi;

		while (VirtualQuery(addr, &mbi, sizeof(mbi)))
		{
			addr += mbi.RegionSize;

			if (mbi.RegionSize < aPattern.size() ||
				mbi.State != MEM_COMMIT ||
				!(mbi.Protect == PAGE_EXECUTE_READ || mbi.Protect == PAGE_EXECUTE_READWRITE))
			{
				continue;
			}

			PBYTE base = (PBYTE)mbi.BaseAddress;
			size_t end = mbi.RegionSize - aPattern.size();

			for (size_t i = 0; i < end; ++i)
			{
				bool match = aPattern.match(&base[i], aPattern.size());

				if (match)
				{
					return base + i;
				}
			}
		}

		return nullptr;
	}

	void* ScanFollow(CMemoryPattern aPattern, int aOffset)
	{
		void* addr = Scan(aPattern);

		if (addr == nullptr)
		{
			return 0;
		}

		return FollowRelativeAddress((PBYTE)addr + aOffset);
	}

	void* FollowRelativeAddress(void* aAddress)
	{
		int jmpOffset = *(int*)aAddress;

		return (PBYTE)aAddress + jmpOffset + 4;
	}

	PBYTE FollowJmpChain(PBYTE aPointer)
	{
		while (true)
		{
			if (aPointer[0] == 0xE9)
			{
				/* near jmp */
				/* address is relative to after jmp */
				aPointer += 5 + *(__unaligned signed int*)&aPointer[1]; // jmp +imm32
			}
			else if (aPointer[0] == 0xFF && aPointer[1] == 0x25)
			{
				/* far jmp */
				/* x64: address is relative to after jmp */
				/* x86: absolute address can be read directly */
#ifdef _WIN64
				aPointer += 6 + *(__unaligned signed int*)&aPointer[2]; // jmp [+imm32]
#else
				aPointer = *(__unaligned signed int*)&aPointer[2]; // jmp [imm32]
#endif
				/* dereference to get the actual target address */
				aPointer = *(__unaligned PBYTE*)aPointer;
			}
			else
			{
				break;
			}
		}

		return aPointer;
	}
}
