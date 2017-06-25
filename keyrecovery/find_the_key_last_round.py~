#!/usr/bin/env python
import sys, math, random, signal, time
ttc = time.time() 

counter = 0

def signal_handler(signal, frame):
  print counter

signal.signal(signal.SIGTSTP, signal_handler)

sbox = (
  0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
  0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
  0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
  0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
  0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
  0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
  0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
  0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
  0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
  0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
  0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
  0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
  0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
  0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
  0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
  0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
)

sbox_mul2 = (
  0xc6, 0xf8, 0xee, 0xf6, 0xff, 0xd6, 0xde, 0x91, 0x60, 0x2, 0xce, 0x56, 0xe7, 0xb5, 0x4d, 0xec,
  0x8f, 0x1f, 0x89, 0xfa, 0xef, 0xb2, 0x8e, 0xfb, 0x41, 0xb3, 0x5f, 0x45, 0x23, 0x53, 0xe4, 0x9b,
  0x75, 0xe1, 0x3d, 0x4c, 0x6c, 0x7e, 0xf5, 0x83, 0x68, 0x51, 0xd1, 0xf9, 0xe2, 0xab, 0x62, 0x2a,
  0x8, 0x95, 0x46, 0x9d, 0x30, 0x37, 0xa, 0x2f, 0xe, 0x24, 0x1b, 0xdf, 0xcd, 0x4e, 0x7f, 0xea,
  0x12, 0x1d, 0x58, 0x34, 0x36, 0xdc, 0xb4, 0x5b, 0xa4, 0x76, 0xb7, 0x7d, 0x52, 0xdd, 0x5e, 0x13,
  0xa6, 0xb9, 0x0, 0xc1, 0x40, 0xe3, 0x79, 0xb6, 0xd4, 0x8d, 0x67, 0x72, 0x94, 0x98, 0xb0, 0x85,
  0xbb, 0xc5, 0x4f, 0xed, 0x86, 0x9a, 0x66, 0x11, 0x8a, 0xe9, 0x4, 0xfe, 0xa0, 0x78, 0x25, 0x4b,
  0xa2, 0x5d, 0x80, 0x5, 0x3f, 0x21, 0x70, 0xf1, 0x63, 0x77, 0xaf, 0x42, 0x20, 0xe5, 0xfd, 0xbf,
  0x81, 0x18, 0x26, 0xc3, 0xbe, 0x35, 0x88, 0x2e, 0x93, 0x55, 0xfc, 0x7a, 0xc8, 0xba, 0x32, 0xe6,
  0xc0, 0x19, 0x9e, 0xa3, 0x44, 0x54, 0x3b, 0xb, 0x8c, 0xc7, 0x6b, 0x28, 0xa7, 0xbc, 0x16, 0xad,
  0xdb, 0x64, 0x74, 0x14, 0x92, 0xc, 0x48, 0xb8, 0x9f, 0xbd, 0x43, 0xc4, 0x39, 0x31, 0xd3, 0xf2,
  0xd5, 0x8b, 0x6e, 0xda, 0x1, 0xb1, 0x9c, 0x49, 0xd8, 0xac, 0xf3, 0xcf, 0xca, 0xf4, 0x47, 0x10,
  0x6f, 0xf0, 0x4a, 0x5c, 0x38, 0x57, 0x73, 0x97, 0xcb, 0xa1, 0xe8, 0x3e, 0x96, 0x61, 0xd, 0xf,
  0xe0, 0x7c, 0x71, 0xcc, 0x90, 0x6, 0xf7, 0x1c, 0xc2, 0x6a, 0xae, 0x69, 0x17, 0x99, 0x3a, 0x27,
  0xd9, 0xeb, 0x2b, 0x22, 0xd2, 0xa9, 0x7, 0x33, 0x2d, 0x3c, 0x15, 0xc9, 0x87, 0xaa, 0x50, 0xa5,
  0x3, 0x59, 0x9, 0x1a, 0x65, 0xd7, 0x84, 0xd0, 0x82, 0x29, 0x5a, 0x1e, 0x7b, 0xa8, 0x6d, 0x2c
)

sbox_mul3 = (
  0xa5, 0x84, 0x99, 0x8d, 0xd, 0xbd, 0xb1, 0x54, 0x50, 0x3, 0xa9, 0x7d, 0x19, 0x62, 0xe6, 0x9a,
  0x45, 0x9d, 0x40, 0x87, 0x15, 0xeb, 0xc9, 0xb, 0xec, 0x67, 0xfd, 0xea, 0xbf, 0xf7, 0x96, 0x5b,
  0xc2, 0x1c, 0xae, 0x6a, 0x5a, 0x41, 0x2, 0x4f, 0x5c, 0xf4, 0x34, 0x8, 0x93, 0x73, 0x53, 0x3f,
  0xc, 0x52, 0x65, 0x5e, 0x28, 0xa1, 0xf, 0xb5, 0x9, 0x36, 0x9b, 0x3d, 0x26, 0x69, 0xcd, 0x9f,
  0x1b, 0x9e, 0x74, 0x2e, 0x2d, 0xb2, 0xee, 0xfb, 0xf6, 0x4d, 0x61, 0xce, 0x7b, 0x3e, 0x71, 0x97,
  0xf5, 0x68, 0x0, 0x2c, 0x60, 0x1f, 0xc8, 0xed, 0xbe, 0x46, 0xd9, 0x4b, 0xde, 0xd4, 0xe8, 0x4a,
  0x6b, 0x2a, 0xe5, 0x16, 0xc5, 0xd7, 0x55, 0x94, 0xcf, 0x10, 0x6, 0x81, 0xf0, 0x44, 0xba, 0xe3,
  0xf3, 0xfe, 0xc0, 0x8a, 0xad, 0xbc, 0x48, 0x4, 0xdf, 0xc1, 0x75, 0x63, 0x30, 0x1a, 0xe, 0x6d,
  0x4c, 0x14, 0x35, 0x2f, 0xe1, 0xa2, 0xcc, 0x39, 0x57, 0xf2, 0x82, 0x47, 0xac, 0xe7, 0x2b, 0x95,
  0xa0, 0x98, 0xd1, 0x7f, 0x66, 0x7e, 0xab, 0x83, 0xca, 0x29, 0xd3, 0x3c, 0x79, 0xe2, 0x1d, 0x76,
  0x3b, 0x56, 0x4e, 0x1e, 0xdb, 0xa, 0x6c, 0xe4, 0x5d, 0x6e, 0xef, 0xa6, 0xa8, 0xa4, 0x37, 0x8b,
  0x32, 0x43, 0x59, 0xb7, 0x8c, 0x64, 0xd2, 0xe0, 0xb4, 0xfa, 0x7, 0x25, 0xaf, 0x8e, 0xe9, 0x18,
  0xd5, 0x88, 0x6f, 0x72, 0x24, 0xf1, 0xc7, 0x51, 0x23, 0x7c, 0x9c, 0x21, 0xdd, 0xdc, 0x86, 0x85,
  0x90, 0x42, 0xc4, 0xaa, 0xd8, 0x5, 0x1, 0x12, 0xa3, 0x5f, 0xf9, 0xd0, 0x91, 0x58, 0x27, 0xb9,
  0x38, 0x13, 0xb3, 0x33, 0xbb, 0x70, 0x89, 0xa7, 0xb6, 0x22, 0x92, 0x20, 0x49, 0xff, 0x78, 0x7a,
  0x8f, 0xf8, 0x80, 0x17, 0xda, 0x31, 0xc6, 0xb8, 0xc3, 0xb0, 0x77, 0x11, 0xcb, 0xfc, 0xd6, 0x3a
)
sboxInv = (
  0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
  0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
  0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
  0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
  0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
  0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
  0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
  0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
  0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
  0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
  0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
  0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
  0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
  0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
  0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
  0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
)

