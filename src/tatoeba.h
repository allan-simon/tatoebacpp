#ifndef TATOEBA_H
#define TATOEBA_H

#include <cppcms/application.h>
#include <cppdb/frontend.h>


#include <contents/content.h>

#include "controllers/Pages.h"
#include "controllers/Sentences.h"
#include "controllers/Users.h"



extern "C" {
#include "tato/db.h"
}

namespace content {
	class homepage;
}

namespace apps {


class tatoeba : public cppcms::application {

private:
	controllers::Pages pc;
	controllers::Sentences sc;
	controllers::Users uc;
    std::map<std::string,std::string> lang_map;

public:
    TatoDb *tatoDb;
    //cppdb::session sqliteDb;
	tatoeba(cppcms::service &w, TatoDb* db);
	void main(std::string url);
};
}
#endif
