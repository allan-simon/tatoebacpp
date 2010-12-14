#ifndef CONTROLLERS_CONTROLLER_H
#define CONTROLLERS_CONTROLLER_H

#include <cppcms/json.h>
#include <cppcms/application.h>
#include <cppcms/url_dispatcher.h>

#include "contents/content.h"

namespace apps {
class tatoeba;
}
namespace controllers {

class Controller : public cppcms::application {
	protected:
		contents::ConfigContent configContent;
		apps::tatoeba &tatoapp;
		int i;
        void initContent(contents::BaseContent& content);
	public:
		Controller(apps::tatoeba &tatoapp);
};

} // End namespace

#endif
