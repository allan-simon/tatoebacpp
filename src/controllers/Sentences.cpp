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
#include "controllers/Sentences.h"
#include "contents/sentences.h"

#include "models/Sentences.h"

namespace controllers {

/**
 *
 */
Sentences::Sentences(cppcms::service &serv) : Controller(serv) {
    // TODO have /  and /show directing to some "index" page 
    // as cburgmer pointed out, some people do navigate by crafting url
    cppcms::url_dispatcher* disp = &dispatcher();

    
  	disp->assign("/show/(\\d+)", &Sentences::show, this, 1);
  	disp->assign("/add", &Sentences::add, this);
  	disp->assign("/add_treat", &Sentences::add_treat, this);
  	disp->assign("/show-random", &Sentences::show_random, this);

    sentencesModel = new models::Sentences();
}

/**
 *
 */
Sentences::~Sentences() {
    delete sentencesModel; 
}

/**
 * 
 */
void Sentences::show(std::string sentence_id) {
	int id = atoi(sentence_id.c_str());

	contents::SentencesShow c;
    init_content(c);
	contents::helpers::Sentences shc(
        sentencesModel->get_by_id(id)
    );
    c.id = id;
    shc.lang = c.lang;
    c.shc = shc;
    

    render("sentences_show", c);
}


/**
 *
 */
void Sentences::show_random() {
    std::ostringstream oss;
    oss << sentencesModel->get_random_id();

    response().set_redirect_header(
        "/" + get_interface_lang() +
        "/sentences/show"
        "/" + oss.str()
    );

}

/**
 *
 */
void Sentences::add() {
    CHECK_PERMISSION_OR_GO_TO_LOGIN(); 

	contents::SentencesAdd c;
    init_content(c);

    render("sentences_add",c);

}

/**
 *
 */
void Sentences::add_treat() {
    CHECK_PERMISSION_OR_GO_TO_LOGIN();

	forms::AddSentence addSentence;
    addSentence.load(context());

    results::Sentence sentence;
    if (addSentence.validate()) {
        // TODO : handle if something wrong happen while saving
        try {
            sentence = sentencesModel->add(
                addSentence.sentenceLang.selected_id(),
                addSentence.sentenceString.value(),
                get_current_user_id()
            );
        } catch (const models::SentDupliException & e) {
            //TODO display the message to the user
            std::ostringstream oss;
            oss << e.get_original_id();

            response().set_redirect_header(
                "/" + get_interface_lang() +
                "/sentences/show"
                "/" + oss.str()
            );
            return; 

        }

        if (sentence.exists()) {
            std::ostringstream oss;
            oss << sentence.id;

            response().set_redirect_header(
                "/" + get_interface_lang() +
                "/sentences/show"
                "/" + oss.str()
            );
            return; 
        }
    }

    go_back_to_previous_page();
}


} // End namespace
