#ifndef TATOEBA_REGISTER_FORM_H
#define TATOEBA_REGISTER_FORM_H

#include <cppcms/form.h>
#include "contents/content.h"

namespace contents {

struct register_form : public cppcms::form {
    cppcms::widgets::text username;
    cppcms::widgets::password password;
    cppcms::widgets::text email;
    cppcms::widgets::text quiz;
    cppcms::widgets::checkbox termOfUse;
    cppcms::widgets::submit submit;

    register_form() {
    }

    virtual bool validate() {
        if (! validate()) {
            return false;
        }
        return true;
    }
};

struct Register : public BaseContent {
    register_form registerForm;
};

}

#endif
