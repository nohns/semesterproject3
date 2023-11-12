from database.database import Database
from domain.domain import Image

def get_images(database: Database) -> list[Image] :
    try:
        images=database.get_images()
        return images
    except Exception as e:
        print(f"error {e}, when trying to get images from database to controller")
        return None