import pytest
from unittest.mock import MagicMock
from controller.controller import Controller
from database.database import Database
from netlink.publisher import NetlinkPublisher
from api.api import Api
from domain.domain import Fluid, Drink, Image, Ingredient

test_fluids = [{"id": 1, "name": "Snaps"}, {"id": 2, "name": "Vand"}]
test_drinks = [
    {
        "id": 1,
        "name": "Snapsevand",
        "image": {"path": "images/Snapsevand", "id": 1},
        "ingredients": [
            {"fluid": "Snaps", "amountInCl": 10, "id": 1},
            {"fluid": "Vand", "amountInCl": 90, "id": 2},
        ],
    }
]
test_containers = [
    {"id": 1, "fluid": {"id": 1, "name": "Snaps"}, "fluidAmountInCl": 500}
]


class MockDatabase:
    def get_fluids(self):
        return test_fluids

    def get_drinks(self):
        return test_drinks

    def get_containers(self):
        return test_containers


@pytest.fixture
def app(api):
    return api.create_app()


@pytest.fixture
def api():
    database = MockDatabase()
    netlink_publisher = MagicMock()

    controller = Controller(database, netlink_publisher)
    return Api(controller)


@pytest.fixture
def client(app):
    return app.test_client()


@pytest.fixture
def controller():
    database = MockDatabase()
    netlink_publisher = MagicMock()

    controller = Controller(database, netlink_publisher)
    return controller
