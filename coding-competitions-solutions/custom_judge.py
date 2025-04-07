import os, sys

class Judge:
  @staticmethod
  def _get_judge(path):
    judge_file = os.path.join(path, 'custom_judge.py')
    namespace = dict()
    exec(open(judge_file).read(), namespace)
    def judge(s_in, s_ans, s_out, debug = False):
      result = namespace['FindError'](None, s_in, s_ans, s_out)
      if (debug and result):
        print(result)
      return result == None
    return judge

  def __init__(self, path):
    SOLUTION_DIR_NAME = 'coding-competitions-solutions'
    ARCHIVE_DIR_NAME = 'coding-competitions-archive'
    path = path.replace(SOLUTION_DIR_NAME, ARCHIVE_DIR_NAME)
    path = os.path.join(path, 'output_validators', 'validator')
    self.test = Judge._get_judge(path)

if __name__ == '__main__':
  judge = Judge(os.path.join(os.getcwd(), os.path.dirname(sys.argv[0])))
  if judge.test(*map(lambda f: open(f).read(), sys.argv[1:]), debug = True):
    print('succeed')
  else:
    print('failed')
