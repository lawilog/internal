import re

patterns = [
	r'(?i)s(\d{1,2})[\W_]{0,1}[ef](\d{1,3})', # S03E18, s3f14, ...
	r'(?i)(\d{1,2})x+(\d{1,2})', # 2x08
#	(?i)/(?:s|season|staffel)\W?(\d{1,2})\s*(?:--[^/]*|\([^/]*|[^/]*)[/]\D*\1[\. _-]*(\d{1,2})
#	(?i)/(?:s|season|staffel)\W?(\d{1,2})\s*[^/]*[/]\D*\1[\. _-]*(\d{1,2})
	r'(?i)/(?:s|season|staffel)\W?(\d{1,2})\s*(?:--[^/]*|\([^/]*)[/]\D*\1[\. _-]*(\d{1,2})', # Season 1/foo 107 bar
#	r'(?i)/(?:s|season|staffel)\W?(\d{1,2})\s*(?:--[^/\\]*|\([^/\\]*)[/\\]\D*\1[\. _-]*(\d{1,2})', # Season 1\foo 107 bar
#	r'(?i)[/\\](?:s|season|staffel)\W?(\d{1,2})\s*(?:--[^/\\]*|\([^/\\]*)[/\\]\D*(\d{1,2})' # match season and then just the frist number afterwards

#	r'(?i)[/\\](?:s|season|staffel)\W?(\d{1,2})\D*[/\\]\D+[\. _-]\1(\d{1,2})[\. _-]\D+'
#	r'(\d{2})(\d{2})'
]

f = open('/tmp/tmp/Serien.txt')
for line in f:
	line = line.strip()
	b = 0
	for pat in patterns:
		m = re.search(pat, line)
		if m:
			print '#', m.group(1), m.group(2), line
			b = 1
			break
	
	if b == 0:
		print line

f.close()
