from pyroute2.netlink import genlmsg


DMC_DRIVER_GENL_VERSION = 1

DMC_EVENT_TYPE_GENL_USER_CONFIRM = 3
DMC_EVENT_TYPE_GENL_FLUID_POUR_REQUESTED = 4

class BaseEvent(genlmsg):
    version = DMC_DRIVER_GENL_VERSION
    
    def __init__(self, *argv, **kwarg):
        super().__init__(*argv, **kwarg)
        self['cmd'] = self.evt_type
        self['version'] = DMC_DRIVER_GENL_VERSION

class UserConfirmEvent(BaseEvent):
    evt_type = DMC_EVENT_TYPE_GENL_USER_CONFIRM
    nla_map = (
        ('DMC_EVENT_GENL_USER_CONFIRM_ATTR_UNSPECIFIED', 'none'),
        ('DMC_EVENT_GENL_USER_CONFIRM_ATTR_TYPE', 'uint8'),
    )

    def set(self):
        self['attrs'] = [
            ('DMC_EVENT_GENL_USER_CONFIRM_ATTR_TYPE', self.evt_type)
        ]

class FluidPourRequestedEvent(BaseEvent):
    evt_type = DMC_EVENT_TYPE_GENL_FLUID_POUR_REQUESTED
    nla_map = (
        ('DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_UNSPECIFIED', 'none'),
        ('DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_TYPE', 'uint8'),
        ('DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_CONTAINER', 'uint8'),
        ('DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_AMOUNT', 'uint8'),
    )

    def set(self, container, amount):
        self['attrs'] = [
            ('DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_TYPE', self.evt_type),
            ('DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_CONTAINER', container),
            ('DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_AMOUNT', amount),
        ]