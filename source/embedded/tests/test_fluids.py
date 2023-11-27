from sample_data import fluids
from flask import jsonify


def test_get_fluids(client):
    response = client.get("/v1/fluids")

    assert response.status_code == 200
    assert response.json["fluids"] == fluids.jsonify()
