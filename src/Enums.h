///----------------------------------------------------------------------------------------------------
/// Copyright (c) Raidcore.GG - All rights reserved.
///
/// Name         :  Enums.h
/// Description  :  Contains functions for enums.
/// Authors      :  K. Bieniek
///----------------------------------------------------------------------------------------------------

#ifndef ENUMS_H
#define ENUMS_H

#include <type_traits>

///----------------------------------------------------------------------------------------------------
/// Enum Namespace
///----------------------------------------------------------------------------------------------------
namespace Enum
{
	///----------------------------------------------------------------------------------------------------
	/// HasFlag:
	/// 	Returns true if the enum has the passed flag set.
	///----------------------------------------------------------------------------------------------------
	template <typename T>
	bool HasFlag(const T& aEnum, T aFlag)
	{
		return static_cast<T>(
			std::underlying_type_t<T>(aEnum) &
			std::underlying_type_t<T>(aFlag)
			);
	}

	///----------------------------------------------------------------------------------------------------
	/// SetFlag:
	/// 	Sets the flag on the enum.
	///----------------------------------------------------------------------------------------------------
	template <typename T>
	void SetFlag(T& aEnum, T aFlag)
	{
		return static_cast<T>(
			std::underlying_type_t<T>(aEnum) |
			std::underlying_type_t<T>(aFlag)
			);
	}

	///----------------------------------------------------------------------------------------------------
	/// RemoveFlag:
	/// 	Removes the flag from the enum.
	///----------------------------------------------------------------------------------------------------
	template <typename T>
	void RemoveFlag(T& aEnum, T aFlag)
	{
		return static_cast<T>(
			std::underlying_type_t<T>(aEnum) &
			~std::underlying_type_t<T>(aFlag)
			);
	}
}

#endif
