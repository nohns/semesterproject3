# Call controller class
from database.database import Database
from netlink.publisher import NetlinkPublisher
from domain.domain import *


# <- IMPORT FUNCTIONS FROM OTHER FILES ->
from controller.update import update
from controller.containers import change_containers, get_containers
from controller.drinks import create_drink, delete_drink, get_drinks, pour_drink
from controller.fluids import get_fluids, create_fluid, delete_fluid
from controller.images import get_images

# <- IMPORT FUNCTIONS FROM OTHER FILES ->


class Controller:
    database: Database
    netlink_publisher: NetlinkPublisher

    def __init__(self, database: Database, netlink_publisher: NetlinkPublisher):
        self.database = database
        self.netlink_publisher = netlink_publisher

    # Probaly need to add more parameters to this
    def change_containers(self, id: int):
        return change_containers(self.database, id)

    def get_containers(self) -> list[FluidContainer]:
        return get_containers(self.database)

    def create_drink(self, image_path: str, name: str, ingredients: list) -> int:
        return create_drink(self.database, image_path, name, ingredients)

    def delete_drink(self) -> None:
        return delete_drink(self.database)

    def get_drinks(self) -> list[Drink]:
        return get_drinks(self.database)

    def pour_drink(self) -> None:
        return pour_drink(self.database)

    def get_fluids(self) -> list[Fluid]:
        return get_fluids(self.database)

    def create_fluid(self, name: str) -> int:
        return create_fluid(self.database, name)

    def delete_fluid(self, id: int) -> None:
        return delete_fluid(self.database, id)

    def get_images(self) -> list[Image]:
        return get_images(self.database)

    def update(self) -> bool:
        return update(self.database)
