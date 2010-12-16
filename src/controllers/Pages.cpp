#include "Controller.h"
#include "controllers/Pages.h"
#include "tatoeba.h"
#include "contents/homepage.h"

namespace controllers {

Pages::Pages(apps::tatoeba& tatoapp) : controllers::Controller(tatoapp) {
	std::cout << "i dans pages vaut " << this->i << std::endl;
  	tatoapp.dispatcher().assign("", &Pages::homepage, this);
  	tatoapp.dispatcher().assign("/contribute", &Pages::contribute, this);
  	tatoapp.dispatcher().assign("/terms_of_use", &Pages::termsOfUse, this);
  	tatoapp.dispatcher().assign("/tatoeba_team_and_credits", &Pages::teamAndCredits, this);
}

void Pages::homepage() {
	contents::Homepage c;
    initContent(c);
    std::cout << "lang : " << c.lang << std::endl;
    c.text = "PLOP";
	std::cout << "i dans homepage vaut " << i << std::endl;
	std::cout << "css_path dans homepage vaut " << c.config.css_path << std::endl;
	render("homepage", c);
}


/**
 * Main page to add sentences and so
 */
void Pages::contribute() {
	contents::Homepage c;
    initContent(c);
	render("contribute", c);
}

/**
 * Terms of use page
 */
 void Pages::termsOfUse() {
 	contents::Homepage c;
 	initContent(c);
 	render("termsofuse", c);
 }
 
 /**
 * Team and Credits page
 */
 void Pages::teamAndCredits() {
 	contents::Homepage c;
 	initContent(c);
 	render("teamandcredits", c);
 }

} // End namespace
