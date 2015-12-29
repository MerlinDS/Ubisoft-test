#include "stdafx.h"
#include "InputReader.h"
#include <iostream>

InputReader::InputReader() : 
	config({ 960, 640, 960 / 2, 640 - 80, 20 }){}
InputReader::~InputReader() {
	requests.clear();
}

RES_FLAG InputReader::readUserInput(int argc, char* argv[])
{
	DebugOut("readUserInput: Client configutation");
	for (int i = 1; i < argc; i++)
	{
		char* arg = argv[i];
		if (arg[0] == '-')
		{
			//command was found
			if (i + 1 >= argc)break;
			switch (arg[1])
			{
				case WIDTH_PREF:
					config.width = atoi(argv[i + 1]);
					config.x = config.width / 2;
					break;
				case HEIGHT_PREF:
					config.height = atoi(argv[i + 1]);
					config.y = config.height - 80;
					break;
				case SCALE_PREF:
					config.scale = (float)atof(argv[i + 1]);
					break;
				default:
					break;
			}
		}
	}
	showMessage("Client config: width = " + std::to_string(config.width)
		+ ", height = " + std::to_string(config.height) 
		+ ", scale = " + std::to_string(config.scale), false);
	return NONE;
}

const ClientConfig& InputReader::getConfig()
{
	return config;
}

RES_FLAG InputReader::readUserInput(std::string input)
{
	RES_FLAG result = NONE;
	if (input == EXIT_CMD)
	{
		showMessage("Close application", false);
		result = EXIT;
	}
	else if (input == HELP_CMD)
		showHelp();
	else
	{
		std::istringstream iss(input);
		std::string command, param, value;
		iss >> command;
		if (command == CREATE_CMD)
		{
			UserRequest request = { 0.0, 0.0, 0.0 };
			while (iss)
			{
				iss >> param >> value;
				if (param == VELOCITY_PREF)
					request.v = stof(value);
				else if(param == ANGLE_PREF)
					request.a = stof(value);
				else if (param == MASS_PREF)
					request.m = stof(value);
			}
			requests.push_back(request);
			result = READ;
		}
		else
		{
			showMessage("Unknown command! Type --h to see help");
		}
	}
	return result;
}

bool InputReader::hasRequest()
{
	return requests.size() > 0;
}

UserRequest InputReader::popRequest()
{
	auto request = requests.back();
	requests.pop_back();
	return request;
}

void InputReader::showHelp()
{
	DebugOut("Show help");
	std::cout << std::endl << "help: " << std::endl << std::endl;
	std::cout << "exit - exit from programm " << std::endl;
	std::cout << "create [options] - create projectile, add it to simulation." << std::endl;
	std::cout << "		-v - projectile velocity value" << std::endl;
	std::cout << "		-a - projectile angle value in degrees" << std::endl;
	std::cout << "		-m - projectile mass value" << std::endl;
	std::cout << "help - show help" << std::endl << std::endl;
	std::cout << "execute command: ";
}

void InputReader::showMessage(std::string text)
{
	showMessage(text, true);
}

void InputReader::showMessage(std::string text, bool c)
{
	std::cout << std::endl << text << std::endl;
	DebugOut() << text;
	if(c)std::cout << "execute command: ";
}