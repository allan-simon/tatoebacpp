#ifndef CONTROLLERS_CONTROLLER_H
#define CONTROLLERS_CONTROLLER_H

#include <cppcms/json.h>
#include <cppcms/application.h>
#include <cppcms/url_dispatcher.h>

#include "contents/content.h"

namespace apps {
class Tatoeba;
}
namespace controllers {

class Controller : public cppcms::application {
	protected:
		contents::ConfigContent configContent;
		apps::Tatoeba &tatoapp;
		int i;
        void initContent(contents::BaseContent& content);
	public:
		Controller(apps::Tatoeba &tatoapp);
};

} // End namespace

#endif
