/*!*****************************************************************************
 * \file          ImportExport.h
 * \author        Elton Teo Zhe Wei
 * \par DP email: e.teo@digipen.edu
 * \par Course:   CSD3400
 * \par Section:  A
 * \date          01/10/2023
 * \brief         DLL_API macro for exporting classes and functions as a DLL
 *******************************************************************************/
#pragma once
#ifndef DLL_API
#   if defined DLL_API_EXPORT
#       define DLL_API __declspec(dllexport)
#   else
#       define DLL_API __declspec(dllimport)
#   endif
#endif

//#include "ecs/ecs.h"
//DLL_API TDS::ECS ecs;