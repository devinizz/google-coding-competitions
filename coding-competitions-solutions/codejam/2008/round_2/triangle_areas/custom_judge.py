import os, sys
from lib2to3 import refactor

def convert_python2_to_python3(code):
    fixers = refactor.get_fixers_from_package('lib2to3.fixes')
    refactor_tool = refactor.RefactoringTool(fixers)
    return str(refactor_tool.refactor_string(code, 'converted.py'))

class Judge:
  def __get_judge(path):
    judge_file = os.path.join(path, 'custom_judge.py')
    namespace = dict()
    exec(convert_python2_to_python3(open(judge_file).read()), namespace)
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
    self.test = Judge.__get_judge(path)

if __name__ == '__main__':
  judge = Judge(os.path.join(os.getcwd(), os.path.dirname(sys.argv[0])))
  if judge.test(*map(lambda f: open(f).read(), sys.argv[1:]), debug = True):
    print('succeed')
  else:
    print('failed')
