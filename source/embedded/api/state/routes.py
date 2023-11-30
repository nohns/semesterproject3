from flask import Blueprint, jsonify

from controller.controller import Controller


def register_state_bp(controller: Controller):
    state_bp = Blueprint("state", __name__)

    @state_bp.route("/", methods=["GET"])
    def get_state():
        try:
            return jsonify(controller.get_state()), 200
        except Exception as e:
            return jsonify({"error": str(e)}), 500

    return state_bp
