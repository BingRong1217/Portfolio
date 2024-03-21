import pandas as pd
from sklearn import tree
import matplotlib.pyplot as plt
from sklearn.tree import DecisionTreeRegressor
from crawler import *
from find import *

def predict(choose):
    df1 = pd.read_csv('future2018-2022(1).csv')
    trainX = df1.drop(columns=['Rain'])
    trainY = df1['Rain']

    for i in trainY:
        if i == 'No': trainY = trainY.replace(i, 0)
        else: trainY = trainY.replace(i, 1)

    clf = DecisionTreeRegressor(criterion='absolute_error', max_depth=4, splitter='best', random_state=42)
    clf = clf.fit(trainX, trainY)

    if choose == 'now':
        obstime, temperature, rh, ws, wd, precp = crawl()
        tomorrowRain = future()
    else: obstime, temperature, rh, ws, wd, precp, tomorrowRain = findData(choose)

    testX = pd.DataFrame([[obstime, temperature, rh, ws, wd, precp]], columns=['ObsTime', 'Temperature', 'RH', 'WS', 'WD', 'Precp'])

    predictions = clf.predict(testX)
    if int(predictions[0]) == 0: predict = "不下雨"
    else: predict = "下雨"
    print("predict: " + str(int(predictions[0])))
    return temperature, rh, ws, wd, precp, tomorrowRain, predict

    #tree.plot_tree(clf, feature_names=trainX.columns, class_names=['No', 'Yes'], filled=True, fontsize=5)
    #plt.show()

if __name__ == '__main__':
    choose = '2018/09/13'
    predict(choose)

