from flask import Flask
import requests

app = Flask(__name__)

@app.route("/")
def hello_world():
    respone = requests.get("http://127.0.0.1:5000/service/1")
    res_json = respone.json()
    return res_json
