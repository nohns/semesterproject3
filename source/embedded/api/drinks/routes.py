from flask import Blueprint, jsonify, request

from controller.controller import Controller


def register_drinks_bp(controller: Controller):
    drinks_bp = Blueprint("drinks", __name__)

    @drinks_bp.route("/", methods=["GET"])
    def get_drinks():
        try:
            drinks = controller.get_drinks()
            return jsonify(drinks), 200
        except Exception as e:
            return jsonify({"error": str(e)}), 500


    @drinks_bp.route("/", methods=["POST"])
    def create_drink():
        try:
            data = request.get_json()
            controller.create_drink(data)
            return jsonify({"message": "Drink created successfully"}), 200
        except Exception as e:
            return jsonify({"error": str(e)}), 500

    @drinks_bp.route("/<int:drink_id>", methods=["DELETE"])
    def delete_drink(drink_id):
        try:
            controller.delete_fluid(drink_id)
            return jsonify({"message": "Drink deleted succesfully"}), 200
        except Exception as e:
            return jsonify({"error": str(e)}), 500

    @drinks_bp.route("/pour/<int:drink_id>", methods=["POST"])
    def pour_drink(drink_id):
        try:
            controller.pour_drink(drink_id)
            return jsonify({"message": "drink poured succesfully"}), 200
        except Exception as e:
            return jsonify({"error": str(e)}), 500

    return drinks_bp
