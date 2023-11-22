# Call controller class
from database.database import Database
from netlink.publisher import NetlinkPublisher
from flask import Request

from domain.domain import Fluid, Drink, Container, Image


# <- IMPORT FUNCTIONS FROM OTHER FILES ->
from controller.update import update
from controller.containers import change_containers, get_containers
from controller.drinks import create_drink, delete_drink, get_drinks, pour_drink
from controller.fluids import get_fluids, create_fluid, delete_fluid
from controller.images import get_images

# <- IMPORT FUNCTIONS FROM OTHER FILES ->


class Controller:
    database: Database
    hardware: NetlinkPublisher

    def __init__(self, database: Database, hardware: NetlinkPublisher):
        self.database = database
        self.hardware = hardware

    def change_containers(self, container_id: int, new_fluid_id: int) -> bool:
        return change_containers(self.database, container_id, new_fluid_id)

    def get_containers(self) -> list[Container]:
        return get_containers(self.database)

    def create_drink(self, data: Request) -> None:
        return create_drink(self.database, data)

    def delete_drink(self, drink_id: int) -> None:
        return delete_drink(self.database, drink_id)

    def get_drinks(self) -> list[Drink]:
        return get_drinks(self.database)

    def pour_drink(self, drink_id: int) -> None:
        return pour_drink(self.database, self.hardware, drink_id)

    def get_fluids(self) -> list[Fluid]:
        return get_fluids(self.database)

    def create_fluid(self, data: Request) -> None:
        return create_fluid(self.database, data)

    def delete_fluid(self, fluid_id: int) -> bool:
        return delete_fluid(self.database, fluid_id)

    def get_images(self) -> list[Image]:
        return get_images(self.database)

    def update(self) -> bool:
        return update(self.database)
