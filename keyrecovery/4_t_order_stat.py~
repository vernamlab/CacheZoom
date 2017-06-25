#!/usr/bin/env python

def remove_junk(lst):
  new_lst = []
  for v, v2 in lst:
    if v >= 0 and v < 32:
      new_lst.append(v)
  return new_lst

f = open('multiple_order.txt', 'r')
p_text = f.readline()
measure = []
while p_text:
  pin_trace = eval(f.readline().strip())
  _1_round = eval(f.readline().strip())
  _2_round = eval(f.readline().strip())
  measure.append({"p": eval(p_text.strip()), "pin": { "r_1" : pin_trace[0:16], "r_2" : pin_trace[16:32]}, "r_1" : remove_junk(_1_round), "r_2" : remove_junk(_2_round)})
  
  p_text = f.readline()


def false_true_positive(sample, reference): 
  true_lst_index = []
  t_p = 0
  f_p = 0
  f_n = 0
  for v in sample:
    try:
      i = reference.index(v)
      true_lst_index.append(i)
      t_p += 1
    except:
      f_p += 1

  for v in reference:
    try:
      i = sample.index(v)
    except:
      f_n += 1

  return true_lst_index, float(t_p) / len(sample), float(f_p) / len(sample), float(f_n) / len(reference)


def order_stat(true_samples):
  samples = list(true_samples)
  cnt = 0
  len_lst = len(samples)
  i = 0
  while i < len_lst:   
    j = i + 1 
    while j < len_lst:
      if samples[i] > samples[j]:
        samples.remove(samples[j])
        len_lst -= 1
        cnt += 1
        break
      j += 1
    i += 1
  return 1 - (float(cnt) / len(true_samples))
      
for m in measure:
  true_lst_index, true_pos, false_pos, false_neg =  false_true_positive(m['r_1'], m["pin"]["r_1"])
  order = order_stat(tuple(true_lst_index))
  print {"true_pos": true_pos, "false_pos": false_pos, "false_neg": false_neg, "ordered" : order}
  true_lst_index, true_pos, false_pos, false_neg =  false_true_positive(m['r_2'], m["pin"]["r_2"])
  order = order_stat(tuple(true_lst_index))
  print {"true_pos": true_pos, "false_pos": false_pos, "false_neg": false_neg, "ordered" : order}

