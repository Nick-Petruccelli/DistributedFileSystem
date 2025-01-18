from flask import Flask, request
from flask_restful import Resource, Api
import requests
from enum import Enum


app = Flask(__name__)
api = Api(app)

class Services(Enum):
    GET_STORAGE = 0
    IS_DIR = 1
    LIST = 2
    CREATE_FILE = 3
    CREATE_DIR = 4
    DELETE = 5

storage_servers = []

class ServiceSkeleton(Resource):
    def get(self, service_id):
        service_name = ""
        match service_id:
            case Services.GET_STORAGE.value:
                return {"data": storage_servers}
            case Services.IS_DIR.value:
                service_name = Services.IS_DIR.name
            case Services.LIST.value:
                service_name = Services.LIST.name
            case Services.CREATE_FILE.value:
                service_name = Services.CREATE_FILE.name
            case Services.CREATE_DIR.value:
                service_name = Services.CREATE_DIR.name
            case Services.DELETE.value:
                service_name = Services.DELETE.name
            case _:
                return {"error": {"code": 404, "message": "service you requested was not found"}}
        return {"data": f"you requested {service_name}"}

class RegistrationSkeleton(Resource):
    def get(self, port: int):
        storage_server_address = request.remote_addr + ":" + str(port)
        if storage_server_address in storage_servers:
            return {"error": {"code": 409, "message": "address already registered"}}
        storage_servers.append(storage_server_address)
        return {"data": "successfuly registered"}

api.add_resource(ServiceSkeleton, "/service/<int:service_id>")
api.add_resource(RegistrationSkeleton, "/registration/<int:port>")

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
