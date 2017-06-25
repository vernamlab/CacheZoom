#!/usr/bin/env python


def get_set(addr):
   return (addr >> 6) & 0b111111


stack_sets = []
table_sets = []


T0 = 0x0405400  
T0_enclave = 0x26800
f = open("../src/AESTTAttackEnclave/MyPinTool/output.txt")
print '"'+f.readline().strip()+'"'
print '"'+f.readline().strip()+'"'
line = f.readline()
c = 0
while line:
  parts = line.strip().split(' ')
  if parts[0] == 'S':
    stack_addr = int(parts[1].strip(), 16)
    _set = get_set(stack_addr)
    stack_sets.append(_set)

  if parts[0] == 'T':
    offset = int(parts[1].strip(), 16) - T0
#    print chr((offset - ((c % 4) * 1024))/ 4) # leak key
    enclave_addr = T0_enclave + offset
    _set = get_set(enclave_addr)
    table_sets.append(_set)
    c += 1

  line = f.readline()


#print stack_sets
print table_sets
#for i in xrange(0, len(table_sets), 16):
#  print "%s,"%(table_sets[i:i+16])


TE0 = 0x26800
#TE0 = 0x404780

#for addr in xrange(TE0, TE0 + 4*0x400, 4):
#  print hex(addr), (addr >> 6) & 0b111111, bin((addr >> 6) & 0b111111)

'''
print "TE0--------------------"
for addr in xrange(TE0, TE0 + 0x400, 64):
  print hex(addr), (addr >> 6) & 0b111111, bin((addr >> 6) & 0b111111)

print "TE1--------------------"
for addr in xrange(TE0 + 0x400, TE0 + 2 * 0x400, 64):
  print hex(addr), (addr >> 6) & 0b111111, bin((addr >> 6) & 0b111111)

print "TE2--------------------"
for addr in xrange(TE0 + 2 * 0x400, TE0 + 3 * 0x400, 64):
  print hex(addr), (addr >> 6) & 0b111111, bin((addr >> 6) & 0b111111)

print "TE3--------------------"
for addr in xrange(TE0 + 3 * 0x400, TE0 + 4 * 0x400, 64):
  print hex(addr), (addr >> 6) & 0b111111, bin((addr >> 6) & 0b111111)
'''
