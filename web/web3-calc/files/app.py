import random
from flask import Flask, render_template_string, render_template, request
import os
import re
import string

app = Flask(__name__)
all_letters = string.ascii_letters  # 包含大写和小写字母
filtered_letters = ''.join([char for char in all_letters if char not in 'print'])
@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        try:
            p = request.values.get('formula')
            if p != None:
                if re.match("\d{1,10}.?\d{0,5}[\+\-\*\/]\d{1,10}.?\d{0,5}",p):
                    result=eval(p)
                    return render_template_string(str(result))
                if '{{' in p or '}}' in p or '+' in p :
                    return 'what\'s this?'
                for i in filtered_letters:
                    if i in p:
                        return 'no letter'
                return render_template_string(p)

        except Exception as e:
            print(e)
            return 'too hard for meQ_Q'

    return render_template('index.html')

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=1337)