from flask import Flask
import requests

app = Flask(__name__)

service_stub = "http://172.17.0.2:5000/service/"

@app.route("/")
def home():
    respone = requests.get(service_stub+"0")
    res_json = respone.json()
    return res_json
