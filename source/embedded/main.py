import threading



 #Call database class
class Database:

    def __init__(self):
        pass

class FileStore:
    def __init__(self):
        pass

#call netlink publisher class
class Netlink_publisher:
    
    def __init__(self):
            pass

#Call controller class
class Controller:
    database: Database
    fileStore: FileStore
    netlink_publisher: Netlink_publisher
    
    def __init__(self, database, fileStore, netlink_publisher):
        self.database = database
        self.fileStore = fileStore
        self.netlink_publisher = netlink_publisher

#Call netlink reciever class
class Netlink_reciever:
    controller: Controller
    
    def __init__(self, controller):
        pass
    
    def run(self):
        pass


#call api class
class Api:
    controller: Controller
        
    def __init__(self, controller):
        pass
        
    def run(self):
        pass

class Main:
#Database and publishing events to psoc via netlink (pump control)
    database: Database
    fileStore: FileStore
    netlink_publisher: Netlink_publisher
    
#Controller which handles logic will import domain classes
    controller: Controller

#Recieving events from psoc via netlink (weight sensor)
    netlink_reciever: Netlink_reciever
#Recieving http requests from frontend
    api: Api

    def __init__(self):
    #Initialize all classes
        database = Database()
        fileStore = FileStore()
        netlink_publisher = Netlink_publisher()

        controller = Controller(database, fileStore, netlink_publisher)


#Since we are going to be recieving events from psoc and http requests from frontend we need to create threads for both
        netlink_reciever = Netlink_reciever(controller)
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

         


        
    
         
