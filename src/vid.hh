#pragma once

#ifndef _VID_HH
#define _VID_HH

#include <variant>

namespace vid {
	namespace reses {
		struct none;
		struct autores;
		struct spec;
	}
	using res = std::variant<
		vid::reses::none, vid::reses::autores, vid::reses::spec
	>;
	namespace modes {
		struct none;
		struct windowed;
		struct fullscreen;
	}
	using mode = std::variant<
		vid::modes::none, vid::modes::windowed, vid::modes::fullscreen
	>;
}

struct vid::reses::none {};
struct vid::reses::autores {};
struct vid::reses::spec { int w; int h; };

struct vid::modes::none {};
struct vid::modes::windowed {};
struct vid::modes::fullscreen {};

#endif
