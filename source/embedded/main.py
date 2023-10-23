import threading



 #Call database class
class Database:

    def __init__(self):
        pass

class FileStore:
    def __init__(self):
        pass

#call netlink publisher class
class NetlinkPublisher:
    
    def __init__(self):
        pass

#Call controller class
class Controller:
    database: Database
    fileStore: FileStore
    netlink_publisher: NetlinkPublisher
    
    def __init__(self, database: Database, fileStore: FileStore, netlink_publisher: NetlinkPublisher):
        self.database = database
        self.fileStore = fileStore
        self.netlink_publisher = netlink_publisher

#Call netlink reciever class
class NetlinkReciever:
    controller: Controller
    
    def __init__(self, controller: Controller):
        self.controller = controller

#call api class
class Api:
    controller: Controller
        
    def __init__(self, controller: Controller):
        self.controller = controller
        
class Main:
#Database and publishing events to psoc via netlink (pump control)
    database: Database
    file_store: FileStore
    netlink_publisher: NetlinkPublisher
    
#Controller which handles logic will import domain classes
    controller: Controller

#Recieving events from psoc via netlink (weight sensor)
    netlink_reciever: NetlinkReciever
#Recieving http requests from frontend
    api: Api

    def __init__(self):
    #Initialize all classes
        database = Database()
        file_store = FileStore()
        netlink_publisher = NetlinkPublisher()

        controller = Controller(database, file_store, netlink_publisher)


#Since we are going to be recieving events from psoc and http requests from frontend we need to create threads for both
        netlink_reciever = NetlinkReciever(controller)
        api = Api(controller)

        # Create threads for netlink_reciever and api
        netlink_reciever_thread = threading.Thread(target=netlink_reciever.run)
        api_thread = threading.Thread(target=api.run)

        # Start the threads
        netlink_reciever_thread.start()
        api_thread.start()

        # Wait for the threads to finish (which should be never)
        netlink_reciever_thread.join()
        api_thread.join()

if __name__ == '__main__':
    Main()

         


        
    
         
