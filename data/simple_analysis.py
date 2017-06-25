#!/usr/bin/env python
import matplotlib.pyplot as plt
import numpy as np
import operator, sys

MAX_MEASUREMENT = 50000


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

def compress_data(samples, thresholds):
#  print '[+] Filter measurments...'
  compressed = []
  l = 0
  r = MAX_MEASUREMENT
  if len(sys.argv) > 2:
    l = int(sys.argv[1])
    r = int(sys.argv[2])

  for i in xrange(l, r):
    c = 0
    for j in xrange(64):
      if samples[i][j] > thresholds[j]:
        c += 1

    if c < 30 and c > 0:
      compressed.append((i, samples[i]))

  return compressed

def calc_eviction_percentage(samples, thresholds, i):
    l = int(sys.argv[1])
    r = int(sys.argv[2])
    c = 0
    for j in xrange(l, r):
      if samples[j][i] > thresholds[i]:
        c += 1
    return (c * 1.0) / (r - l) * 100  

   

def auto_tweak_thresholds(samples, thresholds, per_limit):
#  print '[+] Tweaking tresholds for the range in (%s, %s)...'%(sys.argv[1], sys.argv[2])

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

samples, thresholds = unpack_plot_binary('samples.data')
if len(sys.argv) > 2:
  thresholds = auto_tweak_thresholds(samples, thresholds, int(sys.argv[3]))

compressed = compress_data(samples, thresholds)

l = 1
r = 0
if len(sys.argv) > 2:
  l = int(sys.argv[1])
  r = int(sys.argv[2])

evict = {}
plot_x = []
plot_y = []
for i in xrange(len(compressed)):
  for j in xrange(64):
    if list(compressed[i])[1][j] > thresholds[j]:      
      plot_x.append(list(compressed[i])[0])
      plot_y.append(j)
      distance = float(list(compressed[i])[0] - l) / (r - l)
      if evict.has_key(j):
        evict[j].append(distance)
      else:
        evict[j] = [distance]


for k in evict:
  _sum = 0
  for v in evict[k]:
    _sum += v
  evict[k] = _sum / len(evict[k])

evict = sorted(evict.items(), key=operator.itemgetter(1), reverse=False)
print evict

  
fig, ax = plt.subplots()
ax.grid(True)

ax.set_yticks(range(64))
ax.set_xlabel('Measuerment')
ax.set_ylabel('Set number')

ax.plot(plot_x, plot_y, 'o')
plt.show()

