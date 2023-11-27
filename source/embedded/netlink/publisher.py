import sys

is_linux = sys.platform == "Linux"
if is_linux:
    from pyroute2.netlink import NLM_F_REQUEST
    from pyroute2.netlink.generic import GenericNetlinkSocket
    from netlink.events import eventmsg, UserConfirmEvent, FluidPourRequestedEvent
    from netlink.conf import DMC_DRIVER_GENL_FAMILY

    # call netlink publisher class
    class NetlinkPublisher:
        genlsock: GenericNetlinkSocket

        def __init__(self):
            # Setup generic netlink socket for publishing events, by binding their usage to the generic netlink family
            self.genlsock = GenericNetlinkSocket()
            self.genlsock.bind(DMC_DRIVER_GENL_FAMILY, eventmsg)

            print("NetlinkPublisher initialized")

        def user_confirm(self):
            # Create a new message
            msg = UserConfirmEvent().to_msg()

            # Send the event message
            self.genlsock.nlm_request(msg, self.genlsock.prid, msg_flags=NLM_F_REQUEST)

        def pour_fluid(self, container: int, amount: int):
            # Create a new message
            msg = FluidPourRequestedEvent(container, amount).to_msg()

            # Send the event message
            self.genlsock.nlm_request(msg, self.genlsock.prid, msg_flags=NLM_F_REQUEST)

else:

    class NetlinkPublisher:
        def __init__(self):
            print("NetlinkPublisher disabled cause not linux")

        def run(self):
            print("NetlinkPublisher disabled cause not linux")
