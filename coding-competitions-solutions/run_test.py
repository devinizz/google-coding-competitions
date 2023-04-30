#!/usr/bin/env python3
import subprocess, os, sys
sys.dont_write_bytecode = True

class TestData:
  def __raw_test(in_file, ans_file, out_file):
    return open(ans_file, 'r').read() == open(out_file, 'r').read()

  def __init__(self, path):
    SOLUTION_DIR_NAME = 'coding-competitions-solutions'
    ARCHIVE_DIR_NAME = 'coding-competitions-archive'
    if path not in sys.path:
      sys.path.append(path)

    try:
      from judge_wrapper import Judge
      self.judge = Judge(path).test
    except:
      self.judge = TestData.__raw_test

    path = path.replace(SOLUTION_DIR_NAME, ARCHIVE_DIR_NAME)
    self.path = os.path.join(path, 'data', 'secret')
    self.tasks = [d for d in os.listdir(self.path) if d.startswith('subtask')]

  def test(self, cmd):
    for task in self.tasks:
      in_file = os.path.join(self.path, task, '1.in')
      ans_file = os.path.join(self.path, task, '1.ans')
      out_file = '1.out'

      with open(in_file, 'r') as f_in:
        with open(out_file, 'w') as f_out:
          subprocess.run(cmd, stdin = f_in, stdout = f_out)

      if self.judge(in_file, ans_file, out_file):
        print(task + ': test succeed')
      else:
        print(task + ': test failed')
        break

    os.remove(out_file)

if __name__ == '__main__':
  testdata = TestData(os.path.join(os.getcwd(), os.path.dirname(sys.argv[0])))
  testdata.test(sys.argv[1:])
