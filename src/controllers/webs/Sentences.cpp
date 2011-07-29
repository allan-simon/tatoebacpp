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
namespace webs {

/**
 * TODO: maybe does not need to inherit from controller ?
 */
Sentences::Sentences(cppcms::service &serv) : Controller(serv) {
    // TODO have /  and /show directing to some "index" page 
    // as cburgmer pointed out, some people do navigate by crafting url
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
        sentencesModel->get_by_id(id, 20)
    );
    c.id = id;
    shc.lang = c.lang;
    shc.currentUserHelper = c.usersHelper;
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
void Sentences::show_random_in(std::string isoCode) {
    std::ostringstream oss;
    oss << sentencesModel->get_random_id(isoCode);

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
    TREAT_PAGE();
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


/**
 *
 */
void Sentences::translate(std::string toTranslateId) {

	int id = atoi(toTranslateId.c_str());

    CHECK_PERMISSION_OR_GO_TO_LOGIN(); 
	contents::helpers::Sentences shc(
        sentencesModel->get_by_id(id, 5)
    );

    if (!shc.empty()) {
        //we set the value of the hidden field to the id
        //of the sentence we're going to translate 
        contents::SentencesTrans c(
            toTranslateId
        );
        init_content(c);
    
        shc.lang = c.lang;
        c.shc = shc;

        render("sentences_translate",c);


    } else {
        go_back_to_previous_page();
    }

}

/**
 *
 */
void Sentences::translate_treat() {
    TREAT_PAGE();
    CHECK_PERMISSION_OR_GO_TO_LOGIN();

	forms::TransSentence transSentence;
    transSentence.load(context());


    if (!transSentence.validate()) {
        go_back_to_previous_page();
        return;
    }
    int translationId = 0;
    std::string translatedIdStr = transSentence.translatedId.value();
    int translatedId = atoi(translatedIdStr.c_str());

    int userId = get_current_user_id();     

    // TODO : handle if something wrong happen while saving
    try {
        results::Sentence sentence = sentencesModel->add(
            transSentence.transLang.selected_id(),
            transSentence.transString.value(),
            userId
        );

        translationId = sentence.id;

    } catch (const models::SentDupliException & e) {
        //TODO display the message to the user
        translationId = e.get_original_id();
    }

    sentencesModel->link(
        translatedId,
        translationId,
        get_current_user_id()
    );

    response().set_redirect_header(
        "/" + get_interface_lang() +
        "/sentences/show"
        "/" + translatedIdStr
    );
}


/**
 *
 */
void Sentences::link(std::string idOneStr, std::string idTwoStr) {
    CHECK_PERMISSION_OR_GO_TO_LOGIN();
	int idOne = atoi(idOneStr.c_str());
	int idTwo = atoi(idTwoStr.c_str());
    
    sentencesModel->link(
        idOne,
        idTwo,
        get_current_user_id()
    );

    response().set_redirect_header(
        "/" + get_interface_lang() +
        "/sentences/show"
        "/" + idOneStr
    );

}

/**
 *
 */
void Sentences::unlink(std::string idOneStr, std::string idTwoStr) {
    CHECK_PERMISSION_OR_GO_TO_LOGIN();
	int idOne = atoi(idOneStr.c_str());
	int idTwo = atoi(idTwoStr.c_str());
   
    
    sentencesModel->unlink(
        idOne,
        idTwo,
        get_current_user_id()
    );

    response().set_redirect_header(
        "/" + get_interface_lang() +
        "/sentences/show"
        "/" + idOneStr
    );

}




/**
 *
 */
void Sentences::edit_text(std::string sentenceId) {
	int id = atoi(sentenceId.c_str());

    // TODO add a check so that only moderator or owner can modify it
    CHECK_PERMISSION_OR_GO_TO_LOGIN(); 
	contents::helpers::Sentences shc(
        sentencesModel->get_by_id(id, 5)
    );

    if (!shc.empty()) {
        //we set the value of the input field to the current
        //value of the sentence
        contents::SentencesEditText c(
            sentenceId,
            shc.sentences[0].text  
        );
        init_content(c);
    
        shc.lang = c.lang;
        c.shc = shc;

        render("sentences_edit_text",c);


    } else {
        go_back_to_previous_page();
    }
}

/**
 *
 */
void Sentences::edit_text_treat() {
    TREAT_PAGE();
    CHECK_PERMISSION_OR_GO_TO_LOGIN();

	forms::EditTextSentence editText;
    editText.load(context());

    if (!editText.validate()) {
        go_back_to_previous_page();
        return;
    }
    std::string idStr = editText.sentenceId.value();
    int id = atoi(idStr.c_str());
    // TODO : handle if something wrong happen while saving
    try {

        sentencesModel->edit_text(
            id,
            editText.newString.value(),
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

    response().set_redirect_header(
        "/" + get_interface_lang() +
        "/sentences/show"
        "/" + idStr 
    );

}

/**
 * TODO
 */
void Sentences::edit_lang(std::string sentenceId) {
	int id = atoi(sentenceId.c_str());

    // TODO add a check so that only moderator or owner can modify it
    CHECK_PERMISSION_OR_GO_TO_LOGIN(); 
	contents::helpers::Sentences shc(
        sentencesModel->get_by_id(id, 5)
    );

    if (!shc.empty()) {
        //we set the value of the select to the current
        //language of the sentence
        contents::SentencesEditLang c(
            sentenceId,
            shc.sentences[0].lang 
        );
        init_content(c);
    
        shc.lang = c.lang;
        c.shc = shc;

        render("sentences_edit_lang",c);


    } else {
        go_back_to_previous_page();
    }
}

/**
 * TODO
 */
void Sentences::edit_lang_treat() {
    TREAT_PAGE();
    CHECK_PERMISSION_OR_GO_TO_LOGIN();

	forms::EditLangSentence editLang;
    editLang.load(context());

    if (!editLang.validate()) {
        go_back_to_previous_page();
        return;
    }
    std::string idStr = editLang.sentenceId.value();
    int id = atoi(idStr.c_str());
    // TODO : handle if something wrong happen while saving
    try {

        sentencesModel->edit_lang(
            id,
            editLang.newLang.selected_id(),
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

    response().set_redirect_header(
        "/" + get_interface_lang() +
        "/sentences/show"
        "/" + idStr 
    );


}




} // end of namespace webs
} // end of namespace controllers


