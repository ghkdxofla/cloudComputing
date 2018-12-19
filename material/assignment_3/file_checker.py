import os
from time import time, sleep

class CheckFile(object):
    def __init__(self):
        self.data_path = "/data"
        self.cache_name = ".last"
        self.last_time = 0
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
        try:
            with open(self.data_path+'/'+self.cache_name, "r") as f:
                lines = f.readlines()
                new_length = len(lines)
                try:
                    last_time = int(lines[-1].split(",")[0])
                except:
                    last_time = 0
                try:
                    first_time = int(lines[0].split(",")[0]) 
                except:
                    first_time = 0
        except:
            return

        if last_time > self.last_time:
            with open(self.data_path+'/'+".last_log", "a") as f:
                if self.first_time < first_time:
                    # f.write("["+str(int(time()))+"]"+" --- .last file newly created, and added "+str(new_length)+" log data!\n")
                    for line in lines:
                        f.write(line)
                    self.first_time = first_time

                else:
                    # f.write("["+str(int(time()))+"]"+" --- .added "+str(new_length - self.file_length)+" log data!\n")
                    for line in lines[self.file_length:new_length]:
                        f.write(line)


                self.file_length = new_length
                self.last_time = last_time

        


if __name__ == '__main__':
    check_file = CheckFile()
    while True:
        check_file.check()
        sleep(3)
