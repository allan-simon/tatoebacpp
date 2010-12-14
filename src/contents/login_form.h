#ifndef TATOEBA_LOGIN_FORM_H
#define TATOEBA_LOGIN_FORM_H

#include <cppcms/form.h>

namespace contents {

	struct login_form : public cppcms::form {
		cppcms::widgets::text username;
		cppcms::widgets::password password;
		cppcms::widgets::checkbox rememberMe;
		cppcms::widgets::submit submit;
		
		login_form() {
			username.name("username");
			username.message("Username : ");
			username.attributes_string("class=\"input text\"");
			password.name("password");
			password.message("Password : ");
			rememberMe.name("rememberMe");
			rememberMe.message("Remember Me");
			submit.name("submit");
			submit.value("Log in");
			*this + username + password + rememberMe + submit;
			username.non_empty();
			password.non_empty();
		}
		
		virtual bool validate() {
			if ( ! form::validate()) {
				return false;
			}
			return true;
		}
		
	};

}
#endif
