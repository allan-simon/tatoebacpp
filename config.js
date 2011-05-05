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
        "tatodbxml" : "../doc/tatodb.xml.huge",
		"css" : "http://css.tatoeba.org/css",
		"img" : "http://flags.tatoeba.org/img",
        "web" : "http://127.0.0.1:4242/",
        "interfacelangs" : {
            "eng" : "en_GB.UTF-8",
            "fra" : "fr_FR.UTF-8"
        },
        "languages" : {
            "wuu" : ["Shanghainese", 61],
            "eng" : ["English",      17],
            "fra" : ["French",       23],
            "rus" : ["Russian",      46],
            "deu" : ["German",       15],
            "cmn" : ["Chinese",      12],
            "yue" : ["Cantonese",    63],
            "jpn" : ["Japanese",     32]
        },
        "indexedMetas" : {
            "jpn" : [ "reading" , "alternative writing" ],
            "cmn" : [ "pinyin"  ,          "traditional"]
        }
	}
}
