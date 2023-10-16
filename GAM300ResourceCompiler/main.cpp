/*!*****************************************************************************
 * \file          main.cpp
 * \author        Eugene Ho Shu Sheng
 * \par DP email: shushengeugene.ho@digipen.edu
 * \par Course:   CSD3400
 * \par Section:  A
 * \date          01/10/2023
 * \brief         main function that runs the program
 *******************************************************************************/
#include "GeomCompiler.h"
#include "CommandParse.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	std::shared_ptr<TDS::CommandParser> parser = TDS::CommandParser::GetInstance();
	std::shared_ptr<TDS::GeomCompiler> compiler = TDS::GeomCompiler::GetInstance();

	//compiler->GetDescriptor().m_Descriptor.m_FilePath = "../assets/models/";
	//compiler->GetDescriptor().m_Descriptor.m_MeshFileName = "spider.obj";
	//compiler->GetDescriptor().Serialize("../assets/models/Test.desc", false);

	compiler->Init();

	parser->checkForCommands();

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
}