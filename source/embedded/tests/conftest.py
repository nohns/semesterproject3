import pytest
from unittest.mock import MagicMock
from controller.controller import Controller
from database.database import Database
from netlink.publisher import NetlinkPublisher
from api.api import Api
from domain.domain import Fluid


class MockDatabase:
    def get_fluids(self):
        return [Fluid(id=1, name="Vand")]


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
