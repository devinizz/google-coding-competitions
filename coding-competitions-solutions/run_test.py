#!/usr/bin/env python3
import subprocess, os, sys

class TestData:
  def __test(self, s_in, s_ans, s_out):
    if self.tolerance == 0:
      return s_ans == s_out
    else:
      ans = s_ans.split()
      out = s_out.split()
      if len(ans) != len(out):
        return False
      for a, o in zip(ans, out):
        if a == o:
          continue
        if abs(float(a) - float(o)) / max(1, abs(float(a))) > self.tolerance:
          return False
      return True

  def __init__(self, path):
    SOLUTION_DIR_NAME = 'coding-competitions-solutions'
    ARCHIVE_DIR_NAME = 'coding-competitions-archive'

    self.tolerance = 0
    if os.path.exists(os.path.join(path, 'float_tolerance')):
      self.tolerance = float(open(os.path.join(path, 'float_tolerance')).read())

    self.judge = self.__test
    if os.path.exists(os.path.join(path, 'custom_judge.py')):
      namespace = dict()
      exec(open(os.path.join(path, 'custom_judge.py')).read(), namespace)
      self.judge = namespace['Judge'](path).test

    path = path.replace(SOLUTION_DIR_NAME, ARCHIVE_DIR_NAME)
    self.path = os.path.join(path, 'data', 'secret')
    self.tasks = [d for d in os.listdir(self.path) if d.startswith('subtask')]

  def test(self, cmd):
    for task in self.tasks:
      s_in = ''
      for f in sorted(os.listdir(os.path.join(self.path, task))):
        if f.startswith('1.in'):
          s_in += open(os.path.join(self.path, task, f)).read()

      s_ans = open(os.path.join(self.path, task, '1.ans')).read()
      s_out = subprocess.check_output(cmd, input = s_in, text = True)

      if self.judge(s_in, s_ans, s_out):
        print(task + ': test succeed')
      else:
        print(task + ': test failed')
        exit(1)

if __name__ == '__main__':
  testdata = TestData(os.path.join(os.getcwd(), os.path.dirname(sys.argv[0])))
  testdata.test(sys.argv[1:])
