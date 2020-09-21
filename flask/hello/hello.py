from flask import Flask
app = Flask(__name__)

@app.route("/")
def hello():
    return """Hello, world!<br><br>\n
            <a href=\"/hidden\">This page doesn't exist</a>"""

@app.route("/hidden")
def hidden():
    return "Hidden page!"

@app.route("/user/<string:name>")
def user(name):
    return "Hello, " + name
