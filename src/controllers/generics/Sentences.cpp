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
#include "Sentences.h"
#include "contents/sentences.h"

#include "models/Sentences.h"

namespace controllers {
namespace generics {
/**
 * TODO: maybe does not need to inherit from controller ?
 */
Sentences::Sentences() {
    // TODO have /  and /show directing to some "index" page 
    // as cburgmer pointed out, some people do navigate by crafting url
    /*
    cppcms::url_dispatcher* disp = &dispatcher();

    
  	disp->assign("/show/(\\d+)", &Sentences::show, this, 1);
  	disp->assign("/show-random", &Sentences::show_random, this);
  	disp->assign("/show-random-in/(\\w+)", &Sentences::show_random_in, this, 1);

  	disp->assign("/add", &Sentences::add, this);
  	disp->assign("/add_treat", &Sentences::add_treat, this);

  	disp->assign("/translate/(\\d+)", &Sentences::translate, this, 1);
  	disp->assign("/translate_treat", &Sentences::translate_treat, this);

  	disp->assign("/edit-text/(\\d+)", &Sentences::edit_text, this, 1);
  	disp->assign("/edit-text_treat", &Sentences::edit_text_treat, this);

  	disp->assign("/edit-lang/(\\d+)", &Sentences::edit_lang, this, 1);
  	disp->assign("/edit-lang_treat", &Sentences::edit_lang_treat, this);

  	disp->assign("/link/(\\d+)/(\\d+)", &Sentences::link, this, 1, 2);
  	disp->assign("/unlink/(\\d+)/(\\d+)", &Sentences::unlink, this, 1, 2);
    */
    sentencesModel = new models::Sentences();
}

/**
 *
 */
Sentences::~Sentences() {
    delete sentencesModel; 
}

} // End namespace generics
} // End namespace controllers
