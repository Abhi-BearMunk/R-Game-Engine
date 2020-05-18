#include "TestGame.h"

int main()
{
	// Create Game
	auto game = new TestGame();
	if (!game->Init())
	{
		return -1;
	}

	// Game Loop
	while (game->GetIsRunning())
	{
		game->Update();
	}

	game->Quit();
	return 0;
}