def get_T_list(set_number):
  if set_number >= 32 and set_number <= 47:
    k = set_number - 32    
    x = k * 16
    y = x + 16
    return x, y
  elif set_number >= 48 and set_number <= 63:
    k = set_number - 48
    x = k * 16
    y = x + 16
    return x, y
  elif set_number >= 0 and set_number <= 15:
    k = set_number
    x = k * 16
    y = x + 16
    return x, y
  elif set_number >= 16 and set_number <= 31:
    k = set_number - 16
    x = k * 16
    y = x + 16
    return x, y


key_round_10_valid = [111, 191, 99, 248, 253, 118, 140, 250, 35, 50, 175, 52, 148, 110, 88, 145]


f = open('data/last_round.txt', 'r')
plain_t = f.readline()
measure = []
while plain_t:
  cipher_t = f.readline().strip()
  pin_trace = f.readline().strip()

  measure.append({"p": eval(plain_t), "c": eval(cipher_t), "pin": eval(pin_trace)})  
  f.readline()
  f.readline()
  plain_t = f.readline()

random.shuffle(measure)

key_round_10 = []
last_round_trace = measure[0]['pin'][-16:]
for i in xrange(16):
  byte = {}
  x, y = get_T_list(last_round_trace[i])
  for j in xrange(x, y):
    byte.update({ord(measure[0]['c'][i]) ^ sbox[j] : 0})
  key_round_10.append(byte)


last_2_round_trace = measure[0]['pin'][-32:-16]
c_text = measure[0]['c']

#FIX SOME KEYS
#key_round_10[11] = [key_round_10_valid[11]]
#key_round_10[15] = [key_round_10_valid[15]]
#key_round_10[6] = [key_round_10_valid[6]]


'''
Group 2 Eq -----------------------------------------------------------------------
'''
x4_x5_x6_x7 = pow(2, 16) * [None]
counter = 0

x1, y1 = get_T_list(last_2_round_trace[4])
x2, y2 = get_T_list(last_2_round_trace[5])
x3, y3 = get_T_list(last_2_round_trace[6])
x4, y4 = get_T_list(last_2_round_trace[7])

for i1 in xrange(x1, y1):
  for i2 in xrange(x2, y2):
    for i3 in xrange(x3, y3):
      for i4 in xrange(x4, y4):
        x4_x5_x6_x7[counter] = ''.join(map(chr, (i1, i2, i3, i4)))
        counter += 1


x4_x5_x6_x7 = filter(lambda _: _ != None, tuple(set(x4_x5_x6_x7))) 

counter = 0
new_x4_x5_x6_x7 = pow(2, 16) * [None]

for _tuple in x4_x5_x6_x7:
  i1 = ord(_tuple[0])
  i2 = ord(_tuple[1])
  i3 = ord(_tuple[2])
  i4 = ord(_tuple[3])
  f = False
  for k160 in key_round_10[0]:
    if f:
      break
    for k164 in key_round_10[4]:
      expr = sbox_mul2[i1] ^ sbox_mul3[i2] ^ sbox[i3] ^ sbox[i4] ^ sboxInv[ord(c_text[4]) ^ k164] ^ k160 ^ k164
      if not expr:
        f = True
        break

  if not f:
    continue

  f = False
  for k161 in key_round_10[1]:
    if f:
      break
    for k165 in key_round_10[5]:
      expr = sbox[i1] ^ sbox_mul2[i2] ^ sbox_mul3[i3] ^ sbox[i4] ^ sboxInv[ord(c_text[1]) ^ k161] ^ k161 ^ k165
      if not expr:
        f = True
        break

  if not f:
    continue
  
  f = False
  for k162 in key_round_10[2]:
    if f:
      break
    for k166 in key_round_10[6]:
      if f:
        break
      for k174 in key_round_10[14]:
        expr = sbox[i1] ^ sbox[i2] ^ sbox_mul2[i3] ^ sbox_mul3[i4] ^ sboxInv[ord(c_text[14]) ^ k174] ^ k162 ^ k166
        if not expr:
          f = True
          break

  if not f:
    continue

  f = False
  for k163 in key_round_10[3]:
    if f:
      break
    for k167 in key_round_10[7]:
      if f:
        break
      for k171 in key_round_10[11]:
        expr = sbox_mul3[i1] ^ sbox[i2] ^ sbox[i3] ^ sbox_mul2[i4] ^ sboxInv[ord(c_text[11]) ^ k171] ^ k163 ^ k167
        if not expr:
          f = True
          break

  if not f:
    continue

  if f:
    new_x4_x5_x6_x7[counter] = ''.join(map(chr, (i1, i2, i3, i4)))
    counter += 1


x4_x5_x6_x7 = filter(lambda _: _ != None, tuple(set(new_x4_x5_x6_x7)))
print "x4_x5_x6_x7", math.log(len(x4_x5_x6_x7), 2)

counter = 0
x4_x5_x6_x7_k162_k166_k174 = {}

for k162 in key_round_10[2]:
  for k166 in key_round_10[6]:
    for k174 in key_round_10[14]:
      for _tuple in x4_x5_x6_x7:
        i1 = ord(_tuple[0])
        i2 = ord(_tuple[1])
        i3 = ord(_tuple[2])
        i4 = ord(_tuple[3])
        expr = sbox[i1] ^ sbox[i2] ^ sbox_mul2[i3] ^ sbox_mul3[i4] ^ sboxInv[ord(c_text[14]) ^ k174] ^ k162 ^ k166
        if not expr:
          if x4_x5_x6_x7_k162_k166_k174.has_key(_tuple):            
            x4_x5_x6_x7_k162_k166_k174[_tuple].append(''.join(map(chr, (k162, k166, k174))))
          else:
             x4_x5_x6_x7_k162_k166_k174.update({_tuple : [''.join(map(chr, (k162, k166, k174)))]})
          counter += 1

print "x4_x5_x6_x7_k162_k166_k174", math.log(counter, 2)
valid_sub_key = ''.join(map(chr, (key_round_10_valid[2], key_round_10_valid[6], key_round_10_valid[14])))
f = False
for k in x4_x5_x6_x7_k162_k166_k174:
  if f:
    break
  for v in x4_x5_x6_x7_k162_k166_k174[k]:
    if v == valid_sub_key:
      f = True
      break
if f:
  print "x4_x5_x6_x7_k162_k166_k174 have the key"
else:
  print "x4_x5_x6_x7_k162_k166_k174 have not the key"


counter = 0
x4_x5_x6_x7_k161_k165 = {}

for k161 in key_round_10[1]:
  for k165 in key_round_10[5]:
    for _tuple in x4_x5_x6_x7:
      i1 = ord(_tuple[0])
      i2 = ord(_tuple[1])
      i3 = ord(_tuple[2])
      i4 = ord(_tuple[3])
      expr = sbox[i1] ^ sbox_mul2[i2] ^ sbox_mul3[i3] ^ sbox[i4] ^ sboxInv[ord(c_text[1]) ^ k161] ^ k161 ^ k165
      if not expr: 
        if x4_x5_x6_x7_k161_k165.has_key(_tuple):            
          x4_x5_x6_x7_k161_k165[_tuple].append(''.join(map(chr, (k161, k165))))
        else:
          x4_x5_x6_x7_k161_k165.update({_tuple : [''.join(map(chr, (k161, k165)))]})
        counter += 1

print "x4_x5_x6_x7_k161_k165", math.log(counter, 2)
valid_sub_key = ''.join(map(chr, (key_round_10_valid[1], key_round_10_valid[5])))
f = False
for k in x4_x5_x6_x7_k161_k165:
  if f:
    break
  for v in x4_x5_x6_x7_k161_k165[k]:
    if v == valid_sub_key:
      f = True
      break
if f:
  print "x4_x5_x6_x7_k161_k165 have the key"
else:
  print "x4_x5_x6_x7_k161_k165 have not the key"


counter = 0
x4_x5_x6_x7_k160_k164 = {}

