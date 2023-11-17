from flask import Blueprint, jsonify

from controller.controller import Controller


def register_images_bp(controller: Controller):
    images_bp = Blueprint("images", __name__)

    @images_bp.route("/", methods=["GET"])
    def get_images():
        try:
            images = controller.get_images()
            return jsonify(images), 200
        except Exception as e:
            return jsonify({"error": str(e)}), 500

    return images_bp
