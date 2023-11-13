from flask import request, Request, jsonify
from controller.controller import Controller

def get_fluids(controller: Controller):
    try:
        fluids = controller.get_fluids()
        return jsonify(fluids), 200
    except Exception as e:
        return jsonify({"error": str(e)}), 500
