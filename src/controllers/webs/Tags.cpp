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


#include "Tags.h"
#include "contents/tags.h"
#include "contents/forms/tags/add.h"

namespace controllers {
namespace webs {
/**
 *
 */
Tags::Tags(cppcms::service &serv) : Controller(serv) {

    tagsModel = new models::Tags();

    cppcms::url_dispatcher* d = &dispatcher();
    d->assign("/view-all$", &Tags::view_all, this);
    d->assign("/sentences-with-tag/(.*)$", &Tags::sentences_with_tag, this, 1);
    d->assign("/sentences-with-tag-in/(.*)/(\\w+)$", &Tags::sentences_with_tag_in, this, 1, 2);
    d->assign("/sentences-with-tag-in_treat/(.*)", &Tags::sentences_with_tag_in_treat, this, 1);
    d->assign("/add_treat", &Tags::add_treat, this);
    d->assign("/remove-from-sentence/(\\d+)/(\\d+)", &Tags::remove_from_sentence, this, 1, 2);
}

/**
 *
 */
Tags::~Tags() {
    delete tagsModel;
}

/**
 *
 */
void Tags::view_all() {

    contents::tags::ViewAll c;
    init_content(c);
    c.tagsList = tagsModel->get_all();

    render("tags_view_all", c);
}

/**
 *
 */
void Tags::sentences_with_tag(std::string tagName) {


    unsigned int page = get_page();

    contents::tags::SentencesWithTag c;
    init_content(c);
    c.filterLang.set_langs();
    c.tag = tagsModel->get(tagName);

    c.shc.baseUrl = "/tags/sentences-with-tag/" + tagName;
    c.shc.currentUserHelper = c.usersHelper;
    c.shc.sentences = tagsModel->sentences_with_tag(
        tagName,
        page
    );

    render("tags_sentences_with_tag", c);

}
/**
 *
 */
void Tags::sentences_with_tag_in(
    std::string tagName,
    std::string inLanguage
) {


    unsigned int page = get_page();

    contents::tags::SentencesWithTagIn c;
    init_content(c);
    c.filterLang.set_langs();
    c.tag = tagsModel->get(tagName);

    c.inLanguage = Languages::get_instance()->get_name_from_iso( 
        inLanguage
    );

    c.shc.baseUrl = "/tags/sentences-with-tag-in/" + tagName + "/" + inLanguage;
    c.shc.currentUserHelper = c.usersHelper;
    c.shc.sentences = tagsModel->sentences_with_tag_in(
        tagName,
        Languages::get_instance()->get_id_from_iso(inLanguage),
        page
    );

    render("tags_sentences_with_tag_in", c);

}

/**
 *
 */
void Tags::sentences_with_tag_in_treat(
    std::string tagName
) {

    forms::generics::FilterLang form;
    form.set_langs();
    form.load(context());
    if(!form.validate()) {
        go_back_to_previous_page();
    }

    std::string filteredLang = form.filterLang.selected_id();
    if (filteredLang == "mul") {

        response().set_redirect_header(
            "/tags/sentences-with-tag"
            "/" + tagName 
        );
    } else {
        response().set_redirect_header(
            "/tags/sentences-with-tag-in"
            "/" + tagName +
            "/" + filteredLang
        );
    }
}





/**
 *
 */
void Tags::add_treat() {

    TREAT_PAGE();

    CHECK_PERMISSION_OR_GO_TO_LOGIN();

    forms::tags::Add form;
    form.load(context());

    if (form.validate()) {
        int sentenceId = 0;
        std::istringstream(form.sentenceId.value()) >> sentenceId;
        std::string tagName = form.tag.value();

        int tagId = tagsModel->get_id(tagName);

        if (tagId != 0) {

            const bool success = tagsModel->tag_sentence(
                sentenceId,
                tagId,
                get_current_user_id()
            );
            if (success) {
                set_message("Tag added");        
            }

        } else {
            set_message("This tag does not exist.");
        }
        //set_message("Problem while saving.")

    } else { 
        //TODO i18n this
        set_message("The form was not correctly filled.");
    }
    go_back_to_previous_page();
}


/**
 *
 */
void Tags::remove_from_sentence(std::string sentenceIdStr, std::string tagIdStr) {

    CHECK_PERMISSION_OR_GO_TO_LOGIN();

	int sentenceId = atoi(sentenceIdStr.c_str());
	int tagId = atoi(tagIdStr.c_str());

    bool success = tagsModel->remove_from_sentence(
        sentenceId,
        tagId
    );

    if (success) { 
        set_message("Tag removed.");
    } else {
        set_message("A problem occured while trying to remove the tag.");
    }
    go_back_to_previous_page();
}


} // End namespace webs 
} // End namespace controllers


