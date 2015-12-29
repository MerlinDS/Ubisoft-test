// ubi_soft_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <thread>
#include <iostream>
#include "InputReader.h"
#include "WorldManager.h"
/* 
* Entry point of application.
**/
int main(int argc, char* argv[])
{
	//create InputReader and read provided args
	InputReader reader;
	reader.showMessage("Application started", false);
	RES_FLAG result = reader.readUserInput(argc, argv);
	if (result == RES_FLAG::EXIT)return -1;
	//create World manager, configure it by provided config
	WorldManager wm = WorldManager(reader);
	reader.showMessage("");
	//waiting for user input
	while (true)
	{
		wm.process();//process last user input
		std::string input = "";
		std::getline(std::cin, input);
		result = reader.readUserInput(input);
		if(result == RES_FLAG::EXIT)break;//exit from programm
	}
	wm.terminate();
	reader.showMessage("Application exit", false);
    return 0;
}
