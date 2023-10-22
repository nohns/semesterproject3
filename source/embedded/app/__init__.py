from flask import Flask, Blueprint
from app.blueprints.fluid import fluid

app = Flask(__name__)
v1 = Blueprint("v1", __name__, url_prefix="/v1")

v1.register_blueprint(fluid)
app.register_blueprint(v1)