#include "src/Game.h"
#include <iostream>

int main()
{
	try
	{
		Game().Run(); // Start the game.
	}
	catch (const std::exception& e)
	{
		std::cerr << "EXCEPTION: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}