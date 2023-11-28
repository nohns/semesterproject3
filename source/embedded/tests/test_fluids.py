from tests.conftest import test_fluids

expected_fluids = test_fluids


def test_get_fluids_api(client):
    response = client.get("/v1/fluids", follow_redirects=True)

    assert response.status_code == 200

    actual_fluids = response.json["fluids"]
    assert actual_fluids == expected_fluids


def test_get_fluids_controller(controller):
    assert {"fluids": expected_fluids} == controller.get_fluids()
