#ifndef CONTROLLERS_USERS_H
#define CONTROLLERS_USERS_H

#include "Controller.h"
#include "models/Users.h"

namespace controllers {

class Users : public Controller {
    private:
        models::Users userModel;
	public:
		Users(apps::tatoeba& tatoapp);
        void registerUser();
		void check_login();
        void logout();
};

} // End namespace

#endif
