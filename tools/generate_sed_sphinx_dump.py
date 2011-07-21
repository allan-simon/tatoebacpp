import json
import sys

from pprint import pprint

jsonFile = "../config.js"
if (len(sys.argv) == 2):
    jsonFile = sys.argv[1]

jsonData = open(jsonFile)
data = json.load(jsonData)


print "sed \\"
for isoCode, array in data["tatoeba"]["languages"].iteritems():
    print " -e '/^    \<translatedin>/! s/\([>,]\)" + isoCode + "\([,<]\)/\\1"+str(array[1]) + "\\2/' \\"

print "-e '/^    \<translatedin>/! s/,[a-z]\\{3,4\\}//g'  ../build/sphinxdump.xml* "

