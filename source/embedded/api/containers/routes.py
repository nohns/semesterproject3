from flask import Blueprint, jsonify, request

from controller.controller import Controller


def register_containers_bp(controller: Controller):
    containers_bp = Blueprint("containers", __name__)

    @containers_bp.route("/", methods=["GET"])
    def get_containers():
        try:
            containers = controller.get_containers()
            return jsonify(containers), 200
        except Exception as e:
            return jsonify({"error": str(e)}), 500

    @containers_bp.route("/<int:container_id>", methods=["PATCH"])
    def change_containers_api(container_id):
        try:
            # Parse fluid id from JSON request
            new_fluid_data = request.get_json()
            new_fluid_id = new_fluid_data.get('fluid_id')
            if new_fluid_id is None:
                return jsonify({"error": "No fluid id provided"}), 400
            
            # Call controller with new fluid id
            success = controller.change_containers(container_id, new_fluid_id)
            if success:
                return jsonify({"message": "Container updated successfully"}), 200
            else:
                return jsonify({"error": "Failed to update container"}), 500
        except Exception as e:
            return jsonify({"error": str(e)}), 500


    return containers_bp
