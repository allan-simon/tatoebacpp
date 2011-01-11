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
    cppcms::widgets::checkbox termsOfUse;
    cppcms::widgets::submit submit;

    register_form() {
        *this + username + password + email + quiz + termsOfUse + submit;
        submit.value("Register");
        submit.id("registerButton");
    }

    virtual bool validate() {
        if (! form::validate()) {
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