for k160 in key_round_10[0]:
  for k164 in key_round_10[4]:
    for _tuple in x4_x5_x6_x7:
      i1 = ord(_tuple[0])
      i2 = ord(_tuple[1])
      i3 = ord(_tuple[2])
      i4 = ord(_tuple[3])
      expr = sbox_mul2[i1] ^ sbox_mul3[i2] ^ sbox[i3] ^ sbox[i4] ^ sboxInv[ord(c_text[4]) ^ k164] ^ k160 ^ k164
      if not expr:
        if x4_x5_x6_x7_k160_k164.has_key(_tuple):            
          x4_x5_x6_x7_k160_k164[_tuple].append(''.join(map(chr, (k160, k164))))
        else:
          x4_x5_x6_x7_k160_k164.update({_tuple : [''.join(map(chr, (k160, k164)))]})
        counter += 1

print "x4_x5_x6_x7_k160_k164", math.log(counter, 2)
valid_sub_key = ''.join(map(chr, (key_round_10_valid[0], key_round_10_valid[4])))
f = False
for k in x4_x5_x6_x7_k160_k164:
  if f:
    break
  for v in x4_x5_x6_x7_k160_k164[k]:
    if v == valid_sub_key:
      f = True
      break
if f:
  print "x4_x5_x6_x7_k160_k164 have the key"
else:
  print "x4_x5_x6_x7_k160_k164 have not the key"

counter = 0
x4_x5_x6_x7_k163_k167_k171 = {}

for k163 in key_round_10[3]:
  for k167 in key_round_10[7]:
    for k171 in key_round_10[11]:
      for _tuple in x4_x5_x6_x7:
        i1 = ord(_tuple[0])
        i2 = ord(_tuple[1])
        i3 = ord(_tuple[2])
        i4 = ord(_tuple[3])
        expr = sbox_mul3[i1] ^ sbox[i2] ^ sbox[i3] ^ sbox_mul2[i4] ^ sboxInv[ord(c_text[11]) ^ k171] ^ k163 ^ k167
        if not expr:
          if x4_x5_x6_x7_k163_k167_k171.has_key(_tuple):            
            x4_x5_x6_x7_k163_k167_k171[_tuple].append(''.join(map(chr, (k163, k167, k171))))
          else:
            x4_x5_x6_x7_k163_k167_k171.update({_tuple : [''.join(map(chr, (k163, k167, k171)))]})
          counter += 1

print "x4_x5_x6_x7_k163_k167_k171", math.log(counter, 2)
valid_sub_key = ''.join(map(chr, (key_round_10_valid[3], key_round_10_valid[7], key_round_10_valid[11])))
f = False
for k in x4_x5_x6_x7_k163_k167_k171:
  if f:
    break
  for v in x4_x5_x6_x7_k163_k167_k171[k]:
    if v == valid_sub_key:
      f = True
      break
if f:
  print "x4_x5_x6_x7_k163_k167_k171 have the key"
else:
  print "x4_x5_x6_x7_k163_k167_k171 have not the key"

x4_x5_x6_x7_k160_k162_k164_k166_k174 = {}
counter = 0
for k in x4_x5_x6_x7_k160_k164:
  try:
    items = x4_x5_x6_x7_k162_k166_k174[k]
    items2 = x4_x5_x6_x7_k160_k164[k]
  except:
    continue
  for v in items:
    for v2 in items2:   
      if x4_x5_x6_x7_k160_k162_k164_k166_k174.has_key(k):
        x4_x5_x6_x7_k160_k162_k164_k166_k174[k].append(''.join((v2[0], v[0], v2[1], v[1], v[2])))
      else:
        x4_x5_x6_x7_k160_k162_k164_k166_k174.update({k : [''.join((v2[0], v[0], v2[1], v[1], v[2]))]})
      counter += 1     

print "x4_x5_x6_x7_k160_k162_k164_k166_k174", math.log(counter, 2)
valid_sub_key = ''.join(map(chr, (key_round_10_valid[0], key_round_10_valid[2], key_round_10_valid[4], key_round_10_valid[6], key_round_10_valid[14])))
f = False
for k in x4_x5_x6_x7_k160_k162_k164_k166_k174:
  if f:
    break
  for v in x4_x5_x6_x7_k160_k162_k164_k166_k174[k]:
    if v == valid_sub_key:
      f = True
      break
if f:
  print "x4_x5_x6_x7_k160_k162_k164_k166_k174 have the key"
else:
  print "x4_x5_x6_x7_k160_k162_k164_k166_k174 have not the key"

x4_x5_x6_x7_k162_k166_k174 = None
x4_x5_x6_x7_k160_k164 = None


x4_x5_x6_x7_k161_k163_k165_k167_k171 = {}
counter = 0
for k in x4_x5_x6_x7_k163_k167_k171:
  try:
    items = x4_x5_x6_x7_k163_k167_k171[k]
    items2 = x4_x5_x6_x7_k161_k165[k]
  except:
    continue
  for v in items:
    for v2 in items2:   
      if x4_x5_x6_x7_k161_k163_k165_k167_k171.has_key(k):
        x4_x5_x6_x7_k161_k163_k165_k167_k171[k].append(''.join((v2[0], v[0], v2[1], v[1], v[2])))
      else:
        x4_x5_x6_x7_k161_k163_k165_k167_k171.update({k : [''.join((v2[0], v[0], v2[1], v[1], v[2]))]})
      counter += 1     

print "x4_x5_x6_x7_k161_k163_k165_k167_k171", math.log(counter, 2)
valid_sub_key = ''.join(map(chr, (key_round_10_valid[1], key_round_10_valid[3], key_round_10_valid[5], key_round_10_valid[7], key_round_10_valid[11])))
f = False
for k in x4_x5_x6_x7_k161_k163_k165_k167_k171:
  if f:
    break
  for v in x4_x5_x6_x7_k161_k163_k165_k167_k171[k]:
    if v == valid_sub_key:
      f = True
      break
if f:
  print "x4_x5_x6_x7_k161_k163_k165_k167_k171 have the key"
else:
  print "x4_x5_x6_x7_k161_k163_k165_k167_k171 have not the key"

x4_x5_x6_x7_k163_k167_k171 = None
x4_x5_x6_x7_k161_k165 = None

k160_k161_k162_k163_k164_k165_k166_k167_k171_k174 = {}
counter = 0
for k in x4_x5_x6_x7_k161_k163_k165_k167_k171:
  try:
    items = x4_x5_x6_x7_k161_k163_k165_k167_k171[k]
    items2 = x4_x5_x6_x7_k160_k162_k164_k166_k174[k]
  except:
    continue
  for v in items:
    for v2 in items2:   
      kkk = ''.join((v2[0], v[0], v2[1], v[1], v2[2], v[2], v2[3], v[3], v[4], v2[4]))
      if not k160_k161_k162_k163_k164_k165_k166_k167_k171_k174.has_key(kkk):
        k160_k161_k162_k163_k164_k165_k166_k167_k171_k174.update({kkk : 0})
        counter += 1     

print "k160_k161_k162_k163_k164_k165_k166_k167_k171_k174", math.log(len(k160_k161_k162_k163_k164_k165_k166_k167_k171_k174), 2)
valid_sub_key = ''.join(map(chr, (key_round_10_valid[0], key_round_10_valid[1], key_round_10_valid[2], key_round_10_valid[3], key_round_10_valid[4], key_round_10_valid[5], key_round_10_valid[6], key_round_10_valid[7], key_round_10_valid[11], key_round_10_valid[14])))
f = False
for k in k160_k161_k162_k163_k164_k165_k166_k167_k171_k174:
  if k == valid_sub_key:
    f = True
    break
if f:
  print "k160_k161_k162_k163_k164_k165_k166_k167_k171_k174 have the key"
else:
  print "k160_k161_k162_k163_k164_k165_k166_k167_k171_k174 have not the key"

x4_x5_x6_x7 = None
x4_x5_x6_x7_k161_k163_k165_k167_k171 = None
x4_x5_x6_x7_k160_k162_k164_k166_k174 = None

counter = 0
'''     0    1   2    3   4    5    6    7    8    9'''
hash_k160_k161_k162_k163_k164_k165_k166_k167_k171_k174 = {}
for k in k160_k161_k162_k163_k164_k165_k166_k167_k171_k174:
  new_key = ''.join((k[2], k[4], k[5], k[6], k[7], k[8]))
  new_value = ''.join((k[0], k[1], k[3], k[9]))
  counter += 1
  if hash_k160_k161_k162_k163_k164_k165_k166_k167_k171_k174.has_key(new_key):
    hash_k160_k161_k162_k163_k164_k165_k166_k167_k171_k174[new_key].append(new_value)
  else:
    hash_k160_k161_k162_k163_k164_k165_k166_k167_k171_k174.update({new_key: [new_value]})
  k160_k161_k162_k163_k164_k165_k166_k167_k171_k174[k] = None

