import os
from time import time, sleep

class CheckFile(object):
    def __init__(self):
        self._cache_stamp = 0
        self.data_path = "/data"
        self.cache_name = ".last"
        try:
            with open(self.data_path+'/'+self.cache_name, "r") as f:
                lines = f.readlines()
                self.file_length = len(lines)
                try:
                    self.first_time = int(lines[0].split(",")[0])
                except:
                    self.first_time = 0
        except:
            self.file_length = 0
        

    def check(self):
        
        stamp = os.stat(self.data_path+'/'+self.cache_name).st_mtime

        if stamp != self._cache_stamp:
            self._cache_stamp = stamp
            try:
                with open(self.data_path+'/'+self.cache_name, "r") as f:
                    lines = f.readlines()
                    new_length = len(lines)
                    try:
                        last_time = int(lines[-1].split(",")[0])
                    except:
                        last_time = 0
                with open(self.data_path+'/'+".last_log", "w") as f:
                    if self.first_time > last_time:
                        f.write("["+str(int(time()))+"]"+" --- .last file newly created!")
                        f.write("["+str(int(time()))+"]"+" --- .added "+str(new_length)+"log data!")
                        
                    else:
                        f.write("["+str(int(time()))+"]"+" --- .added "+str(new_length - self.file_length)+"log data!")
                    self.file_length = new_length
                    self.first_time = last_time

            except:
                pass

if __name__ == '__main__':
    check_file = CheckFile()
    while True:
        check_file.check()
        sleep(3)
