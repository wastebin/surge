#include <cstdio>
#include <cstring>
#include <variant>

#include "eng_opts.hh"

eng::opts::opts(int argc, char **argv)
: mode((vid::modes::none) {})
, res((vid::reses::none) {}) {
	invoc = *argv;

	for (int i = 1; i < argc; i++) {
		if (*argv[i] == '+') {
			if (!strcmp(argv[i] + 1, "res")) {
				if (++i >= argc) {
					throw (eng::opts::err::missing) {
						argv, i, "WIDTHxHEIGHT | auto"
					};
				}
				if (!std::holds_alternative<vid::reses::none>(res)) {
					throw (eng::opts::err::dup) { argv, i, "video mode" };
				}

				int w, h;
				if (!strcmp(argv[i], "auto")) {
					if (std::holds_alternative<vid::modes::windowed>(mode)) {
						throw (eng::opts::err::incompat) {
							argv, i,
							"automatic resolution", grammar::num::sg, "windowed mode"
						};
					}
					res = (vid::reses::autores) {};
				} else if (sscanf(argv[i], "%ux%u", &w, &h) == 2) {
					res = (vid::reses::spec) { w, h };
				} else {
					throw (eng::opts::err::malformed) {
						argv, i, "WIDTHxHEIGHT | auto"
					};
				}
			} else if (!strcmp(argv[i] + 1, "windowed")) {
				if (!std::holds_alternative<vid::modes::none>(mode)) {
					throw (eng::opts::err::dup) { argv, i, "mode" };
				}
				if (std::holds_alternative<vid::reses::autores>(res)) {
					throw (eng::opts::err::incompat) {
						argv, i,
						"windowed mode", grammar::num::sg, "automatic resolution"
					};
				} else mode = (vid::modes::windowed) {};
			} else if (!strcmp(argv[i] + 1, "fullscreen")) {
				if (!std::holds_alternative<vid::modes::none>(mode)) {
					throw (eng::opts::err::dup) { argv, i, "mode" };
				}
			} else {
				throw (eng::opts::err::unknown) { argv, i };
			}
		} else {
			throw (eng::opts::err::plain) { argv, i };
		}
	}

	if (std::holds_alternative<vid::reses::none>(res)) {
		res = (vid::reses::autores) {};
	}
	if (std::holds_alternative<vid::modes::none>(mode)) {
		if (std::holds_alternative<vid::reses::spec>(res)) {
			mode = (vid::modes::windowed) {};
		} else {
			mode = (vid::modes::fullscreen) {};
		}
	}
}
