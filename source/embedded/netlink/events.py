from pyroute2.netlink import genlmsg
from netlink.conf import DMC_DRIVER_GENL_VERSION

# Command for raising events
DMC_DRIVER_GENL_CMD_RAISE_EVENT = 1

"""
Drinks machine event types. See dmc/event.h in kernel driver
"""
DMC_EVENT_TYPE_GENL_OUT_OF_ORDER = 1
DMC_EVENT_TYPE_GENL_CONTAINER_WEIGHT_MEASURED = 2
DMC_EVENT_TYPE_GENL_USER_CONFIRM = 3
DMC_EVENT_TYPE_GENL_FLUID_POUR_REQUESTED = 4

class eventmsg(genlmsg):
    version = DMC_DRIVER_GENL_VERSION

    nla_map = (
        ('DMC_GENL_EVENT_ATTR_UNSPECIFIED', 'none'),
        ('DMC_GENL_EVENT_ATTR_TYPE', 'uint8'),
        ('DMC_GENL_EVENT_CONTAINER_WEIGHT_MEASURED_ATTR_CONTAINER', 'uint8'),
        ('DMC_GENL_EVENT_CONTAINER_WEIGHT_MEASURED_ATTR_WEIGHT', 'int16'),
        ('DMC_GENL_EVENT_OUT_OF_ORDER_ATTR_MESSAGE', 'asciiz'),
        ('DMC_GENL_EVENT_OUT_OF_ORDER_ATTR_REASON', 'uint8'),
        ('DMC_GENL_EVENT_FLUID_POUR_REQUESTED_ATTR_CONTAINER', 'uint8'),
        ('DMC_GENL_EVENT_FLUID_POUR_REQUESTED_ATTR_AMOUNT', 'uint8'),
    )
    
    def __init__(self, *argv, **kwarg):
        super().__init__(*argv, **kwarg)
        self['cmd'] = DMC_DRIVER_GENL_CMD_RAISE_EVENT
        self['version'] = DMC_DRIVER_GENL_VERSION

    def get_event_type(self) -> int:
        return self.get_attr('DMC_GENL_EVENT_ATTR_TYPE')

class OutOfOrderEvent(object):
    def __init__(self, message: str = None, reason: int = None):
        self.message = message
        self.reason = reason

    def to_msg(self):
        msg = eventmsg()
        msg['attrs'] = [
            ('DMC_GENL_EVENT_ATTR_TYPE', DMC_EVENT_TYPE_GENL_OUT_OF_ORDER), 
            ('DMC_GENL_EVENT_OUT_OF_ORDER_ATTR_MESSAGE', self.message), 
            ('DMC_GENL_EVENT_OUT_OF_ORDER_ATTR_REASON', self.reason)
        ]
        return msg

    def from_msg(self, msg: eventmsg):
        self.message = msg.get_attr('DMC_GENL_EVENT_OUT_OF_ORDER_ATTR_MESSAGE')
        self.reason = msg.get_attr('DMC_GENL_EVENT_OUT_OF_ORDER_ATTR_REASON')
        return self

class ContainerWeightMeasuredEvent(object):
    def __init__(self, container: int = None, weight: int = None):
        self.container = container
        self.weight = weight

    def to_msg(self):
        msg = eventmsg()
        msg['attrs'] = [
            ('DMC_GENL_EVENT_ATTR_TYPE', DMC_EVENT_TYPE_GENL_CONTAINER_WEIGHT_MEASURED), 
            ('DMC_GENL_EVENT_CONTAINER_WEIGHT_MEASURED_ATTR_CONTAINER', self.container), 
            ('DMC_GENL_EVENT_CONTAINER_WEIGHT_MEASURED_ATTR_WEIGHT', self.weight)
        ]
        return msg

    def from_msg(self, msg: eventmsg):
        self.container = msg.get_attr('DMC_GENL_EVENT_CONTAINER_WEIGHT_MEASURED_ATTR_CONTAINER')
        self.weight = msg.get_attr('DMC_GENL_EVENT_CONTAINER_WEIGHT_MEASURED_ATTR_WEIGHT')
        return self

class UserConfirmEvent(object):


    def to_msg(self):
        msg = eventmsg()
        msg['attrs'] = [
            ('DMC_GENL_EVENT_ATTR_TYPE', DMC_EVENT_TYPE_GENL_USER_CONFIRM)
        ]
        return msg

    def from_msg(self, msg: eventmsg):
        self.container = msg.get_attr('DMC_GENL_EVENT_FLUID_POUR_REQUESTED_ATTR_CONTAINER')
        self.amount = msg.get_attr('DMC_GENL_EVENT_FLUID_POUR_REQUESTED_ATTR_AMOUNT')
        return self

class FluidPourRequestedEvent(object):
    def __init__(self, container: int = None, amount: int = None):
        self.container = container
        self.amount = amount

    def to_msg(self):
        msg = eventmsg()
        msg['attrs'] = [
            ('DMC_GENL_EVENT_ATTR_TYPE', DMC_EVENT_TYPE_GENL_FLUID_POUR_REQUESTED), 
            ('DMC_GENL_EVENT_FLUID_POUR_REQUESTED_ATTR_CONTAINER', self.container), 
            ('DMC_GENL_EVENT_FLUID_POUR_REQUESTED_ATTR_AMOUNT', self.amount)
        ]
        return msg

    def from_msg(self, msg: eventmsg):
        self.container = msg.get_attr('DMC_GENL_EVENT_FLUID_POUR_REQUESTED_ATTR_CONTAINER')
        self.amount = msg.get_attr('DMC_GENL_EVENT_FLUID_POUR_REQUESTED_ATTR_AMOUNT')
        return self
