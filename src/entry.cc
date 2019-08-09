#include <cstdlib>
#include <iostream>

#include "eng_errs.hh"
#include "eng_main.hh"
#include "eng_opts.hh"

int main(int argc, char **argv) {
	try {
		eng::opts opts(argc, argv);

		eng::main(opts);

		exit(EXIT_SUCCESS);
	} catch (eng::err::comp comp) {
		std::cerr << comp.invoc << ": "
		          << comp.desc << ": " << comp.msg << std::endl;
	} catch (eng::opts::err::dup dup) {
		std::cerr << *dup.argv << ": forbidden duplicate "
		          << dup.thing << " " << dup.argv[dup.i] << "." << std::endl;
	} catch (eng::opts::err::malformed mf) {
		std::cerr << *mf.argv << ": "
		          << mf.argv[mf.i - 1] << " argument " << mf.argv[mf.i]
		          << " is not of form " << mf.form << "." << std::endl;
	} catch (eng::opts::err::missing miss) {
		std::cerr << *miss.argv << ": missing " << miss.thing
		          << " (" << miss.form << ") for option " << miss.argv[miss.i]
							<< "." << std::endl;
	} catch (eng::opts::err::incompat inc) {
		std::cerr << *inc.argv << ": " << inc.thing_a
		          << " " << (inc.num == grammar::num::pl ? "are" : "is")
							<< " incompatible with " << inc.thing_b << std::endl;
	} catch (eng::opts::err::unknown unk) {
		std::cerr << *unk.argv << ": unknown option " << unk.argv[unk.i]
		          << "." << std::endl;
	} catch (eng::opts::err::plain pl) {
		std::cerr << *pl.argv << ": unexpected argument " << pl.argv[pl.i]
		          << "." << std::endl;
	}

	exit(EXIT_FAILURE);
}
