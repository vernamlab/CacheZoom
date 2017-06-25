#!/usr/bin/env python
import operator
import matplotlib.pyplot as plt
import numpy

def normalize_data(source):
  f = open(source, 'r')
  addr = []
  l = f.readline()
  vert = []
  horz = []
  while l:
    l = f.readline()
    lst = l.strip().split(',')[:-1]
    lst = map(int, lst)

    for j in xrange(len(lst)):
      if j >=len(horz):
        horz.append([])

      horz[j].append(lst[j])
    
    if len(lst) > 0:
      vert.append(lst)
  return vert, horz



treshold = [ 
#[255, 76, 56, 56, 56, 62, 56, 70, 62, 66, 78, 62, 62, 64, 48, 56, 62, 48, 56, 48, 48, 54, 50, 42, 42, 48, 44, 60, 56, 48, 62, 70, 48, 48, 56, 42, 56, 48, 44, 56, 42, 42, 50, 42, 50, 46, 52, 42, 62, 56, 70, 56, 48, 48, 50, 48, 42, 48, 64, 62, 62, 110, 80, 104],
[
255, 
76, 
56, 
56,
56, 62, 56, 70, 62, 66, 78, 62, 62, 64, 48, 56, 62, 48, 56, 48, 48, 54, 50, 42, 42, 48, 44, 60, 56, 48, 62, 70, 48, 48, 56, 42, 56, 48, 44, 56, 42, 42, 50, 42, 50, 46, 52, 42, 62, 56, 70, 56, 48, 48, 50, 48, 42, 48, 64, 62, 62, 255, 255, 255],
#[255, 76, 58, 56, 56, 62, 58, 56, 62, 64, 78, 56, 70, 54, 44, 56, 70, 48, 50, 56, 48, 48, 44, 42, 42, 48, 44, 56, 48, 48, 56, 62, 42, 54, 64, 42, 42, 42, 44, 48, 46, 42, 50, 48, 48, 46, 56, 42, 56, 54, 58, 56, 48, 48, 50, 48, 42, 54, 56, 70, 62, 70, 80, 84]
[255, 76, 58, 56, 56, 62, 58, 56, 62, 64, 78, 56, 70, 54, 44, 56, 70, 48, 50, 56, 48, 48, 44, 42, 42, 48, 44, 56, 48, 48, 56, 62, 42, 54, 64, 42, 42, 42, 44, 48, 46, 42, 50, 48, 48, 46, 56, 42, 56, 54, 58, 56, 48, 48, 50, 48, 42, 54, 56, 70, 62, 70, 80, 84]
]

fig, ax = plt.subplots()

def get_affected_lines(horz, sample_number):
  sets_score = []
  for i in xrange(len(horz)):
    sets_score.append([])
    for j in xrange(len(horz[i])):
      if horz[i][j] <= treshold[sample_number][i]:
        sets_score[i].append(0)
      else:
        sets_score[i].append(1)

  lin_sets_affected = []
  for i in xrange(len(sets_score[0])):
    c = 0
    for j in xrange(len(sets_score)):
      if sets_score[j][i]:
        ax.scatter(i, j, color='r')
#        lin_sets_affected.append(j)
#        c += 1

#    if c > 30:
#      for i in xrange(c):
#        lin_sets_affected.pop()


  return lin_sets_affected

vert, horz = normalize_data('key0.csv')
lin_sets_affected0 = get_affected_lines(horz, 0)
vert, horz = normalize_data('key1.csv')
lin_sets_affected1 = get_affected_lines(horz, 1)

#for k in xrange(64):
#  plt.clf()
#  plt.plot(horz[k], '.')
#  plt.savefig('%s.png'%(k), bbox_inches='tight')





#for i in xrange(6000):
#  ax.scatter(i, lin_sets_affected0[i])



#ax.plot(lin_sets_affected0, '.', c='b')


#ax.plot(lin_sets_affected3, '.')



ax.grid(True)
gridlines = ax.get_xgridlines() + ax.get_ygridlines()
for line in gridlines:
  line.set_linestyle('-')

ax.set_yticks(range(64))



def get_set(addr):
   return (addr >> 6) & 0b111111


stack_sets = []
table_sets = []
full_sets = []

T0 = 0x0404780
T0_enclave = 0x260E0
f = open("../src/AttackEnclave/MyPinTool/output.txt")
line = f.readline()
while line:
  parts = line.strip().split(' ')
  if parts[0] == 'S':
    stack_addr = int(parts[1].strip(), 16) 
    _set = get_set(stack_addr) 
    stack_sets.append(_set)
    full_sets.append(_set)

  if parts[0] == 'T':
    offset = int(parts[1].strip(), 16) - T0
    enclave_addr = T0_enclave + offset
    _set = get_set(enclave_addr)
    table_sets.append(_set)
    full_sets.append(_set)

  line = f.readline()

#for i in xrange(len(stack_sets)):
#  ax.scatter(120+i*4, stack_sets[i], color='g')

#for i in xrange(len(table_sets)):
#  ax.scatter(220+i*8.7, table_sets[i], color='r')


#ax.plot(x, '.', color='r')

#print stack_sets
#print table_sets








plt.show()


#print len(sets_score)
#plt.imshow(sets_score, cmap='Greys', interpolation='nearest')
#plt.show()



'''
sets_stats = []
for i in xrange(len(horz)):
  sets_stats.append({})
  for j in xrange(len(horz[i])):
    if sets_stats[i].has_key(horz[i][j]):
      sets_stats[i][horz[i][j]] += 1
    else:
      sets_stats[i].update({horz[i][j]: 1})

thresholds = []
for k in sets_stats:
  k_sorted = sorted(k.items(), key=operator.itemgetter(1), reverse=True)
  print k_sorted
  select = 0
  for tu in k_sorted:
    if tu[0] > select and tu[1] > 600:
      select = tu[0]
  thresholds.append(select)
'''






