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
#include "OfUser.h"
#include "contents/sentences.h"

#include "models/OfUser.h"
#include "contents/Config.h"

namespace controllers {
namespace webs {

OfUser::OfUser(cppcms::service &serv) : Controller(serv) {

    cppcms::url_dispatcher* disp = &dispatcher();

  	disp->assign("/sentences-of/(.*)", &OfUser::sentences_of, this, 1);
  	disp->assign("/adopt-sentence/(\\d+)", &OfUser::adopt_sentence, this, 1);

    ofUsersModel = new models::OfUser(
        cppdb::session(
            "sqlite3:db=" + Config::get_instance()->sqlite3Path
        )
    );
}

/**
 *
 */
OfUser::~OfUser() {
    delete ofUsersModel;
}

/**
 *
 */
void OfUser::sentences_of(
    std::string userName
) {
}

/**
 *
 */
void OfUser::adopt_sentence(
    std::string sentenceIdStr
) {
    CHECK_PERMISSION_OR_GO_TO_LOGIN(); 
    std::stringstream ss(sentenceIdStr);
    int sentenceId = 0;
    ss >> sentenceId;
    
    const bool success = ofUsersModel->adopt_sentence(
        sentenceId,
        get_current_user_id()
    );

    if (success) {
        // TODO say that the sentence has been correctly adopted
    } else {
        // TODO print an error message
    }

    //TODO factorize this
    response().set_redirect_header(
        "/" + get_interface_lang() +
        "/sentences/show"
        "/" + sentenceIdStr
    );
}



} // end of namespace webs
} // end of namespace controllers
