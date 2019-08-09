#pragma once

#include "grammar.hh"
#include "vid.hh"

namespace eng {
	struct opts;
}

struct eng::opts {
	opts(int, char **);

	char *invoc;

	vid::mode mode;
	vid::res res;

	struct err;
};

struct eng::opts::err {
	struct dup;
	struct malformed;
	struct missing;
	struct incompat;
	struct unknown;
	struct plain;
};

struct eng::opts::err::dup {
	char **argv;
	int i;

	char const *thing;
};
struct eng::opts::err::malformed {
	char **argv;
	int i;

	char const *form;
};
struct eng::opts::err::missing {
	char **argv;
	int i;

	char const *thing;
	char const *form;
};
struct eng::opts::err::incompat {
	char **argv;
	int i;

	char const *thing_a;
	grammar::num num;
	char const *thing_b;
};
struct eng::opts::err::unknown {
	char **argv;
  int i;
};
struct eng::opts::err::plain {
	char **argv;
  int i;
};
