import pytest

from embedded.api.api import Api


@pytest.fixture()
def app():
    app = Api()

    yield app


@pytest.fixture()
def client(app):
    return app.test_client()
