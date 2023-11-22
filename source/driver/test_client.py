from pyroute2.netlink import NLM_F_REQUEST
from pyroute2.netlink import genlmsg
from pyroute2.netlink.generic import GenericNetlinkSocket


DMC_DRIVER_GENL_VERSION = 1

DMC_EVENT_TYPE_GENL_USER_CONFIRM = 3
DMC_EVENT_TYPE_GENL_FLUID_POUR_REQUESTED = 4

class UserConfirmEvent(genlmsg):
    cmd = DMC_EVENT_TYPE_GENL_USER_CONFIRM
    version = DMC_DRIVER_GENL_VERSION
    nla_map = (
        ('DMC_EVENT_GENL_USER_CONFIRM_ATTR_UNSPECIFIED', 'none'),
        ('DMC_EVENT_GENL_USER_CONFIRM_ATTR_TYPE', 'uint8'),
    )

class FluidPourRequestedEvent(genlmsg):
    cmd = DMC_EVENT_TYPE_GENL_FLUID_POUR_REQUESTED
    version = DMC_DRIVER_GENL_VERSION
    nla_map = (
        ('DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_UNSPECIFIED', 'none'),
        ('DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_TYPE', 'uint8'),
        ('DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_CONTAINER', 'uint8'),
        ('DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_AMOUNT', 'uint8'),
    )

# Define the Netlink group ID you want to listen to
NETLINK_GROUP_ID = 1

RLINK_CMD_UNSPEC = 0
RLINK_CMD_REQ = 1

def send_user_confirm_event(socket: GenericNetlinkSocket):
    # Create a new message
    msg = UserConfirmEvent()

    msg['cmd'] = DMC_EVENT_TYPE_GENL_USER_CONFIRM
    msg['version'] = DMC_DRIVER_GENL_VERSION

    # Set the attributes
    msg['attrs'] = [
        ('DMC_EVENT_GENL_USER_CONFIRM_ATTR_TYPE', DMC_EVENT_TYPE_GENL_USER_CONFIRM)
    ]

    # Send the message
    socket.nlm_request(msg, socket.prid, msg_flags=NLM_F_REQUEST)

def send_fluid_pour_requested_event(socket: GenericNetlinkSocket, container, amount):
    # Create a new message
    msg = FluidPourRequestedEvent()

    msg['cmd'] = DMC_EVENT_TYPE_GENL_FLUID_POUR_REQUESTED
    msg['version'] = DMC_DRIVER_GENL_VERSION

    # Set the attributes
    msg['attrs'] = [
        ('DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_TYPE', DMC_EVENT_TYPE_GENL_FLUID_POUR_REQUESTED),
        ('DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_CONTAINER', container),
        ('DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_AMOUNT', amount),
    ]

    # Send the message
    socket.nlm_request(msg, socket.prid, msg_flags=NLM_F_REQUEST)

def handle_netlink_message(msg):
    print(f"Received Netlink message: {msg.get('message')}")

def main():
    #try:
        # create protocol instance
        genlsock = GenericNetlinkSocket()
        genlsock.bind('DMC_DRIVER_FAM', UserConfirmEvent)
        genlsock.bind('DMC_DRIVER_FAM', FluidPourRequestedEvent)
        # request a method
        print(send_fluid_pour_requested_event(genlsock, 1, 2))
        print(send_user_confirm_event(genlsock))
    # except:
    #     # if there was an error, log it to the console
    #     print('frick')
    # finally:
    #     # finally -- release the instance
    #     genlsock.close()

if __name__ == '__main__':
    main()