k160_k161_k162_k163_k164_k165_k166_k167_k171_k174 = None

'''-----------------------------------------------------------------------'''
'''
Group 3 Eq -----------------------------------------------------------------------
'''
x8_x9_x10_x11 = pow(2, 16) * [None]
counter = 0

x1, y1 = get_T_list(last_2_round_trace[8])
x2, y2 = get_T_list(last_2_round_trace[9])
x3, y3 = get_T_list(last_2_round_trace[10])
x4, y4 = get_T_list(last_2_round_trace[11])

for i1 in xrange(x1, y1):
  for i2 in xrange(x2, y2):
    for i3 in xrange(x3, y3):
      for i4 in xrange(x4, y4):
        x8_x9_x10_x11[counter] = ''.join(map(chr, (i1, i2, i3, i4)))
        counter += 1


x8_x9_x10_x11 = filter(lambda _: _ != None, tuple(set(x8_x9_x10_x11))) 

counter = 0
new_x8_x9_x10_x11 = pow(2, 16) * [None]

for _tuple in x8_x9_x10_x11:
  i1 = ord(_tuple[0])
  i2 = ord(_tuple[1])
  i3 = ord(_tuple[2])
  i4 = ord(_tuple[3])
  f = False
  for k168 in key_round_10[8]:
    if f:
      break
    for k164 in key_round_10[4]:
      expr = sbox_mul2[i1] ^ sbox_mul3[i2] ^ sbox[i3] ^ sbox[i4] ^ sboxInv[ord(c_text[8]) ^ k168] ^ k168 ^ k164
      if not expr:
        f = True
        break

  if not f:
    continue

  f = False
  for k169 in key_round_10[9]:
    if f:
      break
    for k165 in key_round_10[5]:
      expr = sbox[i1] ^ sbox_mul2[i2] ^ sbox_mul3[i3] ^ sbox[i4] ^ sboxInv[ord(c_text[5]) ^ k165] ^ k169 ^ k165
      if not expr:
        f = True
        break

  if not f:
    continue
  
  f = False
  for k162 in key_round_10[2]:
    if f:
      break
    for k166 in key_round_10[6]:
      if f:
        break
      for k170 in key_round_10[10]:
        expr = sbox[i1] ^ sbox[i2] ^ sbox_mul2[i3] ^ sbox_mul3[i4] ^ sboxInv[ord(c_text[2]) ^ k162] ^ k170 ^ k166
        if not expr:
          f = True
          break

  if not f:
    continue

  f = False
  for k175 in key_round_10[15]:
    if f:
      break
    for k167 in key_round_10[7]:
      if f:
        break
      for k171 in key_round_10[11]:
        expr = sbox_mul3[i1] ^ sbox[i2] ^ sbox[i3] ^ sbox_mul2[i4] ^ sboxInv[ord(c_text[15]) ^ k175] ^ k167 ^ k171
        if not expr:
          f = True
          break

  if not f:
    continue

  if f:
    new_x8_x9_x10_x11[counter] = ''.join(map(chr, (i1, i2, i3, i4)))
    counter += 1


x8_x9_x10_x11 = filter(lambda _: _ != None, tuple(set(new_x8_x9_x10_x11)))
print "x8_x9_x10_x11", math.log(len(x8_x9_x10_x11), 2)

counter = 0
x8_x9_x10_x11_k162_k166_k170 = {}

for k162 in key_round_10[2]:
  for k166 in key_round_10[6]:
    for k170 in key_round_10[10]:
      for _tuple in x8_x9_x10_x11:
        i1 = ord(_tuple[0])
        i2 = ord(_tuple[1])
        i3 = ord(_tuple[2])
        i4 = ord(_tuple[3])
        expr = sbox[i1] ^ sbox[i2] ^ sbox_mul2[i3] ^ sbox_mul3[i4] ^ sboxInv[ord(c_text[2]) ^ k162] ^ k170 ^ k166
        if not expr:
          if x8_x9_x10_x11_k162_k166_k170.has_key(_tuple):            
            x8_x9_x10_x11_k162_k166_k170[_tuple].append(''.join(map(chr, (k162, k166, k170))))
          else:
            x8_x9_x10_x11_k162_k166_k170.update({_tuple : [''.join(map(chr, (k162, k166, k170)))]})
          counter += 1

print "x8_x9_x10_x11_k162_k166_k170", math.log(counter, 2)
valid_sub_key = ''.join(map(chr, (key_round_10_valid[2], key_round_10_valid[6], key_round_10_valid[10])))
f = False
for k in x8_x9_x10_x11_k162_k166_k170:
  if f:
    break
  for v in x8_x9_x10_x11_k162_k166_k170[k]:
    if v == valid_sub_key:
      f = True
      break
if f:
  print "x8_x9_x10_x11_k162_k166_k170 have the key"
else:
  print "x8_x9_x10_x11_k162_k166_k170 have not the key"


counter = 0
x8_x9_x10_x11_k165_k169 = {}

for k169 in key_round_10[9]:
  for k165 in key_round_10[5]:
    for _tuple in x8_x9_x10_x11:
      i1 = ord(_tuple[0])
      i2 = ord(_tuple[1])
      i3 = ord(_tuple[2])
      i4 = ord(_tuple[3])
      expr = sbox[i1] ^ sbox_mul2[i2] ^ sbox_mul3[i3] ^ sbox[i4] ^ sboxInv[ord(c_text[5]) ^ k165] ^ k169 ^ k165
      if not expr: 
        if x8_x9_x10_x11_k165_k169.has_key(_tuple):            
          x8_x9_x10_x11_k165_k169[_tuple].append(''.join(map(chr, (k165, k169))))
        else:
          x8_x9_x10_x11_k165_k169.update({_tuple : [''.join(map(chr, (k165, k169)))]})
        counter += 1

print "x8_x9_x10_x11_k165_k169", math.log(counter, 2)
valid_sub_key = ''.join(map(chr, (key_round_10_valid[5], key_round_10_valid[9])))
f = False
for k in x8_x9_x10_x11_k165_k169:
  if f:
    break
  for v in x8_x9_x10_x11_k165_k169[k]:
    if v == valid_sub_key:
      f = True
      break
if f:
  print "x8_x9_x10_x11_k165_k169 have the key"
else:
  print "x8_x9_x10_x11_k165_k169 have not the key"


counter = 0
x8_x9_x10_x11_k164_k168 = {}

for k168 in key_round_10[8]:
  for k164 in key_round_10[4]:
    for _tuple in x8_x9_x10_x11:
      i1 = ord(_tuple[0])
      i2 = ord(_tuple[1])
      i3 = ord(_tuple[2])
      i4 = ord(_tuple[3])
      expr = sbox_mul2[i1] ^ sbox_mul3[i2] ^ sbox[i3] ^ sbox[i4] ^ sboxInv[ord(c_text[8]) ^ k168] ^ k168 ^ k164
      if not expr:
        if x8_x9_x10_x11_k164_k168.has_key(_tuple):            
          x8_x9_x10_x11_k164_k168[_tuple].append(''.join(map(chr, (k164, k168))))
        else:
          x8_x9_x10_x11_k164_k168.update({_tuple : [''.join(map(chr, (k164, k168)))]})
        counter += 1

print "x8_x9_x10_x11_k164_k168", math.log(counter, 2)
valid_sub_key = ''.join(map(chr, (key_round_10_valid[4], key_round_10_valid[8])))
f = False
for k in x8_x9_x10_x11_k164_k168:
  if f:
    break
  for v in x8_x9_x10_x11_k164_k168[k]:
    if v == valid_sub_key:
      f = True
      break
if f:
  print "x8_x9_x10_x11_k164_k168 have the key"
