#!/usr/bin/env python

f = open('aes_init_stack_pattern.data', 'r')

addr = []
l = f.readline()
while l:
  l = f.readline()
  t = l.strip().split('[')
  if len(t) > 1:
    addr.append(int(t[1].split(']')[0], 16))

def get_set_line(addr):
  return (addr >> 6) & 0b111111

for i in xrange(len(addr)):
  print i, hex(addr[i]), get_set_line(addr[i])


