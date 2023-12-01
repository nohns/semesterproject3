from flask import Blueprint, jsonify

from controller.controller import Controller
from netlink.publisher import NetlinkPublisher


def register_updates_bp(controller: Controller, hardware: NetlinkPublisher):
    updates_bp = Blueprint("updates", __name__)

    @updates_bp.route("/", methods=["GET"])
    def update():
        try:
            controller.update()
            return jsonify({"success": True}), 200
        except Exception as e:
            return jsonify({"error": str(e)}), 500

    @updates_bp.route("/debug/<int:event_type>/<int:data>", methods=["POST"])
    def debug(event_type, data):
        hardware.debug(event_type, data)
        return jsonify({"success": True}), 200

    return updates_bp
