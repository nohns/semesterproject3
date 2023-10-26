#Call controller class
from database.database import Database
from netlink.publisher import NetlinkPublisher

class Controller:
    database: Database
    netlink_publisher: NetlinkPublisher
    
    def __init__(self, database: Database, netlink_publisher: NetlinkPublisher):
        self.database = database
        self.netlink_publisher = netlink_publisher