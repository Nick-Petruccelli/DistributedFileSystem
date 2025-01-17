from flask import Flask
from flask_restful import Resource, Api

app = Flask(__name__)
api = Api(app)

class StorageSkeleton(Resource):
    def get(self, method_id):
        return {"data": f"hello from storage skeleton method {method_id}"}

class CommandSkeleton(Resource):
    def get(self, method_id):
        return {"data": f"hello from command skeleton method {method_id}"}

api.add_resource(StorageSkeleton, "/storage/<int:method_id>")
api.add_resource(CommandSkeleton, "/command/<int:method_id>")
