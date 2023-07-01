#!/usr/bin/env python3
import subprocess, os, sys
sys.dont_write_bytecode = True

class TestData:
  def __raw_test(s_in, s_ans, s_out):
    return s_ans == s_out

  def __init__(self, path):
    SOLUTION_DIR_NAME = 'coding-competitions-solutions'
    ARCHIVE_DIR_NAME = 'coding-competitions-archive'
    if path not in sys.path:
      sys.path.append(path)

    try:
      from custom_judge import Judge
      self.judge = Judge(path).test
    except:
      self.judge = TestData.__raw_test

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
        break

if __name__ == '__main__':
  testdata = TestData(os.path.join(os.getcwd(), os.path.dirname(sys.argv[0])))
  testdata.test(sys.argv[1:])
