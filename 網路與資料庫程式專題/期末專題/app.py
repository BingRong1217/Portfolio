from flask import Flask, render_template, url_for, request
from testFutureInput import *
from testFuture import *

app = Flask(__name__)
app.debug = True

def queryFunction():
    import datetime

    temperature, rh, ws, wd, precp, tomorrowRain, myPredict = predict('now')
    getDate = datetime.date.today()
    getDate = str(getDate)
    getDate = getDate.split('-')
    info = [getDate[0], getDate[1], getDate[2], temperature, rh, ws, wd, precp]
    result = tomorrowRain

    return render_template('query.html', info=info, result=result, myPredict=myPredict)

def recordFunction():
    inputYear = request.form.get('inputYear', '')
    inputMonth = request.form.get('inputMonth', '')
    inputDay = request.form.get('inputDay', '')

    if len(inputMonth) == 1: inputMonth = '0' + inputMonth
    if len(inputDay) == 1: inputDay = '0' + inputDay

    choose = inputYear + '/' + inputMonth + '/' + inputDay
    temperature, rh, ws, wd, precp, tomorrowRain, myPredict = predict(choose)
    info = [inputYear, inputMonth, inputDay, temperature, rh, ws, wd, precp]
    result = [tomorrowRain, myPredict]

    return render_template('record.html', info=info, result=result)

def correctFunction():
    startYear = request.form.get('startYear', '')
    startMonth = request.form.get('startMonth', '')
    startDay = request.form.get('startDay', '')
    endYear = request.form.get('endYear', '')
    endMonth = request.form.get('endMonth', '')
    endDay = request.form.get('endDay', '')
    
    accuracy = calculate(startYear, startMonth, startDay, endYear, endMonth, endDay)
    return render_template('correct.html', accuracy=accuracy)

@app.route('/')
def home():
    return render_template('index.html') 

@app.route('/index.html')
def index():
    return render_template('index.html')

@app.route('/query.html', methods=['GET','POST'])
def query():
    if request.method=='POST':
        return queryFunction()
    else:
        return render_template('query.html')   
    
@app.route('/record.html', methods=['GET','POST'])
def record():
    if request.method=='POST':
        return recordFunction()
    else:
        return render_template('record.html')   
    
@app.route('/correct.html', methods=['GET','POST'])
def correct():
    if request.method=='POST':
        return correctFunction()
    else:
        return render_template('correct.html')

if __name__ == "__main__":
    app.run(host='127.0.0.1', port=80, debug=True)
