# Call netlink reciever class
from controller.controller import Controller


class NetlinkReciever:
    controller: Controller

    def __init__(self, controller: Controller):
        print("NetlinkReceiver initialized")
        self.controller = controller
