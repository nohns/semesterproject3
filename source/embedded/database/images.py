import sqlite3
from domain.domain import Image

def get_images(connection: sqlite3.Connection):
    cursor = connection.cursor()
    
    try:
        cursor.execute("SELECT * FROM Images")
        images_data = cursor.fetchall()
        
        # Creating a list of dictionaries where each dictionary represents an image record
        images = [{"id": image_id, "path": path} for (image_id, path) in images_data]
        return images

    except sqlite3.Error as e:
        print(f"SQLite error: {e}")
        return None  

    finally:
        cursor.close()
