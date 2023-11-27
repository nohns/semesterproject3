from tests.conftest import test_containers

expected_containers = test_containers


def test_get_containers_api(client):
    response = client.get("/v1/containers", follow_redirects=True)

    assert response.status_code == 200

    actual_containers = response.json["containers"]
    assert actual_containers == expected_containers


def test_get_drinks_controller(controller):
    assert {"containers": expected_containers} == controller.get_containers()
