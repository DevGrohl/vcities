import sys

file = open(sys.argv[1],"r")
content = file.read()
file.close()

lines = [ content[i:i+16] for i in range(0, len(content), 16) ]

print "\t00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f"
i = 0;
for line in lines:
	print format(i,'04x'),'\t',
	for c in line:
		print format(ord(c),'02x'),
	i+=16
	print

