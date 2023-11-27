import sys
is_linux = sys.platform == "Linux"
if is_linux:

    from controller.controller import Controller
    from pyroute2.netlink.generic import GenericNetlinkSocket
    from netlink.conf import DMC_DRIVER_GENL_FAMILY, DMC_DRIVER_GENL_MCAST_GROUP_NAME
    from netlink.events import eventmsg, OutOfOrderEvent, ContainerWeightMeasuredEvent, DMC_EVENT_TYPE_GENL_OUT_OF_ORDER, DMC_EVENT_TYPE_GENL_CONTAINER_WEIGHT_MEASURED

    class NetlinkReciever:
        controller: Controller
        genlsock: GenericNetlinkSocket

        def __init__(self, controller: Controller):
            print("NetlinkReceiver initialized")
            self.controller = controller
            self.genlsock = GenericNetlinkSocket()
            self.genlsock.bind(DMC_DRIVER_GENL_FAMILY, eventmsg)
            self.genlsock.add_membership(DMC_DRIVER_GENL_MCAST_GROUP_NAME)
        
        def run(self):
            print("Netlink receiver listening for events...")
            while True:
                # Recieve the message
                messages = self.genlsock.get()
                for msg in messages:
                    # Check if the message is a fluid pour event
                    self.handle_msg(msg)
                    
        def handle_msg(self, msg: eventmsg):
            evt_type = msg.get_event_type()

            if evt_type == DMC_EVENT_TYPE_GENL_OUT_OF_ORDER:
                self.handle_out_of_order(OutOfOrderEvent().from_msg(msg))
            elif evt_type == DMC_EVENT_TYPE_GENL_CONTAINER_WEIGHT_MEASURED:
                self.handle_container_weight_measured(ContainerWeightMeasuredEvent().from_msg(msg))
                    
        def handle_out_of_order(self, event: OutOfOrderEvent):
            print("Out of order with msg: " + event.message + " (" + str(event.reason) + ")")

        def handle_container_weight_measured(self, event: ContainerWeightMeasuredEvent):
            print("Container weight measured, container: " + str(event.container) + ", weight: " + str(event.weight))
            
else:
    class NetlinkReciever:
        def __init__(self, controller: Controller):
            print("NetlinkReceiver disabled cause not linux")

        def run(self):
            print("NetlinkReceiver disabled cause not linux")
        
