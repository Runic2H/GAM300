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