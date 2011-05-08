#ifndef TATOEBACPP_ADD_SENTENCE_FORM_H
#define TATOEBACPP_ADD_SENTENCE_FORM_H

#include <cppcms/form.h>
#include "generics/Languages.h"

using namespace cppcms;

namespace forms {

    struct AddSentence : public cppcms::form {
        widgets::text sentenceString;
        widgets::select sentenceLang;
        widgets::submit submit;        
    
        // init of the form
        AddSentence() {
            *this + sentenceString + sentenceLang + submit;

            sentenceString.name("str");

            ISOToNameMap isoToName = Languages::get_instance()->get_iso_to_name_map();
            ISOToNameMap::iterator itr;
            for(itr = isoToName.begin(); itr != isoToName.end(); ++itr){
                sentenceLang.add(itr->second,itr->first);
            }

            submit.name("Add sentence");
            submit.value("add");

            sentenceString.non_empty();
            // TODO for select I'm sure there's something more specific for
            // selects to say "value must one the possible values of the select"
            sentenceLang.non_empty();
        };

    };
}



#endif


