from flask import Blueprint, request, jsonify

fluid = Blueprint("fluid", __name__, url_prefix="/fluid")


@fluid.route("/", methods=["GET"])
def get_fluids():
    try:
        fluids = get_fluids_from_database()
        return jsonify(fluids), 200
    except Exception as e:
        return jsonify({"error": str(e)}), 500


@fluid.route("/", methods=["POST"])
def create_fluid():
    try:
        data = request.get_json()
        name = data.get("name")
        if name:
            fluid_id = create_fluid_in_database(name)
            return (
                jsonify(
                    {"message": "Fluid created successfully", "fluid_id": fluid_id}
                ),
                200,
            )
        else:
            return jsonify({"error": "Name is required"}), 400
    except Exception as e:
        return jsonify({"error": str(e)}), 500


@fluid.route("/<int:fluid_id>", methods=["DELETE"])
def delete_fluid(fluid_id):
    try:
        delete_fluid_from_database(fluid_id)
        return jsonify({"message": "Fluid deleted succesfully"}), 200
    except Exception as e:
        return jsonify({"error": str(e)}), 500


def create_fluid_in_database(name):
    # do the creatings
    return 0


def delete_fluid_from_database(fluid_id):
    # do the deletings
    return 0


def get_fluids_from_database():
    return {"name": "bajs"}
