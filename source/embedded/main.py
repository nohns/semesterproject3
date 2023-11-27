import threading


from controller.controller import Controller
from database.database import Database
from netlink.publisher import NetlinkPublisher
from netlink.reciever import NetlinkReciever
from api.api import Api


class Main:
    # Database and publishing events to psoc via netlink (pump control)
    database: Database
    # netlink_publisher: NetlinkPublisher

    # Controller which handles logic will import domain classes
    controller: Controller

    # Recieving events from psoc via netlink (weight sensor)
    # netlink_reciever: NetlinkReciever
    # Recieving http requests from frontend
    api: Api

    def __init__(self):
        # Initialize all classes
        database = Database()

        print("Testitestitest")
        drink = database.get_drink_for_netlink(1)
        print(drink)

        container = database.get_container_by_fluid_id(1)
        print(container)

        netlink_publisher = NetlinkPublisher()

        controller = Controller(database, netlink_publisher)

        # Since we are going to be recieving events from psoc and http requests from frontend we need to create threads for both
        print("Setting up boundaries...")
        # netlink_reciever = NetlinkReciever(controller)
        api = Api(controller)

        # Create threads for netlink_reciever and api
        # netlink_reciever_thread = threading.Thread(target=netlink_reciever.run)
        api_thread = threading.Thread(target=api.run)

        # Start the threads
        print("Starting boundary threads...")
        # netlink_reciever_thread.start()
        api_thread.start()

        # Wait for the threads to finish (which should be never)
        # netlink_reciever_thread.join()
        api_thread.join()
        # api = Api(controller)


if __name__ == "__main__":
    Main()
