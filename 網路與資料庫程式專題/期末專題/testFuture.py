import pandas as pd
from sklearn import tree
import matplotlib.pyplot as plt
from sklearn.tree import DecisionTreeRegressor
from sklearn.metrics import accuracy_score
import sqlite3
from datetime import datetime

def calculate(startYear, startMonth, startDay, endYear, endMonth, endDay):
    df1 = pd.read_csv('future2018-2022(1).csv')
    trainX = df1.drop(columns=['Rain'])
    trainY = df1['Rain']

    for i in trainY:
        if i == 'No': trainY = trainY.replace(i, 0)
        else: trainY = trainY.replace(i, 1)

    clf = DecisionTreeRegressor(criterion='absolute_error', max_depth=4, splitter='best', random_state=42)
    clf = clf.fit(trainX, trainY)

    conn = sqlite3.connect(r"C:\Users\user\me\網路與資料庫\final\database.db")
    cur = conn.cursor()

    cur.execute("select ROWID from RECORD where Year=? and Month=? and Day=?", (startYear, startMonth, startDay))
    row = cur.fetchone()
    #if row is None: return 0
    startRow = row[0]

    cur.execute("select ROWID from RECORD where Year=? and Month=? and Day=?", (endYear, endMonth, endDay))
    row = cur.fetchone()
    endRow = row[0]

    testXarray = []
    testYarray = []
    for i in range(startRow, endRow + 2):
        flag = False
        if i != endRow + 1:
            cur.execute("select Year, Month, Day, Temperature, RH, WS, WD, Precp from RECORD where ROWID=?", (str(i),))
            row = cur.fetchone()
            if row is None: continue
            
            subArray = []
            year = row[0]

            if len(row[1]) == 1: month = '0' + row[1]
            else: month =  row[1]

            if len(row[2]) == 1: day = '0' + row[2]
            else: day = row[2]            

            time = year + '/' + month + '/' + day
            date = datetime.strptime(time, '%Y/%m/%d')
            day_of_year = date.strftime("%j")

            subArray.append(day_of_year)
            subArray.append(row[3])
            subArray.append(row[4])
            subArray.append(row[5])
            subArray.append(row[6])
            subArray.append(row[7])

            flag = True
            
        if i != startRow:
            cur.execute("select Precp from RECORD where ROWID=?", (str(i),))
            row = cur.fetchone()
            if row is None: continue

            if row[0] == '0': testYarray.append(0)
            else: testYarray.append(1)

        if flag == True: testXarray.append(subArray)

    testX = pd.DataFrame(testXarray, columns=['ObsTime', 'Temperature', 'RH', 'WS', 'WD', 'Precp'])
    print(testX)
    testY = pd.DataFrame(testYarray, columns=['Rain'])
    conn.close()

    predictions = clf.predict(testX)
    acc = accuracy_score(testY, predictions)
    print('accuracy: ', acc)

    #tree.plot_tree(clf, feature_names=trainX.columns, class_names=['No', 'Yes'], filled=True, fontsize=6)
    #plt.show()
    return acc

if __name__ == '__main__':
    acc = calculate('2018', '1', '1', '2023', '1', '31')
