#include <tatoeba.h>
#include <contents/content.h>

#include <cppcms/json.h>
#include <cppcms/application.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/http_response.h>

#include <booster/regex.h>

#include <sqlite3.h>
#include <iostream>
namespace apps {

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  int i;
  for(i=0; i<argc; i++){
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

tatoeba::tatoeba(cppcms::service &w, TatoDb *db) : 
	cppcms::application(w),
	pc(*this),
	sc(*this),
	uc(*this),
    tatoDb(db)
    
{	
	add(pc);
	add(sc);
	add(uc);

    // Base sqlite3
    sqlite3 *sqlitedb;
    char *zErrMsg = 0;
    int rc;
    char* sql = (char*) "SELECT * FROM tbl1";

    rc = sqlite3_open("../doc/sqlite3.db", &sqlitedb);
    if (rc) {
        std::cout << "Can't open database: " << sqlite3_errmsg(sqlitedb) << std::endl;
        sqlite3_close(sqlitedb);
    }

    rc = sqlite3_exec(sqlitedb, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cout << "SQL erro: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(sqlitedb);
    

    cppcms::json::object langs = settings().at("tatoeba.languages").object();
    for(cppcms::json::object::const_iterator p=langs.begin();p!=langs.end();++p) {
        lang_map[p->first]=p->second.str();
    }
}
static const booster::regex lang_regex("^/(\\w+)(/.*)?$");

void tatoeba::main(std::string url) {
	booster::smatch res;
	booster::regex_match(url, res, lang_regex);
    std::map<std::string,std::string>::const_iterator p = lang_map.find(std::string(res[1]));
    if (p == lang_map.end()) {
        response().set_redirect_header("/en");
    }
    else {
	    context().locale(p->second);
	    if (!dispatcher().dispatch(res[2])) {
		    response().make_error_response(cppcms::http::response::not_found);
	    }
    }
}



} // namespace apps
