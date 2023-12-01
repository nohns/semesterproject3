from pyroute2.netlink import genlmsg
from netlink.conf import DMC_DRIVER_GENL_VERSION

# Command for raising events
DMC_DRIVER_GENL_CMD_RAISE_EVENT = 1

"""
Drinks machine event types. See dmc/event.h in kernel driver
"""
DMC_EVENT_TYPE_GENL_OUT_OF_ORDER = 1
DMC_EVENT_TYPE_GENL_CONTAINER_VOLUME_MEASURED = 2
DMC_EVENT_TYPE_GENL_USER_CONFIRM = 3
DMC_EVENT_TYPE_GENL_FLUID_POUR_REQUESTED = 4
DMC_EVENT_TYPE_GENL_MACHINE_OK = 5
DMC_EVENT_TYPE_GENL_DEBUG = 6


class eventmsg(genlmsg):
    version = DMC_DRIVER_GENL_VERSION

    nla_map = (
        ("DMC_GENL_EVENT_ATTR_UNSPECIFIED", "none"),
        ("DMC_GENL_EVENT_ATTR_TYPE", "uint8"),
        ("DMC_GENL_EVENT_CONTAINER_VOLUME_MEASURED_ATTR_CONTAINER", "uint8"),
        ("DMC_GENL_EVENT_CONTAINER_VOLUME_MEASURED_ATTR_VOLUME", "int16"),
        ("DMC_GENL_EVENT_OUT_OF_ORDER_ATTR_MESSAGE", "asciiz"),
        ("DMC_GENL_EVENT_OUT_OF_ORDER_ATTR_REASON", "uint8"),
        ("DMC_GENL_EVENT_FLUID_POUR_REQUESTED_ATTR_CONTAINER", "uint8"),
        ("DMC_GENL_EVENT_FLUID_POUR_REQUESTED_ATTR_AMOUNT", "uint8"),
        ("DMC_GENL_EVENT_DEBUG_ATTR_EVENT_TYPE", "uint8"),
        ("DMC_GENL_EVENT_DEBUG_ATTR_DATA", "uint8"),
    )

    def __init__(self, *argv, **kwarg):
        super().__init__(*argv, **kwarg)
        self["cmd"] = DMC_DRIVER_GENL_CMD_RAISE_EVENT
        self["version"] = DMC_DRIVER_GENL_VERSION

    def get_event_type(self) -> int:
        return self.get_attr("DMC_GENL_EVENT_ATTR_TYPE")


class OutOfOrderEvent(object):
    def __init__(self, message: str = None, reason: int = None):
        self.message = message
        self.reason = reason

    def to_msg(self):
        msg = eventmsg()
        msg["attrs"] = [
            ("DMC_GENL_EVENT_ATTR_TYPE", DMC_EVENT_TYPE_GENL_OUT_OF_ORDER),
            ("DMC_GENL_EVENT_OUT_OF_ORDER_ATTR_MESSAGE", self.message),
            ("DMC_GENL_EVENT_OUT_OF_ORDER_ATTR_REASON", self.reason),
        ]
        return msg

    def from_msg(self, msg: eventmsg):
        self.message = msg.get_attr("DMC_GENL_EVENT_OUT_OF_ORDER_ATTR_MESSAGE")
        self.reason = msg.get_attr("DMC_GENL_EVENT_OUT_OF_ORDER_ATTR_REASON")
        return self


class ContainerWeightMeasuredEvent(object):
    def __init__(self, container: int = None, weight: int = None):
        self.container = container
        self.volume = weight

    def to_msg(self):
        msg = eventmsg()
        msg["attrs"] = [
            ("DMC_GENL_EVENT_ATTR_TYPE", DMC_EVENT_TYPE_GENL_CONTAINER_VOLUME_MEASURED),
            ("DMC_GENL_EVENT_CONTAINER_VOLUME_MEASURED_ATTR_CONTAINER", self.container),
            ("DMC_GENL_EVENT_CONTAINER_VOLUME_MEASURED_ATTR_VOLUME", self.volume),
        ]
        return msg

    def from_msg(self, msg: eventmsg):
        self.container = msg.get_attr(
            "DMC_GENL_EVENT_CONTAINER_VOLUME_MEASURED_ATTR_CONTAINER"
        )
        self.volume = msg.get_attr(
            "DMC_GENL_EVENT_CONTAINER_VOLUME_MEASURED_ATTR_VOLUME"
        )
        return self


class UserConfirmEvent(object):
    def to_msg(self):
        msg = eventmsg()
        msg["attrs"] = [("DMC_GENL_EVENT_ATTR_TYPE", DMC_EVENT_TYPE_GENL_USER_CONFIRM)]
        return msg

    def from_msg(self, msg: eventmsg):
        self.container = msg.get_attr(
            "DMC_GENL_EVENT_FLUID_POUR_REQUESTED_ATTR_CONTAINER"
        )
        self.amount = msg.get_attr("DMC_GENL_EVENT_FLUID_POUR_REQUESTED_ATTR_AMOUNT")
        return self


class FluidPourRequestedEvent(object):
    def __init__(self, container: int = None, amount: int = None):
        self.container = container
        self.amount = amount

    def to_msg(self):
        msg = eventmsg()
        msg["attrs"] = [
            ("DMC_GENL_EVENT_ATTR_TYPE", DMC_EVENT_TYPE_GENL_FLUID_POUR_REQUESTED),
            ("DMC_GENL_EVENT_FLUID_POUR_REQUESTED_ATTR_CONTAINER", self.container),
            ("DMC_GENL_EVENT_FLUID_POUR_REQUESTED_ATTR_AMOUNT", self.amount),
        ]
        return msg

    def from_msg(self, msg: eventmsg):
        self.container = msg.get_attr(
            "DMC_GENL_EVENT_FLUID_POUR_REQUESTED_ATTR_CONTAINER"
        )
        self.amount = msg.get_attr("DMC_GENL_EVENT_FLUID_POUR_REQUESTED_ATTR_AMOUNT")
        return self


class MachineOkEvent(object):
    def to_msg(self):
        msg = eventmsg()
        msg["attrs"] = [("DMC_GENL_EVENT_ATTR_TYPE", DMC_EVENT_TYPE_GENL_MACHINE_OK)]
        return msg

    def from_msg(self, msg: eventmsg):
        return self


class DebugEvent(object):
    def __init__(self, event_type: int = None, data: int = None):
        self.event_type = event_type
        self.data = data

    def to_msg(self):
        msg = eventmsg()
        msg["attrs"] = [
            ("DMC_GENL_EVENT_ATTR_TYPE", DMC_EVENT_TYPE_GENL_DEBUG),
            ("DMC_GENL_EVENT_DEBUG_ATTR_EVENT_TYPE", self.event_type),
            ("DMC_GENL_EVENT_DEBUG_ATTR_DATA", self.data),
        ]
        return msg

    def from_msg(self, msg: eventmsg):
        self.event_type = msg.get_attr("DMC_GENL_EVENT_DEBUG_ATTR_EVENT_TYPE")
        self.data = msg.get_attr("DMC_GENL_EVENT_DEBUG_ATTR_DATA")
        return self
