from flask import request, Request, jsonify
from controller.controller import Controller

def update(controller: Controller):
    try:
        controller.update()
        return jsonify({"success": True}), 200
    except Exception as e:
        return jsonify({"error": str(e)}), 500