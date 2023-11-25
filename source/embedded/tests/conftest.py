import pytest
import threading

from controller.controller import Controller
from database.database import Database
from netlink.publisher import NetlinkPublisher
from netlink.reciever import NetlinkReciever
from api.api import Api


@pytest.fixture()
def app():
    database = Database()
    netlink_publisher = NetlinkPublisher()
    controller = Controller(database, netlink_publisher)
    netlink_reciever = NetlinkReciever(controller)
    api = Api(controller)
    api.app = api.create_app()
    api.app.config.update(
        {
            "TESTING": True,
        }
    )
    netlink_reciever_thread = threading.Thread(target=netlink_reciever)
    api_thread = threading.Thread(target=api)

    # Start the threads
    netlink_reciever_thread.start()
    api_thread.start()
    yield app
    netlink_reciever_thread.join()
    api_thread.join()


@pytest.fixture()
def client(app):
    return app.test_client()
