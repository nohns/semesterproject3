from flask import request, Request, jsonify
from controller.controller import Controller


def create_fluid(controller: Controller):
    try:
        data = request.get_json()
        name = data.get("name")
        print("Recieved the following data: ",data)
        controller.create_fluid(name)
        return jsonify({"message": "Fluid created successfully"}), 200
        
    except Exception as e:
        return jsonify({"error": str(e)}), 500
    
def delete_fluid(id: int, controller: Controller):
    try:
        
        return jsonify({"message": "Fluid deleted succesfully"}), 200
    except Exception as e:
        return jsonify({"error": str(e)}), 500
    
def get_fluids(controller: Controller):
    try:
        fluids=controller.get_fluids()
        return jsonify(fluids), 200
    except Exception as e:
        return jsonify({"error": str(e)}), 500