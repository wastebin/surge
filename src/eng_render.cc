#include <SDL2/SDL.h>

#include "eng_state.hh"

#include "eng_render.hh"

void eng::render(SDL_Window *window, SDL_Surface *surface, float ms, eng::state &st) {
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
	SDL_UpdateWindowSurface(window);
}
