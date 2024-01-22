#pragma once
#include "dotnet/ImportExport.h"

class DLL_API InputListener
{
public:
	InputListener()
	{
	}
	~InputListener()
	{
	}

	//KEYBOARD pure virtual callback functions 
	virtual void onKeyPressed(int key) = 0;
	virtual void onKeyDown(int key) = 0;
	virtual void onKeyUp(int key) = 0;
};