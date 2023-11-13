def create_fluid(controller: Controller):
    try:
        data = request.get_json()
        name = data.get("name")
        print("Recieved the following data: ", data)
        controller.create_fluid(name)
        return jsonify({"message": "Fluid created successfully"}), 200

    except Exception as e:
        return jsonify({"error": str(e)}), 500


""" def delete_fluid(id: int, controller: Controller):
    try:
        controller.delete_fluid(id)
        return jsonify({"message": "Fluid deleted succesfully"}), 200
    except Exception as e:
        return jsonify({"error": str(e)}), 500 """

def create_drink(controller: Controller):
    print(f"Create_drink", request.get_json())
    try:
        data = json_to_dataclass(request.get_json(), Drink)
        print("Recieved the following data: ",data)
        controller.create_drink(data)
        return jsonify({"message": "Drink created successfully"}), 200
    except Exception as e:
        return jsonify({"error": str(e)}), 500

def delete_drink(id: int, controller: Controller):
    try:
        controller.delete_drink(id)
        return jsonify({"message": "Fluid deleted succesfully"}), 200
    except Exception as e:
        return jsonify({"error": str(e)}), 500