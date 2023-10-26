from flask import Blueprint, request, jsonify


drink = Blueprint("drink", __name__, url_prefix="/drink")


@drink.route("/", methods=["GET"])
def get_drinks():
    try:
        drinks = get_drinks_from_database()
        return jsonify(drinks), 200
    except Exception as e:
        return jsonify({"error": str(e)}), 500


@drink.route("/", methods=["POST"])
def create_fluid():
    try:
        image_id = request.get("imageId")
        name = request.get("name")
        ingredients = request.get("Ingredient")

        if not image_id:
            raise ValueError("Image is required")
        if not name:
            raise ValueError("Name is required")
        if not ingredients:
            raise ValueError("Ingredients are required")

        drink_id = create_drink_in_database(image_id, name, ingredients)
        return (
            jsonify({"message": "Drink created successfully", "drink_id": drink_id}),
            200,
        )
    except ValueError as e:
        return jsonify({"error": str(e)}), 400
    except Exception as e:
        return jsonify({"error": str(e)}), 500


@drink.route("/<int:drink_id>", methods=["DELETE"])
def delete_fluid(drink_id):
    try:
        delete_drink_from_database(drink)
        return jsonify({"message": "Fluid deleted succesfully"}), 200
    except Exception as e:
        return jsonify({"error": str(e)}), 500


def get_drinks_from_database():
    return {"name": "blå vand"}


def create_drink_in_database(image_id, name, ingredients):
    return 0


def delete_drink_from_database(drink):
    return 0