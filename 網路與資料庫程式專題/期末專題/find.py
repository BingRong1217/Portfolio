import sqlite3
import datetime
from datetime import datetime, timedelta

def findData(time):
    tmp = time.split('/')
    year = tmp[0]

    if tmp[1][0] == '0': month = tmp[1][1]
    else: month = tmp[1]

    if tmp[2][0] == '0': day = tmp[2][1]
    else: day = tmp[2]
    #print(year, month, day)

    conn = sqlite3.connect(r"C:\Users\user\me\網路與資料庫\final\database.db")
    cur = conn.cursor()
    cur.execute("select Year, Month, Day, Temperature, RH, WS, WD, Precp from RECORD where Year=? and Month=? and Day=?", (year, month, day))
    row = cur.fetchone()

    print("Year:", row[0])
    print("Month:", row[1])
    print("Day:", row[2])
    print("Temperature:", row[3])
    print("RH:", row[4])
    print("WS:", row[5])
    print("WD:", row[6])
    print("Precp:", row[7])
    
    date = datetime.strptime(time, '%Y/%m/%d')
    day_of_year = date.strftime("%j")

    next_date = date + timedelta(days=1)
    next_date = str(next_date).split('-')
    nextYear = next_date[0]

    if next_date[1][0] == '0': nextMonth = next_date[1][1]
    else: nextMonth = next_date[1]

    if next_date[2][0] == '0': nextDay = next_date[2][1]
    else: nextDay = next_date[2][:2]    

    cur.execute("select Precp from RECORD where Year=? and Month=? and Day=?", (nextYear, nextMonth, nextDay))
    next = cur.fetchone()
    print("next day:", next[0])

    conn.close()
    return day_of_year, row[3], row[4], row[5], row[6], row[7], next[0]

if __name__ == '__main__':
    findData('2018/10/10')
