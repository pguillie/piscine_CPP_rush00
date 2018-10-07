#include "Game.hpp"
#include <csignal>
#include <stdlib.h>

int g_sig = 0;

void resizeHandler(int sig)
{
	g_sig = sig;
}

int main(void)
{
	Game g;

	std::signal(SIGWINCH, resizeHandler);
	g.Run();
	return 0;
}
