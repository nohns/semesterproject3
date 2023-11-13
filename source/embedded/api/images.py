from flask import request, Request, jsonify
from controller.controller import Controller


def get_images(controller: Controller):
    try:
        images = controller.get_images()
        return jsonify(images), 200
    except Exception as e:
        return jsonify({"error": str(e)}), 500
