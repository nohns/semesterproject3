from controller.controller import Controller
from flask import Flask, Blueprint, request
from flask_cors import CORS


# <- THIS IS THE IMPORTS FOR THE ROUTES -> #
from api.containers import get_containers, change_containers
from api.drinks import get_drinks, create_drink, delete_drink, pour_drink
from api.images import get_images
from api.fluids import get_fluids, create_fluid, delete_fluid
from api.update import update

# <- THIS IS THE IMPORTS FOR THE ROUTES -> #


class Api:
    controller: Controller
    app: Flask
    host = "localhost"
    port = 8000

    # --> THIS IS THE CLASS CONSTRUCTOR <- #
    def __init__(self, controller: Controller):
        print("api initialized")
        self.controller = controller
        self.app = Flask(__name__)

        # Add CORS with custom settings
        CORS(
            self.app,
            origins=["http://localhost:5173"],
            allow_headers=["Content-Type", "Origin"],
            methods=["GET", "POST", "PUT", "PATCH", "DELETE", "OPTIONS"],
        )

        # Register the routes
        self.register_routes()

        # Handle OPTIONS requests
        self.app.before_request(self.handle_options_request)

        # Start running the flask application
        self.app.run(self.host, self.port)

    def handle_options_request(self):
        if request.method == "OPTIONS":
            response = self.app.make_default_options_response()
            return response

    def register_routes(self):
        # Routes for containers
        containers = Blueprint("/v1/containers", __name__, url_prefix="/v1/containers")
        containers.add_url_rule(
            "/<int:id>",
            "change_containers",
            lambda id: change_containers(id, self.controller),
            methods=["PATCH"],
        )
        containers.add_url_rule(
            "/",
            "get_containers",
            lambda: get_containers(self.controller),
            methods=["GET"],
        )
        self.app.register_blueprint(containers)

        # Routes for drinks
        drinks = Blueprint("v1/drinks", __name__, url_prefix="/v1/drinks")
        drinks.add_url_rule(
            "/", "create_drink", lambda: create_drink(self.controller), methods=["POST"]
        )
        drinks.add_url_rule(
            "/<int:id>",
            "delete_drink",
            lambda id: delete_drink(id, self.controller),
            methods=["DELETE"],
        )
        drinks.add_url_rule(
            "/", "get_drinks", lambda: get_drinks(self.controller), methods=["GET"]
        )

        drinks.add_url_rule(
            "/pour", "pour_drink", lambda: pour_drink(self.controller), methods=["POST"]
        )
        self.app.register_blueprint(drinks)

        # Routes for fluids
        fluids = Blueprint("v1/fluids", __name__, url_prefix="/v1/fluids")
        fluids.add_url_rule(
            "/", "get_fluids", lambda: get_fluids(self.controller), methods=["GET"]
        )
        fluids.add_url_rule(
            "/", "create_fluid", lambda: create_fluid(self.controller), methods=["POST"]
        )
        fluids.add_url_rule(
            "/<int:id>",
            "delete_fluid",
            lambda id: delete_fluid(id, self.controller),
            methods=["DELETE"],
        )
        self.app.register_blueprint(fluids)

        # Routes for images
        images = Blueprint("v1/images", __name__, url_prefix="/v1/images")
        images.add_url_rule(
            "/", "/get_images", lambda: get_images(self.controller), methods=["GET"]
        )
        self.app.register_blueprint(images)

        # routes for update
        updates = Blueprint("v1/updates", __name__, url_prefix="/v1/updates")
        updates.add_url_rule(
            "/", "/updates", lambda: update(self.controller), methods=["GET"]
        )
        self.app.register_blueprint(updates)
