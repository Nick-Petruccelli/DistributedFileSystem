from flask import Flask, request
from flask_restful import Resource, Api
import requests


app = Flask(__name__)
api = Api(app)

class ServiceSkeleton(Resource):
    def get(self, service_id):
        storage_res = requests.get("http://127.0.0.1:5080/storage/0")
        res_json = storage_res.json()
        return {"data": f"hello from naming server service {service_id}",
                "storage_res": res_json}

api.add_resource(ServiceSkeleton, "/service/<int:service_id>")
