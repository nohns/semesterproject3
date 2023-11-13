def test_create_fluid(client, app):
    response = client.post("/v1/fluids", data={"name": "blå vand"})

    assert response.status_code == 200
    assert response.json["message"] == "Fluid created succesfully"

    fluids = app.controller.db.get_fluids()
    assert len(fluids) == 1
    assert fluids[0].name == "blå vand"
