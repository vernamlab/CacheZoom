#!/usr/bin/env python
import matplotlib.pyplot as plt
import numpy as np
import operator, sys, subprocess

MAX_MEASUREMENT = 50000
l = 0
r = MAX_MEASUREMENT

'''
f_csv = open('extracted.csv', 'w+')
def export_csv(lst):
  csv = ""
  for n in lst:
    csv += str(n) + ','

  f_csv.write(csv);    
  f_csv.write("\r\n");
'''

def get_set(addr):
   return (addr >> 6) & 0b111111

def calc_threshold(set_stat):
#  print '[+] Calculating eviction thresholds...'
  threshold = []
  for k in set_stat:
    k_sorted = sorted(k.items(), key=operator.itemgetter(1), reverse=True)
    select = 0
    for tu in k_sorted:
      if tu[0] > select and tu[1] > 400:
        select = tu[0]
    if select >= 80:
      threshold.append(255)
    else:
      threshold.append(select)
  return threshold

def unpack_plot_binary(data):
#  print '[+] Unpacking measurement binary...'
  f_raw = open(data, 'rb')
  samples = []
  set_stat = []

  for i in xrange(MAX_MEASUREMENT):
    lst = map(ord, list(f_raw.read(64)))
    samples.append(lst)

    for j in xrange(64):
      if j >=len(set_stat):
        set_stat.append({})
      
      if lst[j] != 0:
        if set_stat[j].has_key(lst[j]):
          set_stat[j][lst[j]] += 1
        else:
          set_stat[j].update({lst[j]: 1})

  return samples, calc_threshold(set_stat)

def read_log_count():
  cmd_process = ['tail', '/var/log/kern.log']
  proc = subprocess.Popen(cmd_process, stdout=subprocess.PIPE)
  proc.wait()
  last_line = line = proc.stdout.readline()
  while line:
    last_line = line
    line = proc.stdout.readline() 
  return int(last_line.split('Iteration:')[1].split('!')[0].strip())

f_auto_extract = False
if len(sys.argv) > 1 and int(sys.argv[1]) == 1:
  f_auto_extract = True


def compress_data(samples, thresholds):
#  print '[+] Filter measurments...'
  compressed = []
  global l
  global r
  if f_auto_extract:
    log_count = read_log_count()
    x = log_count % MAX_MEASUREMENT
    l = x - 1000
    r = x

  for i in xrange(l, r):
    c = 0
    for j in xrange(64):
      if samples[i][j] > thresholds[j]:
        c += 1

    if c < 30 and c > 0:
      compressed.append((i, samples[i]))

  return compressed

def calc_eviction_percentage(samples, thresholds, i):
    c = 0
    for j in xrange(l, r):
      if samples[j][i] > thresholds[i]:
        c += 1
    return (c * 1.0) / (r - l) * 100  
   

def auto_tweak_thresholds(samples, thresholds, per_limit):
#  print '[+] Tweaking tresholds for the range in (%s, %s)...'%(l, r)

  for i in xrange(64):
    if thresholds[i] == 255:
      continue

    per = calc_eviction_percentage(samples, thresholds, i)      
  
    while(per < per_limit):
      thresholds[i] -= 2
      per = calc_eviction_percentage(samples, thresholds, i)
      if per > per_limit:
        thresholds[i] += 2
        break

    while(per > per_limit):
      thresholds[i] += 2
      per = calc_eviction_percentage(samples, thresholds, i)

  return thresholds

samples, thresholds = unpack_plot_binary('plot.data')
compressed = compress_data(samples, thresholds)

def scan_last_round(compressed):
  global l
  global r
  r_set = False
  r_all_set = False
  done = False
  c_zero = 0
  c_data = 0
  for i in xrange(len(compressed), 0, -1):
    if done:
      break
    _sum = 0
    for j in xrange(32, 36):
      for k in xrange(15):
        if compressed[i-k-1][1][j] > thresholds[j]:      
          _sum += 1

    if _sum == 0:
      c_zero += 1
      c_data = 0
      if not r_all_set and c_zero > 15:
        r = compressed[i-1][0]
        r_set = True
      if r_all_set and c_zero > 15:
        l = compressed[i-1][0]
        done = True
    else:
      c_zero = 0
      c_data += 1
      if r_set and c_data > 15:
        r_all_set = True
       
#    print _sum, c_zero, r_set, r_all_set, done

  return l, r


if f_auto_extract:
  l, r = scan_last_round(compressed)
  thresholds = auto_tweak_thresholds(samples, thresholds, 20)


evict = {}
_sum = 0
plot_x = []
plot_y = []
for i in xrange(len(compressed)):
  for j in xrange(32, 36):
    if list(compressed[i])[1][j] > thresholds[j] and compressed[i][0] >= l and compressed[i][0] <= r:
      if evict.has_key(j):
        evict[j] += 1
      else:
        evict.update({j : 1})
      plot_x.append(list(compressed[i])[0])
      plot_y.append(j)
      _sum += 1

#for k in evict:
#  print k, float(evict[k]) / _sum
print evict

'''  
fig, ax = plt.subplots()
ax.grid(True)
ax.set_yticks(range(64))
ax.set_xlabel('Measuerment')
ax.set_ylabel('Set number')

c = 0
for line in ax.get_ygridlines():
  if c >= 32 and c <= 47:
    line.set_linestyle('--')
  if c >= 48 and c <= 63:
    line.set_linestyle('-')
  if c >= 0 and c <= 15:
    line.set_linestyle('-.')
  if c >= 16 and c <= 31:
    line.set_linestyle(':')

  c += 1

ax.plot(plot_x, plot_y, 'o')


plt.show()
'''
