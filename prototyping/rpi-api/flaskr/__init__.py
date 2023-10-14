from flask import Flask, render_template, request, jsonify

static_dir = "../flask-test/dist"
#template_dir = "../flask-test/dist"

tasks = []
task_counter = 1

def create_app():
    app = Flask(__name__, static_url_path='', static_folder=static_dir)


    @app.route("/")
    def index():
        return app.send_static_file("index.html")
    
    @app.route("/api/tasks", methods=["GET"])
    def get_tasks():
        return jsonify(tasks)


    @app.post("/api/tasks")
    #@app.route("/api/tasks", methods=["POST"])
    def add_task():
        global task_counter
        try:
            data = request.get_json()
            if "text" not in data:
                return jsonify({"error": "Task 'text' is required."}), 400
            new_task = {
                "id": task_counter,
                "text": data["text"],
                "completed": False
                }
            task_counter += 1
            tasks.append(new_task)
            return jsonify(new_task), 201
        except Exception as e:
            return jsonify({"error": str(e)}), 400
        
    @app.route ("/api/tasks/<int:id>", methods=["DELETE"])
    def remove_task(id):
        try:
            task_to_be_removed = None
            for task in tasks:
                if task["id"] == id:
                    task_to_be_removed = task
                    tasks.remove(task)
                    break
            if task_to_be_removed:
                return jsonify(task_to_be_removed), 200
            else:
                return jsonify({"error": "Task not found"}), 404
        except Exception as e:
            return jsonify({"error": str(e)}), 400
        
    @app.route("/api/tasks/<int:id>", methods=["PUT"])
    def toggle_complete(id):
        try:
            data = request.get_json()
            for task in tasks:
                if task["id"] == id:
                    task["completed"] = data.get("completed", task["completed"])
                    return jsonify(task), 200
            return jsonify({"error": "Task not found"}, 404)
        except Exception as e:
            return jsonify({"error": str(e)}), 400
      
    return app

