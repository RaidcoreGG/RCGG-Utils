///----------------------------------------------------------------------------------------------------
/// Copyright (c) Raidcore.GG - All rights reserved.
///
/// Name         :  CmdLine.h
/// Description  :  Contains functions for the commandline.
/// Authors      :  K. Bieniek
///----------------------------------------------------------------------------------------------------

#ifndef CMDLINE_H
#define CMDLINE_H

#pragma comment(lib, "Shell32.lib")

#include <string>
#include <vector>
#include <Windows.h>

///----------------------------------------------------------------------------------------------------
/// CmdLine Namespace
///----------------------------------------------------------------------------------------------------
namespace CmdLine
{
	///----------------------------------------------------------------------------------------------------
	/// HasArgument:
	/// 	Returns true if the commandline contains the given argument.
	///----------------------------------------------------------------------------------------------------
	bool HasArgument(const std::string& aArgument);

	///----------------------------------------------------------------------------------------------------
	/// GetArgumentValue:
	/// 	Returns the value following the given argument.
	///----------------------------------------------------------------------------------------------------
	std::string GetArgumentValue(const std::string& aArgument);

	///----------------------------------------------------------------------------------------------------
	/// Parse:
	/// 	Returns all the arguments.
	///----------------------------------------------------------------------------------------------------
	std::vector<std::string> Parse();
}

#endif
