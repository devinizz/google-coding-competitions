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
      if a != o:
        try:
          if abs(float(a) - float(o)) > 1e-6:
            return False
        except:
          return False
    return True

if __name__ == '__main__':
  judge = Judge('.')
  if judge.test(*map(lambda f: open(f).read(), sys.argv[1:])):
    print('succeed')
  else:
    print('failed')
