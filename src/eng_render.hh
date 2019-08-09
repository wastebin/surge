#pragma once

#include <SDL2/SDL.h>

#include "eng_state.hh"

namespace eng {
	void render(SDL_Window *, SDL_Surface *, float, eng::state&);
}
