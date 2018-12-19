from flask import Flask
from time import time
import os

app = Flask(__name__)

@app.route('/')
def index_page():
    ram = os.sysconf('SC_PAGE_SIZE') * os.sysconf('SC_PHYS_PAGES')
    ram_total = str(ram / 2**20)

    html_code = "Hello Container!\n"+"Total memory size of container: "+ram_total+" MiB"

    return html_code

@app.route('/<data>')
def input_data(data=None):
    data_path = "/data"
    cache_name = ".last"
    total_path = data_path+"/"+cache_name
    last_line = ""
    new_line = ""

    if data:
        # Get last line
        try:
            with open(total_path, "r") as f:
                last_line = f.readlines()[-1]
        except:
            with open(total_path, "w") as f:
                pass

        # Write new line
        with open(total_path, "a") as f:
            new_line = str(int(time()))+','+data
            f.write(new_line)
 
        return last_line+"\n"+new_line
    else:
        return index_page()

if __name__ == '__main__':
    app.run(port=8080, debug=True)