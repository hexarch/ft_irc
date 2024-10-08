#include "Bot.hpp"
#include "Exception.hpp"
#include "Utils.hpp"
#include "TextEngine.hpp"
#include "Define.hpp"
#include <signal.h>
#include <stdlib.h>

Bot	*botInstance = NULL;
volatile sig_atomic_t sigint = 0;
void	signalHandler(int signum){
	sigint = 1;
	std::cout << "\rCaught signal " << signum << std::endl;
	if (signum == SIGINT || signum == SIGTERM)
	{
		if (botInstance){
			delete botInstance;
			botInstance = NULL;
		}
		exit(0);
	}
}

int main(int ac, char **av)
{
	try {
		if (ac != 3){
			throw Exception(BOT_USAGE);
		}
		Bot	*bot = new Bot(av[1], av[2]);
		botInstance = bot;
		signal(SIGTERM, signalHandler);
		signal(SIGINT, signalHandler);
		bot->run();
	} catch (Exception &e) {
		TextEngine::red(e.what(), cout) << endl;
	}
	return 0;
}
