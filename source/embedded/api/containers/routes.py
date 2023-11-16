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
    def change_containers(container_id):
        try:
            controller.change_containers(container_id)
        except Exception as e:
            return jsonify({"error": str(e)}), 500

    return containers_bp