else:
  print "x8_x9_x10_x11_k164_k168 have not the key"

counter = 0
x8_x9_x10_x11_k167_k171_k175 = {}

for k175 in key_round_10[15]:
  for k167 in key_round_10[7]:
    for k171 in key_round_10[11]:
      for _tuple in x8_x9_x10_x11:
        i1 = ord(_tuple[0])
        i2 = ord(_tuple[1])
        i3 = ord(_tuple[2])
        i4 = ord(_tuple[3])
        expr = sbox_mul3[i1] ^ sbox[i2] ^ sbox[i3] ^ sbox_mul2[i4] ^ sboxInv[ord(c_text[15]) ^ k175] ^ k171 ^ k167
        if not expr:
          if x8_x9_x10_x11_k167_k171_k175.has_key(_tuple):            
            x8_x9_x10_x11_k167_k171_k175[_tuple].append(''.join(map(chr, (k167, k171, k175))))
          else:
            x8_x9_x10_x11_k167_k171_k175.update({_tuple : [''.join(map(chr, (k167, k171, k175)))]})
          counter += 1

print "x8_x9_x10_x11_k167_k171_k175", math.log(counter, 2)
valid_sub_key = ''.join(map(chr, (key_round_10_valid[7], key_round_10_valid[11], key_round_10_valid[15])))
f = False
for k in x8_x9_x10_x11_k167_k171_k175:
  if f:
    break
  for v in x8_x9_x10_x11_k167_k171_k175[k]:
    if v == valid_sub_key:
      f = True
      break
if f:
  print "x8_x9_x10_x11_k167_k171_k175 have the key"
else:
  print "x8_x9_x10_x11_k167_k171_k175 have not the key"

x8_x9_x10_x11_k162_k164_k166_k168_k170 = {}
counter = 0
for k in x8_x9_x10_x11_k164_k168:
  try:
    items = x8_x9_x10_x11_k162_k166_k170[k]
    items2 = x8_x9_x10_x11_k164_k168[k]
  except:
    continue
  for v in items:
    for v2 in items2:   
      if x8_x9_x10_x11_k162_k164_k166_k168_k170.has_key(k):
        x8_x9_x10_x11_k162_k164_k166_k168_k170[k].append(''.join((v[0], v2[0], v[1], v2[1], v[2])))
      else:
        x8_x9_x10_x11_k162_k164_k166_k168_k170.update({k : [''.join((v[0], v2[0], v[1], v2[1], v[2]))]})
      counter += 1     

print "x8_x9_x10_x11_k162_k164_k166_k168_k170", math.log(counter, 2)
valid_sub_key = ''.join(map(chr, (key_round_10_valid[2], key_round_10_valid[4], key_round_10_valid[6], key_round_10_valid[8], key_round_10_valid[10])))
f = False
for k in x8_x9_x10_x11_k162_k164_k166_k168_k170:
  if f:
    break
  for v in x8_x9_x10_x11_k162_k164_k166_k168_k170[k]:
    if v == valid_sub_key:
      f = True
      break
if f:
  print "x8_x9_x10_x11_k162_k164_k166_k168_k170 have the key"
else:
  print "x8_x9_x10_x11_k162_k164_k166_k168_k170 have not the key"

x8_x9_x10_x11_k162_k166_k170 = None
x8_x9_x10_x11_k164_k168 = None

x8_x9_x10_x11_k165_k167_k169_k171_k175 = {}
counter = 0
for k in x8_x9_x10_x11_k165_k169:
  try:
    items = x8_x9_x10_x11_k165_k169[k]
    items2 = x8_x9_x10_x11_k167_k171_k175[k]
  except:
    continue
  for v in items:
    for v2 in items2:   
      if x8_x9_x10_x11_k165_k167_k169_k171_k175.has_key(k):
        x8_x9_x10_x11_k165_k167_k169_k171_k175[k].append(''.join((v[0], v2[0], v[1], v2[1], v2[2])))
      else:
        x8_x9_x10_x11_k165_k167_k169_k171_k175.update({k : [''.join((v[0], v2[0], v[1], v2[1], v2[2]))]})
      counter += 1     

print "x8_x9_x10_x11_k165_k167_k169_k171_k175", math.log(counter, 2)
valid_sub_key = ''.join(map(chr, (key_round_10_valid[5], key_round_10_valid[7], key_round_10_valid[9], key_round_10_valid[11], key_round_10_valid[15])))
f = False
for k in x8_x9_x10_x11_k165_k167_k169_k171_k175:
  if f:
    break
  for v in x8_x9_x10_x11_k165_k167_k169_k171_k175[k]:
    if v == valid_sub_key:
      f = True
      break
if f:
  print "x8_x9_x10_x11_k165_k167_k169_k171_k175 have the key"
else:
  print "x8_x9_x10_x11_k165_k167_k169_k171_k175 have not the key"

x8_x9_x10_x11_k165_k169 = None
x8_x9_x10_x11_k167_k171_k175 = None

k162_k164_k165_k166_k167_k168_k169_k170_k171_k175 = {}
counter = 0
for k in x8_x9_x10_x11_k162_k164_k166_k168_k170:
  try:
    items = x8_x9_x10_x11_k162_k164_k166_k168_k170[k]
    items2 = x8_x9_x10_x11_k165_k167_k169_k171_k175[k]
  except:
    continue
  for v in items:
    for v2 in items2:   
      kkk = ''.join((v[0], v[1], v2[0], v[2], v2[1], v[3], v2[2], v[4], v2[3], v2[4]))
      if not k162_k164_k165_k166_k167_k168_k169_k170_k171_k175.has_key(kkk):
        k162_k164_k165_k166_k167_k168_k169_k170_k171_k175.update({kkk : 0})
        counter += 1     

print "k162_k164_k165_k166_k167_k168_k169_k170_k171_k175", math.log(len(k162_k164_k165_k166_k167_k168_k169_k170_k171_k175), 2)
valid_sub_key = ''.join(map(chr, (key_round_10_valid[2], key_round_10_valid[4], key_round_10_valid[5], key_round_10_valid[6], key_round_10_valid[7], key_round_10_valid[8], key_round_10_valid[9], key_round_10_valid[10], key_round_10_valid[11], key_round_10_valid[15])))
f = False
for k in k162_k164_k165_k166_k167_k168_k169_k170_k171_k175:
  if k == valid_sub_key:
    f = True
    break
if f:
  print "k162_k164_k165_k166_k167_k168_k169_k170_k171_k175 have the key"
else:
  print "k162_k164_k165_k166_k167_k168_k169_k170_k171_k175 have not the key"

x8_x9_x10_x11 = None
x8_x9_x10_x11_k162_k164_k166_k168_k170 = None
x8_x9_x10_x11_k165_k167_k169_k171_k175 = None

counter = 0
'''     0    1   2    3   4    5    6    7    8    9'''
hash_k162_k164_k165_k166_k167_k168_k169_k170_k171_k175 = {}
for k in k162_k164_k165_k166_k167_k168_k169_k170_k171_k175:
  new_key = ''.join((k[0], k[1], k[2], k[3], k[4], k[8]))
  new_value = ''.join((k[5], k[6], k[7], k[9]))
  counter += 1
  if hash_k162_k164_k165_k166_k167_k168_k169_k170_k171_k175.has_key(new_key):
    hash_k162_k164_k165_k166_k167_k168_k169_k170_k171_k175[new_key].append(new_value)
  else:
    hash_k162_k164_k165_k166_k167_k168_k169_k170_k171_k175.update({new_key: [new_value]})
  k162_k164_k165_k166_k167_k168_k169_k170_k171_k175[k] = None

k162_k164_k165_k166_k167_k168_k169_k170_k171_k175 = None
'''-----------------------------------------------------------------------'''

