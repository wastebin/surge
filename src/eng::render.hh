#pragma once

#include <SDL2/SDL.h>

#include "eng::state.hh"

namespace eng {
	void render(SDL_Window *, SDL_Surface *, float, eng::state&);
}
