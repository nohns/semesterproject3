from tests.conftest import test_drinks

expected_drinks = test_drinks


def test_get_drinks_api(client):
    response = client.get("/v1/drinks", follow_redirects=True)

    assert response.status_code == 200

    actual_drinks = response.json["drinks"]
    assert actual_drinks == expected_drinks