'''-----------------------------------------------------------------------'''
k160_k161_k162_k163_k164_k165_k166_k167_k168_k169_k170_k171_k174_k175 = {}
counter = 0
for k in hash_k162_k164_k165_k166_k167_k168_k169_k170_k171_k175:
  if hash_k160_k161_k162_k163_k164_k165_k166_k167_k171_k174.has_key(k):
    try:
      items = hash_k160_k161_k162_k163_k164_k165_k166_k167_k171_k174[k]
      items2 = hash_k162_k164_k165_k166_k167_k168_k169_k170_k171_k175[k]
    except:
      continue
    for v in items:
      for v2 in items2:   
        kkk = ''.join((v[0], v[1], k[0], v[2], k[1], k[2], k[3], k[4], v2[0], v2[1], v2[2], k[5], v[3], v2[3]))
        if not k160_k161_k162_k163_k164_k165_k166_k167_k168_k169_k170_k171_k174_k175.has_key(kkk):
          k160_k161_k162_k163_k164_k165_k166_k167_k168_k169_k170_k171_k174_k175.update({kkk : 0})
          counter += 1
  
  hash_k162_k164_k165_k166_k167_k168_k169_k170_k171_k175[k] = None
  if hash_k160_k161_k162_k163_k164_k165_k166_k167_k171_k174.has_key(k):
    hash_k160_k161_k162_k163_k164_k165_k166_k167_k171_k174[k] = None

hash_k160_k161_k162_k163_k164_k165_k166_k167_k171_k174 = None
hash_k162_k164_k165_k166_k167_k168_k169_k170_k171_k175 = None

print "k160_k161_k162_k163_k164_k165_k166_k167_k168_k169_k170_k171_k174_k175", math.log(counter, 2)
valid_sub_key = ''.join(map(chr, (key_round_10_valid[0], key_round_10_valid[1], key_round_10_valid[2], key_round_10_valid[3], key_round_10_valid[4], key_round_10_valid[5], key_round_10_valid[6], key_round_10_valid[7], key_round_10_valid[8], key_round_10_valid[9], key_round_10_valid[10], key_round_10_valid[11], key_round_10_valid[14], key_round_10_valid[15])))
f = False
for k in k160_k161_k162_k163_k164_k165_k166_k167_k168_k169_k170_k171_k174_k175:
  if k == valid_sub_key:
    f = True
    break
if f:
  print "k160_k161_k162_k163_k164_k165_k166_k167_k168_k169_k170_k171_k174_k175 have the key"
else:
  print "k160_k161_k162_k163_k164_k165_k166_k167_k168_k169_k170_k171_k174_k175 have not the key"


#160 161 162 164 165 167

counter = 0
'''     0    1    2    3   4    5    6   7    8    9   10   11   12   13'''
hash_k160_k161_k162_k163_k164_k165_k166_k167_k168_k169_k170_k171_k174_k175 = {}
for k in k160_k161_k162_k163_k164_k165_k166_k167_k168_k169_k170_k171_k174_k175:
  new_key = ''.join((k[3], k[6], k[8], k[9], k[10], k[11], k[12], k[13]))
  new_value = ''.join((k[0], k[1], k[2], k[4], k[5], k[7]))
  counter += 1
  if hash_k160_k161_k162_k163_k164_k165_k166_k167_k168_k169_k170_k171_k174_k175.has_key(new_key):
    hash_k160_k161_k162_k163_k164_k165_k166_k167_k168_k169_k170_k171_k174_k175[new_key].append(new_value)
  else:
    hash_k160_k161_k162_k163_k164_k165_k166_k167_k168_k169_k170_k171_k174_k175.update({new_key: [new_value]})
  k160_k161_k162_k163_k164_k165_k166_k167_k168_k169_k170_k171_k174_k175[k] = None

k160_k161_k162_k163_k164_k165_k166_k167_k168_k169_k170_k171_k174_k175 = None

'''-------------------------------------------------------------------------------'''

'''
Group 4 Eq -----------------------------------------------------------------------
'''
x12_x13_x14_x15 = pow(2, 16) * [None]
counter = 0

x1, y1 = get_T_list(last_2_round_trace[12])
x2, y2 = get_T_list(last_2_round_trace[13])
x3, y3 = get_T_list(last_2_round_trace[14])
x4, y4 = get_T_list(last_2_round_trace[15])

for i1 in xrange(x1, y1):
  for i2 in xrange(x2, y2):
    for i3 in xrange(x3, y3):
      for i4 in xrange(x4, y4):
        x12_x13_x14_x15[counter] = ''.join(map(chr, (i1, i2, i3, i4)))
        counter += 1


x12_x13_x14_x15 = filter(lambda _: _ != None, tuple(set(x12_x13_x14_x15))) 

counter = 0
new_x12_x13_x14_x15 = pow(2, 16) * [None]

for _tuple in x12_x13_x14_x15:
  i1 = ord(_tuple[0])
  i2 = ord(_tuple[1])
  i3 = ord(_tuple[2])
  i4 = ord(_tuple[3])
  f = False
  for k168 in key_round_10[8]:
    if f:
      break
    for k172 in key_round_10[12]:
      expr = sbox_mul2[i1] ^ sbox_mul3[i2] ^ sbox[i3] ^ sbox[i4] ^ sboxInv[ord(c_text[12]) ^ k172] ^ k168 ^ k172
      if not expr:
        f = True
        break

  if not f:
    continue

  f = False
  for k169 in key_round_10[9]:
    if f:
      break
    for k173 in key_round_10[13]:
      expr = sbox[i1] ^ sbox_mul2[i2] ^ sbox_mul3[i3] ^ sbox[i4] ^ sboxInv[ord(c_text[9]) ^ k169] ^ k169 ^ k173
      if not expr:
        f = True
        break

  if not f:
    continue
  
  f = False
  for k174 in key_round_10[14]:
    if f:
      break
    for k166 in key_round_10[6]:
      if f:
        break
      for k170 in key_round_10[10]:
        expr = sbox[i1] ^ sbox[i2] ^ sbox_mul2[i3] ^ sbox_mul3[i4] ^ sboxInv[ord(c_text[6]) ^ k166] ^ k170 ^ k174
        if not expr:
          f = True
          break

  if not f:
    continue

  f = False
  for k175 in key_round_10[15]:
    if f:
      break
    for k163 in key_round_10[3]:
      if f:
        break
      for k171 in key_round_10[11]:
        expr = sbox_mul3[i1] ^ sbox[i2] ^ sbox[i3] ^ sbox_mul2[i4] ^ sboxInv[ord(c_text[3]) ^ k163] ^ k175 ^ k171
        if not expr:
          f = True
          break

  if not f:
    continue

  if f:
    new_x12_x13_x14_x15[counter] = ''.join(map(chr, (i1, i2, i3, i4)))
    counter += 1


x12_x13_x14_x15 = filter(lambda _: _ != None, tuple(set(new_x12_x13_x14_x15)))
print "x12_x13_x14_x15", math.log(len(x12_x13_x14_x15), 2)

counter = 0
x12_x13_x14_x15_k166_k170_k174 = {}

for k174 in key_round_10[14]:
  for k166 in key_round_10[6]:
    for k170 in key_round_10[10]:
      for _tuple in x12_x13_x14_x15:
        i1 = ord(_tuple[0])
        i2 = ord(_tuple[1])
        i3 = ord(_tuple[2])
        i4 = ord(_tuple[3])
        expr = sbox[i1] ^ sbox[i2] ^ sbox_mul2[i3] ^ sbox_mul3[i4] ^ sboxInv[ord(c_text[6]) ^ k166] ^ k170 ^ k174
        if not expr:
          if x12_x13_x14_x15_k166_k170_k174.has_key(_tuple):
            x12_x13_x14_x15_k166_k170_k174[_tuple].append(''.join(map(chr, (k166, k170, k174))))
          else:
            x12_x13_x14_x15_k166_k170_k174.update({_tuple : [''.join(map(chr, (k166, k170, k174)))]})
          counter += 1

print "x12_x13_x14_x15_k166_k170_k174", math.log(counter, 2)
valid_sub_key = ''.join(map(chr, (key_round_10_valid[6], key_round_10_valid[10], key_round_10_valid[14])))
f = False
for k in x12_x13_x14_x15_k166_k170_k174:
  if f:
    break
  for v in x12_x13_x14_x15_k166_k170_k174[k]:
    if v == valid_sub_key:
      f = True
      break
