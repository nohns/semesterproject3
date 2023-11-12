from flask import request, Request, jsonify
from controller.controller import Controller

def get_images(controller: Controller):
    
    return jsonify({"Hello": "World"})