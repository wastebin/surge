#include <SDL2/SDL.h>

#include "eng_state.hh"

#include "eng_update.hh"

void eng::update(unsigned int ms, eng::state& st) {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
			case SDL_QUIT:
				st.exit_req = true;
				break;
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym) {
					case SDLK_ESCAPE:
						st.exit_req = true;
						break;
				}
				break;
		}
	}
}
