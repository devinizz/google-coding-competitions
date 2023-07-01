import sys

class Judge:
  def __init__(self, path):
    pass
  def test(self, s_in, s_ans, s_out):
    ans = s_ans.splitlines()
    out = s_out.splitlines()
    if len(ans) != len(out):
      return False
    for a, o in zip(ans, out):
      a = a.split()[2:]
      o = o.split()[2:]
      for i, j in zip(a, o):
        if abs(float(i) - float(j)) > 1e-5:
          return False
    return True

if __name__ == '__main__':
  judge = Judge('.')
  if judge.test(*map(lambda f: open(f).read(), sys.argv[1:])):
    print('succeed')
  else:
    print('failed')
