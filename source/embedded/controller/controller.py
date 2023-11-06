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

    def change_containers(self, id: int, fluid_type: str, fluid_amount_in_cl: int):
        return change_containers(id, self.database)

    def get_containers(self):
        return get_containers(self.database)

    def create_drink(self):
        return create_drink(self.database)

    def delete_drink(self, id: int):
        return delete_drink(id, self.database)

    def get_drinks(self):
        return get_drinks(self.database)

    def pour_drink(self):
        return pour_drink(self.database)

    def get_fluids(self):
        return get_fluids(self.database)

    def create_fluid(self, fluid: Fluid):
        return create_fluid(self.database)

    def delete_fluid(self, id: int):
        return delete_fluid(self.database)

    def get_images(self):
        return get_images(self.database)

    def update(self):
        return update(self.database)
