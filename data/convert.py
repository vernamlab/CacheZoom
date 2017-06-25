#!/usr/bin/python
import struct, glob, os
from operator import itemgetter

MAX_MEASUREMENT = 50000

def export_csv_line(f_csv, values):	
	csv = ''
	for v in values:
		csv += str(v) + ','
	
	csv = csv[:-1]

	f_csv.write(csv);    
	f_csv.write("\r\n");


sample_files = []
for f in glob.iglob('archive/gladman/*.data'):
  sample_files.append(f)


for f in sample_files:
	csv_path = f[0:-4]+'csv'
	f_raw = open(f, 'r')
	f_csv = open(csv_path, 'w+')
	for i in xrange(MAX_MEASUREMENT):  
		data = f_raw.read(64)
		export_csv_line(f_csv, map(ord, data))

	f_csv.close()
	f_raw.close()
