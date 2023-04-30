import subprocess, os, sys
if '.' not in sys.path:
  sys.path.append('.')
sys.dont_write_bytecode = True

class Judge:
  def __get_judge(path):
    judge_file = os.path.join(path, 'custom_judge.py')
    subprocess.run(['python3', '-m', 'lib2to3', '-Wno.', judge_file],
      stdout = subprocess.DEVNULL, stderr = subprocess.DEVNULL)
    from custom_judge import FindError
    read = lambda name: open(name, 'r').read()
    def judge(in_f, ans_f, out_f, debug = False):
      result = FindError(None, read(in_f), read(ans_f), read(out_f))
      if (debug and result):
        print(result)
      return result == None
    return judge

  def __init__(self, path):
    SOLUTION_DIR_NAME = 'coding-competitions-solutions'
    ARCHIVE_DIR_NAME = 'coding-competitions-archive'
    path = path.replace(SOLUTION_DIR_NAME, ARCHIVE_DIR_NAME)
    path = os.path.join(path, 'output_validators', 'validator')
    self.test = Judge.__get_judge(path)

  def __del__(self):
    os.remove('custom_judge.py')

if __name__ == '__main__':
  judge = Judge(os.path.join(os.getcwd(), os.path.dirname(sys.argv[0])))
  print('succeed' if judge.test(*sys.argv[1:], True) else 'failed')
