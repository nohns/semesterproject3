import sys

is_linux = sys.platform == "linux"
if is_linux:
    from pyroute2.netlink import NLM_F_REQUEST
    from pyroute2.netlink.generic import GenericNetlinkSocket
    from netlink.events import (
        eventmsg,
        UserConfirmEvent,
        FluidPourRequestedEvent,
        DebugEvent,
    )
    from netlink.conf import DMC_DRIVER_GENL_FAMILY

    class NetlinkPublisher:
        genlsock: GenericNetlinkSocket
        initialized = False

        def __init__(self):
            # Setup generic netlink socket for publishing events, by binding their usage to the generic netlink family
            self.genlsock = GenericNetlinkSocket()

            try:
                self.genlsock.bind(DMC_DRIVER_GENL_FAMILY, eventmsg)
                self.initialized = True
                print("NetlinkPublisher initialized")
            except Exception as e:
                print(f"error {e}, when trying to bind to netlink socket")

        def send_msg(self, msg: eventmsg):
            if not self.initialized:
                print("NetlinkPublisher not initialized, exiting")
                return

            # Send the event message
            self.genlsock.nlm_request(msg, self.genlsock.prid, msg_flags=NLM_F_REQUEST)

        def user_confirm(self):
            # Create a new message
            msg = UserConfirmEvent().to_msg()

            # Send the event message
            self.send_msg(msg)

        def pour_fluid(self, container: int, amount: int):
            # Create a new message
            msg = FluidPourRequestedEvent(container, amount).to_msg()

            # Send the event message
            self.send_msg(msg)

        def debug(self, event_type: int, data: int):
            # Create a new message
            msg = DebugEvent(event_type, data).to_msg()

            # Send the event message
            self.send_msg(msg)

else:

    class NetlinkPublisher:
        def __init__(self):
            print("NetlinkPublisher disabled cause not linux")

        def run(self):
            print("NetlinkPublisher disabled cause not linux")
