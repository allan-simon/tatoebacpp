#ifndef TATOEBA_H
#define TATOEBA_H

#include <cppcms/application.h>
#include <contents/content.h>

#include "controllers/Pages.h"
#include "controllers/Sentences.h"
#include "controllers/Users.h"

#include "sqlite3.h"

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
    sqlite3 *sqliteDb;
	tatoeba(cppcms::service &w, TatoDb* db, sqlite3* sqliteDb);
	void main(std::string url);
};
}
#endif
