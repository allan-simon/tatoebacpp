#ifndef CONTROLLERS_USERS_H
#define CONTROLLERS_USERS_H

#include "Controller.h"

namespace controllers {

class Users : public Controller {
	public:
		Users(apps::tatoeba& tatoapp);
		void check_login();
        void logout();
};

} // End namespace

#endif
