import sqlite3

db = sqlite3.connect("favorites.db")

cur = db.cursor()

favorite = input("Favorite: ")

rows = cur.execute("SELECT COUNT (*) AS n FROM favorites WHERE problem = ?", favorite)

for row in rows:
    print(row["language"])