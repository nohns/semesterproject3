from flask import Blueprint, jsonify

from controller.controller import Controller


def register_updates_bp(controller: Controller):
    updates_bp = Blueprint("updates", __name__)

    @updates_bp.route("/", methods=["GET"])
    def update():
        try:
            controller.update()
            return jsonify({"success": True}), 200
        except Exception as e:
            return jsonify({"error": str(e)}), 500

    return updates_bp
