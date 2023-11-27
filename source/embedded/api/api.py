from controller.controller import Controller
from flask import Flask, request
from flask_cors import CORS


class Api:
    controller: Controller

    # --> THIS IS THE CLASS CONSTRUCTOR <- #
    def __init__(self, controller: Controller):
        print("API initialized")
        self.controller = controller
        self.app = None

    def create_app(self):
        app = Flask(__name__)

        # Add CORS with custom settings
        CORS(
            app,
            origins=["http://localhost:5173", "http://localhost", "http://172.20.10.3"],
            allow_headers=["Content-Type", "Origin"],
            methods=["GET", "POST", "PUT", "PATCH", "DELETE", "OPTIONS"],
        )

        # Register the routes
        self.register_routes(app)

        # Handle OPTIONS requests
        app.before_request(self.handle_options_request)

        return app

    def handle_options_request(self):
        if request.method == "OPTIONS":
            response = self.app.make_default_options_response()
            return response

    def register_routes(self, app):
        from api.containers.routes import register_containers_bp
        from api.images.routes import register_images_bp
        from api.fluids.routes import register_fluids_bp
        from api.drinks.routes import register_drinks_bp
        from api.updates.routes import register_updates_bp

        containers_bp = register_containers_bp(self.controller)
        images_bp = register_images_bp(self.controller)
        drinks_bp = register_drinks_bp(self.controller)
        fluids_bp = register_fluids_bp(self.controller)
        updates_bp = register_updates_bp(self.controller)
        app.register_blueprint(containers_bp, url_prefix="/v1/containers")
        app.register_blueprint(images_bp, url_prefix="/v1/images")
        app.register_blueprint(drinks_bp, url_prefix="/v1/drinks")
        app.register_blueprint(fluids_bp, url_prefix="/v1/fluids")
        app.register_blueprint(updates_bp, url_prefix="/v1/updates")

    def run(self, host="localhost", port=8000):
        self.app = self.create_app()
        self.app.run(host=host, port=port)
