from flask import request, Request, jsonify
from controller.controller import Controller
from domain.domain import Drink
from domain.domain import json_to_dataclass
 
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
