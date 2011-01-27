#ifndef CONTROLLERS_PAGES_H
#define CONTROLLERS_PAGES_H

#include "Controller.h"

namespace controllers {

class Pages : public Controller {
	public:
		Pages(apps::Tatoeba& tatoapp);
		void homepage();
		void contribute();
		 void termsOfUse();
		 void teamAndCredits();
};

} // End namespace

#endif