if f:
  print "x12_x13_x14_x15_k166_k170_k174 have the key"
else:
  print "x12_x13_x14_x15_k166_k170_k174 have not the key"


counter = 0
x12_x13_x14_x15_k169_k173 = {}

for k169 in key_round_10[9]:
  for k173 in key_round_10[13]:
    for _tuple in x12_x13_x14_x15:
      i1 = ord(_tuple[0])
      i2 = ord(_tuple[1])
      i3 = ord(_tuple[2])
      i4 = ord(_tuple[3])
      expr = sbox[i1] ^ sbox_mul2[i2] ^ sbox_mul3[i3] ^ sbox[i4] ^ sboxInv[ord(c_text[9]) ^ k169] ^ k169 ^ k173
      if not expr: 
        if x12_x13_x14_x15_k169_k173.has_key(_tuple):            
         x12_x13_x14_x15_k169_k173[_tuple].append(''.join(map(chr, (k169, k173))))
        else:
          x12_x13_x14_x15_k169_k173.update({_tuple : [''.join(map(chr, (k169, k173)))]})
        counter += 1

print "x12_x13_x14_x15_k169_k173", math.log(counter, 2)
valid_sub_key = ''.join(map(chr, (key_round_10_valid[9], key_round_10_valid[13])))
f = False
for k in x12_x13_x14_x15_k169_k173:
  if f:
    break
  for v in x12_x13_x14_x15_k169_k173[k]:
    if v == valid_sub_key:
      f = True
      break
if f:
  print "x12_x13_x14_x15_k169_k173 have the key"
else:
  print "x12_x13_x14_x15_k169_k173 have not the key"


counter = 0
x12_x13_x14_x15_k168_k172 = {}

for k168 in key_round_10[8]:
  for k172 in key_round_10[12]:
    for _tuple in x12_x13_x14_x15:
      i1 = ord(_tuple[0])
      i2 = ord(_tuple[1])
      i3 = ord(_tuple[2])
      i4 = ord(_tuple[3])
      expr = sbox_mul2[i1] ^ sbox_mul3[i2] ^ sbox[i3] ^ sbox[i4] ^ sboxInv[ord(c_text[12]) ^ k172] ^ k168 ^ k172
      if not expr:
        if x12_x13_x14_x15_k168_k172.has_key(_tuple):            
          x12_x13_x14_x15_k168_k172[_tuple].append(''.join(map(chr, (k168, k172))))
        else:
          x12_x13_x14_x15_k168_k172.update({_tuple : [''.join(map(chr, (k168, k172)))]})
        counter += 1

print "x12_x13_x14_x15_k168_k172", math.log(counter, 2)
valid_sub_key = ''.join(map(chr, (key_round_10_valid[8], key_round_10_valid[12])))
f = False
for k in x12_x13_x14_x15_k168_k172:
  if f:
    break
  for v in x12_x13_x14_x15_k168_k172[k]:
    if v == valid_sub_key:
      f = True
      break
if f:
  print "x12_x13_x14_x15_k168_k172 have the key"
else:
  print "x12_x13_x14_x15_k168_k172 have not the key"

counter = 0
x12_x13_x14_x15_k163_k171_k175 = {}

for k175 in key_round_10[15]:
  for k163 in key_round_10[3]:
    for k171 in key_round_10[11]:
      for _tuple in x12_x13_x14_x15:
        i1 = ord(_tuple[0])
        i2 = ord(_tuple[1])
        i3 = ord(_tuple[2])
        i4 = ord(_tuple[3])
        expr = sbox_mul3[i1] ^ sbox[i2] ^ sbox[i3] ^ sbox_mul2[i4] ^ sboxInv[ord(c_text[3]) ^ k163] ^ k171 ^ k175
        if not expr:
          if x12_x13_x14_x15_k163_k171_k175.has_key(_tuple):            
            x12_x13_x14_x15_k163_k171_k175[_tuple].append(''.join(map(chr, (k163, k171, k175))))
          else:
            x12_x13_x14_x15_k163_k171_k175.update({_tuple : [''.join(map(chr, (k163, k171, k175)))]})
          counter += 1

print "x12_x13_x14_x15_k163_k171_k175", math.log(counter, 2)
valid_sub_key = ''.join(map(chr, (key_round_10_valid[3], key_round_10_valid[11], key_round_10_valid[15])))
f = False
for k in x12_x13_x14_x15_k163_k171_k175:
  if f:
    break
  for v in x12_x13_x14_x15_k163_k171_k175[k]:
    if v == valid_sub_key:
      f = True
      break
if f:
  print "x12_x13_x14_x15_k163_k171_k175 have the key"
else:
  print "x12_x13_x14_x15_k163_k171_k175 have not the key"


x12_x13_x14_x15_k166_k168_k170_k172_k174 = {}
counter = 0
for k in x12_x13_x14_x15_k168_k172:
  try:
    items = x12_x13_x14_x15_k166_k170_k174[k]
    items2 = x12_x13_x14_x15_k168_k172[k]
  except:
    continue
  for v in items:
    for v2 in items2:   
      if x12_x13_x14_x15_k166_k168_k170_k172_k174.has_key(k):
        x12_x13_x14_x15_k166_k168_k170_k172_k174[k].append(''.join((v[0], v2[0], v[1], v2[1], v[2])))
      else:
        x12_x13_x14_x15_k166_k168_k170_k172_k174.update({k : [''.join((v[0], v2[0], v[1], v2[1], v[2]))]})
      counter += 1     

print "x12_x13_x14_x15_k166_k168_k170_k172_k174", math.log(counter, 2)
valid_sub_key = ''.join(map(chr, (key_round_10_valid[6], key_round_10_valid[8], key_round_10_valid[10], key_round_10_valid[12], key_round_10_valid[14])))
f = False
for k in x12_x13_x14_x15_k166_k168_k170_k172_k174:
  if f:
    break
  for v in x12_x13_x14_x15_k166_k168_k170_k172_k174[k]:
    if v == valid_sub_key:
      f = True
      break
if f:
  print "x12_x13_x14_x15_k166_k168_k170_k172_k174 have the key"
else:
  print "x12_x13_x14_x15_k166_k168_k170_k172_k174 have not the key"

x12_x13_x14_x15_k166_k170_k174 = None
x12_x13_x14_x15_k168_k172 = None


x12_x13_x14_x15_k163_k169_k171_k173_k175 = {}

counter = 0
for k in x12_x13_x14_x15_k169_k173:
  try:
    items = x12_x13_x14_x15_k169_k173[k]
    items2 = x12_x13_x14_x15_k163_k171_k175[k]
  except:
    continue
  for v in items:
    for v2 in items2:   
      if x12_x13_x14_x15_k163_k169_k171_k173_k175.has_key(k):
        x12_x13_x14_x15_k163_k169_k171_k173_k175[k].append(''.join((v2[0], v[0], v2[1], v[1], v2[2])))
      else:
        x12_x13_x14_x15_k163_k169_k171_k173_k175.update({k : [''.join((v2[0], v[0], v2[1], v[1], v2[2]))]})
      counter += 1     

print "x12_x13_x14_x15_k163_k169_k171_k173_k175", math.log(counter, 2)
valid_sub_key = ''.join(map(chr, (key_round_10_valid[3], key_round_10_valid[9], key_round_10_valid[11], key_round_10_valid[13], key_round_10_valid[15])))
f = False
for k in x12_x13_x14_x15_k163_k169_k171_k173_k175:
  if f:
    break
  for v in x12_x13_x14_x15_k163_k169_k171_k173_k175[k]:
    if v == valid_sub_key:
      f = True
      break
if f:
  print "x12_x13_x14_x15_k163_k169_k171_k173_k175 have the key"
else:
  print "x12_x13_x14_x15_k163_k169_k171_k173_k175 have not the key"

x12_x13_x14_x15_k169_k173 = None
x12_x13_x14_x15_k163_k171_k175 = None


