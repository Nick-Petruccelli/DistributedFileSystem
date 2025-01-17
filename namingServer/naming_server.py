from flask import Flask
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

class ServiceSkeleton(Resource):
    def get(self, service_id):
        service_name = ""
        match service_id:
            case Services.GET_STORAGE.value:
                service_name = Services.GET_STORAGE.name
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

        return {"data": f"you requested {service_name}"}

api.add_resource(ServiceSkeleton, "/service/<int:service_id>")
