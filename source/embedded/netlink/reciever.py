import sys
from controller.controller import Controller

is_linux = sys.platform == "linux"
if is_linux:
    from pyroute2.netlink.generic import GenericNetlinkSocket
    from netlink.conf import DMC_DRIVER_GENL_FAMILY, DMC_DRIVER_GENL_MCAST_GROUP_NAME
    from netlink.events import (
        eventmsg,
        OutOfOrderEvent,
        ContainerVolumeMeasuredEvent,
        MachineOkEvent,
        DMC_EVENT_TYPE_GENL_OUT_OF_ORDER,
        DMC_EVENT_TYPE_GENL_CONTAINER_VOLUME_MEASURED,
        DMC_EVENT_TYPE_GENL_MACHINE_OK,
    )

    class NetlinkReciever:
        controller: Controller
        genlsock: GenericNetlinkSocket
        initialized = False

        def __init__(self, controller: Controller):
            print("NetlinkReceiver initialized")
            self.controller = controller
            self.genlsock = GenericNetlinkSocket()
            try:
                self.genlsock.bind(DMC_DRIVER_GENL_FAMILY, eventmsg)
                self.genlsock.add_membership(DMC_DRIVER_GENL_MCAST_GROUP_NAME)
                self.initialized = True
            except Exception as e:
                print(f"error {e}, when trying to bind to netlink socket")

        def run(self):
            if not self.initialized:
                print("NetlinkReceiver not initialized, exiting")
                return

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
            elif evt_type == DMC_EVENT_TYPE_GENL_CONTAINER_VOLUME_MEASURED:
                self.handle_container_volume_measured(
                    ContainerVolumeMeasuredEvent().from_msg(msg)
                )
            elif evt_type == DMC_EVENT_TYPE_GENL_MACHINE_OK:
                self.handle_machine_ok(MachineOkEvent().from_msg(msg))

        def handle_out_of_order(self, event: OutOfOrderEvent):
            print(
                "Out of order with msg: "
                + event.message
                + " ("
                + str(event.reason)
                + ")"
            )
            try:
                self.controller.set_state_out_of_order(event.message, event.reason)
            except Exception as e:
                print(
                    f"error {e}, when trying to set state out of order via controller"
                )

        def handle_container_volume_measured(self, event: ContainerVolumeMeasuredEvent):
            print(
                "Container volume measured for container "
                + event.container
                + " with "
                + event.volume
                + " cl"
            )
            try:
                self.controller.update_container_fluid_amount(
                    event.container, event.volume
                )
            except Exception as e:
                print(
                    f"error {e}, when trying to update container fluid amount via controller"
                )

        def handle_machine_ok(self, event: MachineOkEvent):
            print("Machine is ok")
            try:
                self.controller.clear_state_out_of_order()
            except Exception as e:
                print(
                    f"error {e}, when trying to clear state out of order via controller"
                )

else:

    class NetlinkReciever:
        def __init__(self, controller: Controller):
            print("NetlinkReceiver disabled cause not linux")

        def run(self):
            print("NetlinkReceiver disabled cause not linux")
