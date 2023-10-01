/*!*************************************************************************
****
\file ExceptionHandler.h
\author Cheung Jun Yin Matthew
\par DP email: j.cheung@digipen.edu
\par Course: CSD3400
\par Section: a
\par assignment: M1
\date 01-10-2023
\brief  This file implements an exception handler through a macro to
		try catch blocks to catch, native and managed code exceptions.
****************************************************************************
***/

#ifndef TDS_EXCEPTIONS
#define TDS_EXCEPTIONS

#include <stdexcept>
#include <iostream>

#define DEBUG_CALL_BEGIN try{
#define DEBUG_CALL_END														\
}																			\
catch (const std::exception& e)												\
{																			\
	std::cout << "Native Exception: " << e.what() << std::endl;				\
}																			\
catch (System::Exception^ e)												\
{																			\
	System::Console::WriteLine("Managed Exeception" + e->Message);			\
}																			\
catch(...)																	\
{																			\
	System::Console::WriteLine("Unknown exception caught.");				\
}

#endif