import sqlite3

con = sqlite3.connect("flopple.db")
cursor = con.cursor()
msg = ''


try:
    cursor.execute("DROP TABLE games")
    msg += 'La Table games a été reinitialisée'
except:
    msg = "po marché"

print(msg)