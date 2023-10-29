from flask import request, Request, jsonify
from controller.controller import Controller
def create_drink(controller: Controller):
    return jsonify({"Hello": "World"})
    
def delete_drink(id: int, controller: Controller):
    return jsonify({"Hello": "World"})
    
def get_drinks(controller: Controller):
    return jsonify({"Hello": "World"})
    
def pour_drink(controller: Controller):
    return jsonify({"Hello": "World"})
    
def cancel_pour_drink(controller: Controller):
    return jsonify({"Hello": "World"})