{
	"service" : {
		"api" : "http",
		"port" : 4242
	},

    "cache" : {
        "backend" : "thread_shared"
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
        "interfacelangs" : [
            ["en"  , "eng", "en_GB.UTF-8", "English"],
            ["fr"  , "fre", "fr_FR.UTF-8", "Français"]
        ],
        "searchEngine" : {
            "indexesPath" : "../data/indexes/"
        },
        "sqlite3" : {
            "path" : "../doc/sqlite3.db"
        },
        "languages" : [
            [ "acm"  , "Iraqi Arabic" ,  2], 
            ["afr"  , "Afrikaans" ,  3], 
            ["ara"  , "Arabic" ,  4], 
            ["arz"  , "Egyptian Arabic" ,  5], 
            ["bel"  , "Belarusian" ,  6], 
            ["ben"  , "Bengali" ,  7], 
            ["bre"  , "Breton" ,  8], 
            ["bul"  , "Bulgarian" ,  9], 
            ["cat"  , "Catalan" , 10], 
            ["ces"  , "Czech" , 11], 
            ["cmn"  , "Mandarin Chinese" , 12], 
            ["cycl" , "CycL", 13], 
            ["dan"  , "Danish" , 14], 
            ["deu"  , "German" , 15], 
            ["ell"  , "Modern Greek" , 16], 
            ["eng"  , "English" , 17], 
            ["epo"  , "Esperanto" , 18], 
            ["est"  , "Estonian" , 19], 
            ["eus"  , "Basque" , 20], 
            ["fao"  , "Faroese" , 21], 
            ["fin"  , "Finnish" , 22], 
            ["fra"  , "French" , 23], 
            ["fry"  , "Frisian" , 24], 
            ["heb"  , "Hebrew" , 25], 
            ["hin"  , "Hindi" , 26], 
            ["hun"  , "Hungarian" , 27], 
            ["hye"  , "Armenian" , 28], 
            ["ind"  , "Indonesian" , 29], 
            ["isl"  , "Icelandic" , 30], 
            ["ita"  , "Italian" , 31], 
            ["jpn"  , "Japanese" , 32], 
            ["kat"  , "Georgian" , 33], 
            ["kaz"  , "Kazakh" , 34], 
            ["kor"  , "Korean" , 35], 
            ["lat"  , "Latin" , 36], 
            ["lvs"  , "Latvian" , 37], 
            ["nan"  , "Teochew" , 38], 
            ["nld"  , "Dutch" , 39], 
            ["nob"  , "Norwegian (Bokmål)" , 40], 
            ["non"  , "Norwegian (Nynorsk)" , 41], 
            ["pes"  , "Persian" , 42], 
            ["pol"  , "Polish" , 43], 
            ["por"  , "Portuguese" , 44], 
            ["ron"  , "Romanian" , 45], 
            ["rus"  , "Russian" , 46], 
            ["san"  , "Sanskrit" , 47], 
            ["slk"  , "Slovak" , 48], 
            ["spa"  , "Spanish" , 49], 
            ["sqi"  , "Albanian" , 50], 
            ["srp"  , "Serbian" , 51], 
            ["swe"  , "Swedish" , 52], 
            ["swh"  , "Swahili" , 53], 
            ["tat"  , "Tatar" , 54], 
            ["tur"  , "Turkish" , 55], 
            ["uig"  , "Uyghur" , 56], 
            ["ukr"  , "Ukrainian" , 57], 
            ["urd"  , "Urdu" , 58], 
            ["uzb"  , "Uzbek" , 59], 
            ["vie"  , "Vietnamese" , 60], 
            ["wuu"  , "Shanghainese (Wu)" , 61], 
            ["yid"  , "Yiddish" , 62], 
            ["yue"  , "Cantonese" , 63], 
            ["zsm"  , "Malay" , 64], 
            ["bos"  , "Bosnian" , 65], 
            ["hrv"  , "Croatian" , 66], 
            ["orv"  , "Old East Slavic" , 67], 
            ["cha"  , "Chamorro" , 68], 
            ["tgl"  , "Tagalog" , 69], 
            ["que"  , "Quechua" , 70], 
            ["mon"  , "Mongolian" , 71], 
            ["lit"  , "Lithuanian" , 72], 
            ["glg"  , "Galician" , 73], 
            ["gle"  , "Irish" , 74], 
            ["ina"  , "Interlingua" , 75], 
            ["jbo"  , "Lojban" , 76], 
            ["toki" , "Toki Pona", 77], 
            ["ain"  , "Ainu" , 78], 
            ["scn"  , "Sicilian" , 79], 
            ["mal"  , "Malayalam" , 80], 
            ["nds"  , "low Saxon" , 81], 
            ["tlh"  , "Klingon" , 82], 
            ["slv"  , "Slovenian" , 83], 
            ["tha"  , "Thai" , 84], 
            ["lzh"  , "Literary Chinese" , 85], 
            ["roh"  , "Romansh" , 86], 
            ["vol"  , "Volapük" , 87],
            ["oss"  , "Ossetian" , 88], 
            ["ido"  , "Ido" , 89], 
            ["gla"  , "Scottish Gaelic" , 90], 
            ["ast"  , "Asturian" , 91] 
        ],
        "indexedMetas" : {
            "jpn" : [ "reading" , "alternative writing" ],
            "cmn" : [ "pinyin"  ,          "traditional"]
        }
	}
}
