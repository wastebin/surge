#include <cstdlib>
#include <iostream>

#include <SDL2/SDL.h>

#include "eng_errs.hh"
#include "eng_opts.hh"
#include "eng_state.hh"
#include "eng_update.hh"
#include "eng_render.hh"

#include "eng_main.hh"

#include "overload.hh"

void eng::main(eng::opts& opts) {
	if (SDL_Init(0) < 0) throw (eng::err::comp) {
		opts.invoc, "couldn’t init SDL", SDL_GetError()
	};

	auto window = SDL_CreateWindow(
		"Surge",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		640, 480,
		SDL_WINDOW_HIDDEN
	);

	if (!window) throw (eng::err::comp) {
		opts.invoc, "couldn’t create SDL window", SDL_GetError()
	};

	auto display = SDL_GetWindowDisplayIndex(window);

	auto res = std::visit(overload {
		[](vid::reses::none) {
			return vid::reses::spec { 800, 600 };
		},
		[](vid::reses::spec spec) {
			return spec;
		},
		[display](vid::reses::autores) {
			SDL_DisplayMode dm;
			SDL_GetDesktopDisplayMode(display, &dm);
			return vid::reses::spec { dm.w, dm.h };
		}
	}, opts.res);

	SDL_SetWindowSize(window, res.w, res.h);

	std::visit(overload {
		[window](vid::modes::fullscreen) {
			SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
		},
		[window](vid::modes::windowed) {
			SDL_SetWindowPosition(
				window,
				SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
			);
		},
		[window](vid::modes::none) {
			std::cout << "fuck if i know /shruggie" << std::endl;
		}
	}, opts.mode);

	SDL_ShowWindow(window);

	auto surface = SDL_GetWindowSurface(window);

	eng::state st = {0};

	const unsigned int tps = 25;
	const unsigned int upd_time = 1000 / tps;

	unsigned int next_upd = SDL_GetTicks() + upd_time;

	while (!st.exit_req) {
		while (SDL_GetTicks() > next_upd) {
			eng::update(upd_time, st);
			next_upd += upd_time;
		}
		const float lerp =
			(float) (SDL_GetTicks() + upd_time - next_upd) / (float) upd_time;
		eng::render(window, surface, lerp, st);
	}
}
