from flask import Flask
from flask_restful import Resource, Api
import requests

app = Flask(__name__)
api = Api(app)

port = 5080

class StorageSkeleton(Resource):
    def get(self, method_id):
        return {"data": f"hello from storage skeleton method {method_id}"}

class CommandSkeleton(Resource):
    def get(self, method_id):
        return {"data": f"hello from command skeleton method {method_id}"}

naming_server_register_stub = "http://127.0.0.1:5000/registration/"

def register():
    response = requests.get(naming_server_register_stub+str(port))
    res_json = response.json()
    if "error" in res_json:
        print("Error registering")
        return
    print("Server registered with naming server")


api.add_resource(StorageSkeleton, "/storage/<int:method_id>")
api.add_resource(CommandSkeleton, "/command/<int:method_id>")

register()
