from flask import Flask
import requests

app = Flask(__name__)

service_stub = "http://127.0.0.1:5000/service/"

@app.route("/")
def home():
    respone = requests.get(service_stub+"1")
    res_json = respone.json()
    return res_json
