#pragma once

namespace eng {
	//namespace err;
}

namespace eng::err {
	struct comp;
}

struct eng::err::comp {
	char const *invoc;
	char const *desc;
	char const *msg;
};
