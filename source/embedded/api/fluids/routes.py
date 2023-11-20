from flask import Blueprint, jsonify, request

from controller.controller import Controller


def register_fluids_bp(controller: Controller):
    fluids_bp = Blueprint("fluids", __name__)

    @fluids_bp.route("/", methods=["GET"])
    def get_fluids():
        try:
            fluids = controller.get_fluids()
            return jsonify(fluids), 200  # This will now return an object with a 'fluids' key
        except Exception as e:
            return jsonify({"error": str(e)}), 500


    @fluids_bp.route("/", methods=["POST"])
    def create_fluid():
        try:
            data = request.get_json()
            controller.create_fluid(data)
            return jsonify({"message": "Fluid created successfully"}), 200
        except Exception as e:
            return jsonify({"error": str(e)}), 500

    @fluids_bp.route("/<int:fluid_id>", methods=["DELETE"])
    def delete_fluid(fluid_id):
        try:
            wasDeleted: bool = controller.delete_fluid(fluid_id)
            if wasDeleted:
                return jsonify({"message": "Fluid deleted succesfully"}), 200
            return jsonify({"message": "Fluid doesn't exist"})
        except Exception as e:
            return jsonify({"error": str(e)}), 500

    return fluids_bp
