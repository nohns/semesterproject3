from flask import request, Request, jsonify
from controller.controller import Controller
from domain.domain import Drink
from domain.domain import json_to_dataclass

def create_drink(controller: Controller):
    print(f"Create_drink", request.get_json())
    try:
        data = json_to_dataclass(request.get_json(), Drink)
        print("Recieved the following data: ",data)
        controller.create_drink(data)
        return jsonify({"message": "Drink created successfully"}), 200
    except Exception as e:
        return jsonify({"error": str(e)}), 500

def delete_drink(id: int, controller: Controller):
    try:
        controller.delete_drink(id)
        return jsonify({"message": "Fluid deleted succesfully"}), 200
    except Exception as e:
        return jsonify({"error": str(e)}), 500
    
def get_drinks(controller: Controller):
    try:
        drinks = controller.get_drinks()
        return jsonify(drinks), 200
    except Exception as e:
        return jsonify({"error": str(e)}), 500
    
def pour_drink(controller: Controller):
    try:
        controller.pour_drink()
        return jsonify({"message": "drink poured succesfully"}), 200
    except Exception as e:
        return jsonify({"error": str(e)}), 500
