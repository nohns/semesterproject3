# Call netlink reciever class
from controller.controller import Controller


class NetlinkReciever:
    controller: Controller

    def __init__(self, controller: Controller):
        print("NetlinkReciever initialized")
        self.controller = controller
    
    def run(self):
        print("Netlink receiver start")
