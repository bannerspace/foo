#include "MainGame.h"
#include "CommandManager.h"
#include <thread>


CommandManager *cmdManager;
MainGame mainGame;

void cmdManagerInit()
{
	cmdManager = new CommandManager();
	cmdManager->call();
}

void startGame()
{
	mainGame.startGame();
}

int main(int argc, char **argv) {

	//using 2 threads for opengl render and command manager
	std::thread mainGame_thread(startGame);
	std::thread cmd_thread(cmdManagerInit);

	if (mainGame_thread.joinable())
	{
		mainGame_thread.join();
		cmd_thread.detach();
	}
	if (cmd_thread.joinable())
		cmd_thread.join();
	

	return 0;
}