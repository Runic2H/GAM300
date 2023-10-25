/*!*************************************************************************
****
\file winData.cpp
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program defines the functions in the WinData component class
****************************************************************************
***/

#include "components/winData.h"

RTTR_REGISTRATION
{
	using namespace TDS;

	rttr::registration::class_<WinData>("Win Data");
}

namespace TDS
{
	/*!*************************************************************************
	Initializes the WinData component when created
	****************************************************************************/
	WinData::WinData() : mTitle				("Disinheritance"),
						 mWidth				(1920),
						 mHeight			(1080),
						 mCurrentWidth		(1920),
						 mCurrentHeight		(1080),
						 mMasterVolume		(1.0f),
						 mBGMVolume			(1.0f),
						 mSFXVolume			(1.0f)
	{ }

	/*!*************************************************************************
	Initializes the WinData component when created, given another WinData 
	component to move (for ECS)
	****************************************************************************/
	WinData::WinData(WinData&& toMove) noexcept : mTitle			(toMove.mTitle),
												  mWidth			(toMove.mWidth),
												  mHeight			(toMove.mHeight),
												  mCurrentWidth		(toMove.mCurrentWidth),
												  mCurrentHeight	(toMove.mCurrentHeight),
												  mMasterVolume		(toMove.mMasterVolume),
												  mBGMVolume		(toMove.mBGMVolume),
												  mSFXVolume		(toMove.mSFXVolume)
	{ }
}
