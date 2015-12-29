#pragma once
#include <vector>

#define EXIT_CMD "exit"
#define HELP_CMD "help"
#define CREATE_CMD "create"

#define VELOCITY_PREF "-v"
#define ANGLE_PREF "-a"
#define MASS_PREF "-m"

#define WIDTH_PREF 'v'
#define HEIGHT_PREF 'h'
#define SCALE_PREF 's'

/*
Flags fro input results
*/
enum RES_FLAG
{
	EXIT, NONE, READ
};
/*
	Serialized client configuration.
	Provided by initial user input, or by default system parameter.
*/
struct ClientConfig {
	//width of the scree
	int width;
	//height of the scree
	int height;
	//x coordinate of the center of the simulated world
	int x;
	//y coordinate of the center of the simulated world
	int y;
	//scale of the screen (pixel * scale = meter)
	float scale;
};
/*
	Serialized user request
*/
struct UserRequest
{
	//starting velocity
	float v;
	//starting angle
	float a;
	//starting mass 
	float m;
};
/*
	User console input reader.
	Read user input and save it for future providing it to requester.
*/
class InputReader
{
public:
	/*
		Consturctor
	*/
	InputReader();
	~InputReader();
	/* Read user input from arguments and serialize it to configuration struct*/
	RES_FLAG readUserInput(int argc, char* argv[]);
	/* Read user input from console*/
	RES_FLAG readUserInput(std::string input);
	/*Reader has saved user request*/
	bool hasRequest();
	/*Provide user input to requester and remove it from queue*/
	UserRequest popRequest();
	//getter for client configuration
	const ClientConfig& getConfig();
	//Show help in console
	void showHelp();
	//Show message in console
	void showMessage(std::string);
	void showMessage(std::string, bool);
private:
	// vector of saved users request
	std::vector<UserRequest> requests;
	//client configuration
	ClientConfig config;
};

