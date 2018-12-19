import os

class CheckFile(object):
    def __init__(self):
        self._cache_stamp = 0
        self.data_path = "/data"
        self.cache_name = ".last"

    def check(self):
        total_path = self.data_path+'/'+self.cache_name
        stamp = os.stat(total_path).st_mtime

        if stamp != self._cache_stamp:
            self._cache_stamp = stamp
            with open(total_path, "r") as f:
                lines = f.readlines()
                for line in lines:
                    print(line)


if __name__ == '__main__':
    check_file = CheckFile()
    while True:
        check_file.check()