k163_k166_k168_k169_k170_k171_k172_k173_k174_k175 = {}
counter = 0
for k in x12_x13_x14_x15_k163_k169_k171_k173_k175:
  try:
    items = x12_x13_x14_x15_k163_k169_k171_k173_k175[k]
    items2 = x12_x13_x14_x15_k166_k168_k170_k172_k174[k]
  except:
    continue
  for v in items:
    for v2 in items2:   
      kkk = ''.join((v[0], v2[0], v2[1], v[1], v2[2], v[2], v2[3], v[3], v2[4], v[4]))
      if not k163_k166_k168_k169_k170_k171_k172_k173_k174_k175.has_key(kkk):
        k163_k166_k168_k169_k170_k171_k172_k173_k174_k175.update({kkk : 0})
        counter += 1     

print "k163_k166_k168_k169_k170_k171_k172_k173_k174_k175", math.log(len(k163_k166_k168_k169_k170_k171_k172_k173_k174_k175), 2)
valid_sub_key = ''.join(map(chr, (key_round_10_valid[3], key_round_10_valid[6], key_round_10_valid[8], key_round_10_valid[9], key_round_10_valid[10], key_round_10_valid[11], key_round_10_valid[12], key_round_10_valid[13], key_round_10_valid[14], key_round_10_valid[15])))
f = False
for k in k163_k166_k168_k169_k170_k171_k172_k173_k174_k175:
  if k == valid_sub_key:
    f = True
    break
if f:
  print "k163_k166_k168_k169_k170_k171_k172_k173_k174_k175 have the key"
else:
  print "k163_k166_k168_k169_k170_k171_k172_k173_k174_k175 have not the key"

x12_x13_x14_x15 = None
x12_x13_x14_x15_k163_k169_k171_k173_k175 = None
x12_x13_x14_x15_k166_k168_k170_k172_k174 = None

counter = 0
'''     0    1   2    3   4    5    6    7    8    9'''
hash_k163_k166_k168_k169_k170_k171_k172_k173_k174_k175 = {}
for k in k163_k166_k168_k169_k170_k171_k172_k173_k174_k175:
  new_key = ''.join((k[0], k[1], k[2], k[3], k[4], k[5], k[8], k[9]))
  new_value = ''.join((k[6], k[7]))
  counter += 1
  if hash_k163_k166_k168_k169_k170_k171_k172_k173_k174_k175.has_key(new_key):
    hash_k163_k166_k168_k169_k170_k171_k172_k173_k174_k175[new_key].append(new_value)
  else:
    hash_k163_k166_k168_k169_k170_k171_k172_k173_k174_k175.update({new_key: [new_value]})
  k163_k166_k168_k169_k170_k171_k172_k173_k174_k175[k] = None

k163_k166_k168_k169_k170_k171_k172_k173_k174_k175 = None

'''----------------------------------------------------------------------'''

'''
163 166 168 169 170 171 174 175

172 173

160 161 162 164 165 167
'''

'''-----------------------------------------------------------------------'''
k160_k161_k162_k163_k164_k165_k166_k167_k168_k169_k170_k171_k172_k173_k174_k175 = {}
counter = 0
for k in hash_k160_k161_k162_k163_k164_k165_k166_k167_k168_k169_k170_k171_k174_k175:
  if hash_k163_k166_k168_k169_k170_k171_k172_k173_k174_k175.has_key(k):
    try:
      items = hash_k160_k161_k162_k163_k164_k165_k166_k167_k168_k169_k170_k171_k174_k175[k]
      items2 = hash_k163_k166_k168_k169_k170_k171_k172_k173_k174_k175[k]
    except:
      continue
    for v in items:
      for v2 in items2:   
        kkk = ''.join((v[0], v[1], v[2], k[0], v[3], v[4], k[1], v[5], k[2], k[3], k[4], k[5], v2[0], v2[1], k[6], k[7]))
        if not k160_k161_k162_k163_k164_k165_k166_k167_k168_k169_k170_k171_k172_k173_k174_k175.has_key(kkk):
          k160_k161_k162_k163_k164_k165_k166_k167_k168_k169_k170_k171_k172_k173_k174_k175.update({kkk : 0})
          counter += 1
  
  hash_k160_k161_k162_k163_k164_k165_k166_k167_k168_k169_k170_k171_k174_k175[k] = None
  if hash_k163_k166_k168_k169_k170_k171_k172_k173_k174_k175.has_key(k):
    hash_k163_k166_k168_k169_k170_k171_k172_k173_k174_k175[k] = None

hash_k160_k161_k162_k163_k164_k165_k166_k167_k168_k169_k170_k171_k174_k175 = None
hash_k163_k166_k168_k169_k170_k171_k172_k173_k174_k175 = None

print "k160_k161_k162_k163_k164_k165_k166_k167_k168_k169_k170_k171_k172_k173_k174_k175", math.log(counter, 2)
valid_sub_key = ''.join(map(chr, key_round_10_valid))
f = False
for k in k160_k161_k162_k163_k164_k165_k166_k167_k168_k169_k170_k171_k172_k173_k174_k175:
  if k == valid_sub_key:
    f = True
    break
if f:
  print "k160_k161_k162_k163_k164_k165_k166_k167_k168_k169_k170_k171_k172_k173_k174_k175 have the key"
else:
  print "k160_k161_k162_k163_k164_k165_k166_k167_k168_k169_k170_k171_k172_k173_k174_k175 have not the key"


'''
Group 4 Eq -----------------------------------------------------------------------
'''

x1_x2_x3_x4 = pow(2, 16) * [None]
counter = 0

x1, y1 = get_T_list(last_2_round_trace[0])
x2, y2 = get_T_list(last_2_round_trace[1])
x3, y3 = get_T_list(last_2_round_trace[2])
x4, y4 = get_T_list(last_2_round_trace[3])

for i1 in xrange(x1, y1):
  for i2 in xrange(x2, y2):
    for i3 in xrange(x3, y3):
      for i4 in xrange(x4, y4):
        x1_x2_x3_x4[counter] = ''.join(map(chr, (i1, i2, i3, i4)))
        counter += 1


x1_x2_x3_x4 = filter(lambda _: _ != None, tuple(set(x1_x2_x3_x4))) 

counter = 0
full_key = {}
for key in k160_k161_k162_k163_k164_k165_k166_k167_k168_k169_k170_k171_k172_k173_k174_k175:
  for _tuple in x1_x2_x3_x4:
    i1 = ord(_tuple[0])
    i2 = ord(_tuple[1])
    i3 = ord(_tuple[2])
    i4 = ord(_tuple[3])

    expr = sbox_mul2[i1] ^ sbox_mul3[i2] ^ sbox[i3] ^ sbox[i4] ^ sboxInv[ord(c_text[0]) ^ ord(key[0])] ^ ord(key[0]) ^ sbox[ord(key[13]) ^ ord(key[9])] ^ 0x36
    if expr:
      continue


    expr = sbox[i1] ^ sbox_mul2[i2] ^ sbox_mul3[i3] ^ sbox[i4] ^ sboxInv[ord(c_text[13]) ^ ord(key[13])] ^ ord(key[1]) ^ sbox[ord(key[14]) ^ ord(key[10])]
    if expr:
      continue

    expr = sbox[i1] ^ sbox[i2] ^ sbox_mul2[i3] ^ sbox_mul3[i4] ^ sboxInv[ord(c_text[10]) ^ ord(key[10])] ^ ord(key[2]) ^ sbox[ord(key[15]) ^ ord(key[11])]
    if expr:
      continue
    
    expr = sbox_mul3[i1] ^ sbox[i2] ^ sbox[i3] ^ sbox_mul2[i4] ^ sboxInv[ord(c_text[7]) ^ ord(key[7])] ^ ord(key[3]) ^ sbox[ord(key[12]) ^ ord(key[8])]
    if expr:
      continue

   
    full_key.update({key: 0})
    counter += 1
    break
      

print "full_key", full_key.keys(), math.log(len(full_key), 2)
valid_sub_key = ''.join(map(chr, key_round_10_valid))
f = False
for k in full_key:
  if k == valid_sub_key:
    f = True
    break
if f:
  print "full_key have the key"
else:
  print "full_key have not the key"

print "Time elapsed:", time.time() - ttc

