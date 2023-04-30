import sys

class Judge:
  def __init__(self, path):
    pass
  def test(self, in_f, ans_f, out_f):
    ans = open(ans_f, 'r').read().splitlines()
    out = open(out_f, 'r').read().splitlines()
    if len(ans) != len(out):
      return False
    for a, o in zip(ans, out):
      a = a.split()[2]
      o = o.split()[2]
      if abs(float(a) - float(o)) > 1e-6:
        return False
    return True

if __name__ == '__main__':
  judge = Judge('.')
  print('succeed' if judge.test(*sys.argv[1:]) else 'failed')
