import sqlite3

 #Call database class
class Database:
    connnection: sqlite3.Connection

    def __init__(self):
        self.connection = sqlite3.connect('database.db')
        