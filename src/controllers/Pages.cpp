/**
 * Tatoeba Project, free collaborative creation of multilingual corpuses project
 * Copyright (C) 2011 Allan SIMON <allan.simon@supinfo.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * @category Tatoebacpp
 * @package  Controllers
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @license  Affero General Public License
 * @link     http://tatoeba.org
 */

#include "Controller.h"
#include "controllers/Pages.h"

#include "contents/pages.h"
#include "models/Sentences.h"

namespace controllers {

Pages::Pages(cppcms::service& serv) : controllers::Controller(serv) {
    dispatcher().assign("", &Pages::homepage, this);
  	dispatcher().assign("/contribute", &Pages::contribute, this);
  	dispatcher().assign("/terms-of-use", &Pages::terms_of_use, this);
  	dispatcher().assign("/tatoeba-team-and-credits", &Pages::team_and_credits, this);
}

/**
 *
 */
void Pages::homepage() {
    contents::PagesHomepage c;
    init_content(c);

    models::Sentences sentencesModel;
	contents::helpers::Sentences shc(
        sentencesModel.get_random()
    );
    shc.lang = c.lang;
    shc.currentUserHelper = c.usersHelper;
    c.shc = shc;
    render("homepage", c);
}

/**
 *
 */
void Pages::contribute() {
    contents::PagesContribute c;
    init_content(c);
    render("contribute", c);
}


/**
 *
 */
void Pages::terms_of_use() {
    contents::PagesTermsOfUse c;
    init_content(c);
    render("termsofuse", c);
}


/**
 *
 */
void Pages::team_and_credits() {
    contents::PagesTeamAndCredits c;
    init_content(c);
    render("teamandcredits", c);
}

} // End namespace
