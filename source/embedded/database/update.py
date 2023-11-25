import sqlite3


def update(connection: sqlite3.Connection) -> bool:
    cursor = connection.cursor()
    cursor.execute("SELECT status FROM updates")
    status = cursor.fetchone()

    print("Status from database: ", status)

    if status is None:
        cursor.execute("INSERT INTO updates VALUES (FALSE)")
        connection.commit()
        cursor.close()
        return False

    if status[0] == 0:
        cursor.close()
        return False

    if status[0] == 1:
        cursor.execute("UPDATE updates SET status = FALSE")
        connection.commit()
        cursor.close()
        return True

    cursor.close()
    return False


def set_status_to_true(connection: sqlite3.Connection) -> None:
    cursor = connection.cursor()

    cursor.execute("UPDATE updates SET status = TRUE")
    connection.commit()  # Commit the change

    cursor.close()
    print("Status set to True successfully.")
