#include <cstdlib>

#include <iostream>

#include <SDL2/SDL.h>

#define SDL_MIN_X 2
#define SDL_MIN_Y 0
#define SDL_MIN_Z 0
#define SDL_MINVER (SDL_VERSIONNUM(SDL_MIN_X, SDL_MIN_Y, SDL_MIN_Z))
#define SDL_TOONEW (SDL_VERSIONNUM(3, 0, 0))

static void init_sdl();

int main(int argc, char **argv) {
	//bool ded = check_param(argc, argv, "-d")
	//        || check_param(argc, argv, "--dedicated");

	//double old_time, new_time;

	init_sdl();

	return 0;
}

static void init_sdl() {
	SDL_version ver;

	SDL_GetVersion(&ver);

	std::cout << "Found SDL version "
	          << ver.major << "."
	          << ver.minor << "."
	          << ver.patch << "." << std::endl;

	auto ver_num = SDL_VERSIONNUM(ver.major, ver.minor, ver.patch);

	if (ver_num < SDL_MINVER) {
		std::cerr << "You need at least version "
		          << SDL_MIN_X << "."
							<< SDL_MIN_Y << "."
		          << SDL_MIN_Z << " of SDL to run me." << std::endl;
		exit(EXIT_FAILURE);
	}

	if (ver_num >= SDL_TOONEW) {
		std::cerr << "Your version of SDL is too recent for me." << std::endl
		          << "You need a version in the line of "
		          << SDL_MIN_X << "."
		          << SDL_MIN_Y << "."
		          << SDL_MIN_Z << "." << std::endl;
		exit(EXIT_FAILURE);
	}
}
