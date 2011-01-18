{
	"service" : {
		"api" : "http",
		"port" : 4242
	},
	"http" : {
		"script_names" : ["/tatoeba"]
	},
	"localization" : {
		"encoding" : "utf-8",
		"messages" : {
			"paths" : [ "../locale" ],
			"domains" : [ "hello" ]
		},
		"locales" : [ "en_GB.UTF-8", "fr_FR.UTF-8" ]
	},
    "session" : {
        "expire" : "renew",
        "timeout" : 604800,
        "location" : "server",
        "server" : {
            "storage" : "memory"
        }
    },
	"tatoeba" : {
        "tatodbxml" : "../doc/tatodb.xml",
		"css" : "http://css.tatoeba.org/css",
		"img" : "http://flags.tatoeba.org/img",
        "web" : "http://127.0.0.1:4242/",
        "languages" : {
            "en" : "en_GB.UTF-8",
            "fr" : "fr_FR.UTF-8"
        }
	}
}
