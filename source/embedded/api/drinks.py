from flask import request, Request, jsonify
from controller.controller import Controller


def create_drink(controller: Controller):
    try:
        data = request.get_json()
        image_id = data.get("imageId")
        name = data.get("name")
        ingredients = data.get("Ingredient")

        print(ingredients)

        if not image_id:
            raise ValueError("Image is required")
        if not name:
            raise ValueError("Name is required")
        if not ingredients:
            raise ValueError("Ingredients are required")

        drink_id = controller.create_drink(image_id, name, ingredients)
        return (
            jsonify({"message": "Drink created successfully", "drink_id": drink_id}),
            200,
        )
    except ValueError as e:
        return jsonify({"error": str(e)}), 400
    except Exception as e:
        return jsonify({"error": str(e)}), 500


def delete_drink(id: int, controller: Controller):
    try:
        controller.delete_drink(id)
        return jsonify({"message": "Fluid deleted succesfully"}), 200
    except Exception as e:
        return jsonify({"error": str(e)}), 500


def get_drinks(controller: Controller):
    try:
        drinks = controller.get_drinks()
        return jsonify(drinks), 200
    except Exception as e:
        return jsonify({"error": str(e)}), 500


def pour_drink(controller: Controller):
    return jsonify({"Hello": "World"})
