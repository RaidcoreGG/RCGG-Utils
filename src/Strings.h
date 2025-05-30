///----------------------------------------------------------------------------------------------------
/// Copyright (c) Raidcore.GG - All rights reserved.
///
/// Name         :  Strings.h
/// Description  :  Contains a variety of string utility.
/// Authors      :  K. Bieniek
///----------------------------------------------------------------------------------------------------

#ifndef STRINGS_H
#define STRINGS_H

#include <string>
#include <vector>
#include <windows.h>

///----------------------------------------------------------------------------------------------------
/// String Namespace
///----------------------------------------------------------------------------------------------------
namespace String
{
	///----------------------------------------------------------------------------------------------------
	/// Replace:
	/// 	Replaces a given sequence from a string and returns the new string.
	///----------------------------------------------------------------------------------------------------
	std::string Replace(const std::string& aString, const std::string& aOld, const std::string& aNew, size_t aPosition = 0);

	///----------------------------------------------------------------------------------------------------
	/// Contains:
	/// 	Returns true if the string contains a given substring.
	///----------------------------------------------------------------------------------------------------
	bool Contains(const std::string& aString, const std::string& aStringFind);

	///----------------------------------------------------------------------------------------------------
	/// Split:
	/// 	Splits a string into parts.
	///----------------------------------------------------------------------------------------------------
	std::vector<std::string> Split(const std::string& aString, const std::string& aDelimiter, bool aKeepDelimiters = false);

	///----------------------------------------------------------------------------------------------------
	/// StartsWith:
	/// 	Returns true if a string starts with a given sequence.
	///----------------------------------------------------------------------------------------------------
	bool StartsWith(std::string aString, const std::string& aStringFind);

	///----------------------------------------------------------------------------------------------------
	/// EndsWith:
	/// 	Returns true if a string ends with a given sequence.
	///----------------------------------------------------------------------------------------------------
	bool EndsWith(std::string aString, const std::string& aStringFind);

	///----------------------------------------------------------------------------------------------------
	/// Format:
	/// 	Returns a string in printf-style format.
	///----------------------------------------------------------------------------------------------------
	std::string Format(std::string aFmt, ...);

	///----------------------------------------------------------------------------------------------------
	/// FormatByteSize:
	/// 	Formats a given size of bytes to a display string.
	///----------------------------------------------------------------------------------------------------
	std::string FormatByteSize(size_t aSize);

	///----------------------------------------------------------------------------------------------------
	/// FormatNumber:
	/// 	Formats a number display string.
	///----------------------------------------------------------------------------------------------------
	std::string FormatNumber(int aNumber, char aSeparator);

	///----------------------------------------------------------------------------------------------------
	/// FormatNumberDenominated:
	/// 	Formats a number display string with a denomination.
	///----------------------------------------------------------------------------------------------------
	std::string FormatNumberDenominated(float aNumber);

	///----------------------------------------------------------------------------------------------------
	/// Normalize:
	/// 	Returns a normalized string.
	///----------------------------------------------------------------------------------------------------
	std::string Normalize(const std::string& aString);

	///----------------------------------------------------------------------------------------------------
	/// ToLower:
	/// 	Returns a lowercase version of the passed string.
	///----------------------------------------------------------------------------------------------------
	std::string ToLower(std::string aString);

	///----------------------------------------------------------------------------------------------------
	/// ToUpper:
	/// 	Returns a uppercase version of the passed string.
	///----------------------------------------------------------------------------------------------------
	std::string ToUpper(std::string aString);

	///----------------------------------------------------------------------------------------------------
	/// ToString:
	/// 	Converts a wstring into a string.
	///----------------------------------------------------------------------------------------------------
	std::string ToString(const std::wstring& aString, UINT aCodePage = CP_UTF8);

	///----------------------------------------------------------------------------------------------------
	/// ToWString:
	/// 	Converts a string into a wstring.
	///----------------------------------------------------------------------------------------------------
	std::wstring ToWString(const std::string& aString, UINT aCodePage = CP_UTF8);

	///----------------------------------------------------------------------------------------------------
	/// ConvertMBToUTF8:
	/// 	Converts a multibyte string to UTF-8.
	///----------------------------------------------------------------------------------------------------
	std::string ConvertMBToUTF8(std::string aString);
}

#endif
