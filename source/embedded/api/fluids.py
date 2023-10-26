from flask import request, Request, jsonify
from controller.controller import Controller


def create_fluid(controller: Controller):
    return jsonify({"Hello": "World"})
    
def delete_fluid(id: int, controller: Controller):
    return jsonify({"Hello": "World"})
    
def get_fluids(controller: Controller):
    return jsonify({"Hello": "World"})