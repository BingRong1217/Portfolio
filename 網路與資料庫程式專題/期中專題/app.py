import sqlite3
from flask import Flask, render_template, url_for, request, redirect
import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
import time
from prettytable import PrettyTable
import requests

app = Flask(__name__)
app.debug = True

categoryOptions = ['生活用品', '電子產品', '飲料', '零食', '蔬果', '蛋豆魚肉', '玩具', '文具', '書籍', '其他']

def sendLineNotification(content):
    content = "\n" + content
    token = 'eaRh5wK1M7hOd62EsNC46VmhoOSBHnrSqaHaEv3bEfW'   # 發行的權杖
    payload = {'message': content, 'stickerPackageId': '6632', 'stickerId': '11825384'}
    requests.post('https://notify-api.line.me/api/notify', headers = {'Authorization': 'Bearer {}'.format(token)}, params = payload)
    print("success")

def sendMail(subject, content):
    msg = MIMEMultipart()
    msg["From"] = "joseph910905@gmail.com"
    msg["To"] = "joy.brwu@gmail.com"
    msg["Subject"] = subject
    msg.attach(MIMEText(content))
    acc = "joseph910905@gmail.com"
 
    with smtplib.SMTP(host="smtp.gmail.com", port="587") as smtp:  # 設定SMTP伺服器
        smtp.ehlo()  # 驗證SMTP伺服器
        smtp.starttls()  # 建立加密傳輸
        smtp.login(acc,"ccpofflososaylqz")  # 登入寄件者gmail
        smtp.send_message(msg)  # 寄送郵件    

    sendLineNotification(content)

def getID(category):
    for i in range(len(categoryOptions)): 
        if category == categoryOptions[i]: return i + 1

def queryFunction(category):
    item = request.form.get('item', '')
 
    if item == '':
        itemOptions = []
        categoryID = getID(category)

        conn = sqlite3.connect('database.db')
        cur = conn.cursor()
        cur.execute("Select Name from COMMODITY where Category = ?", [str(categoryID)])
        rows = cur.fetchall()

        for row in rows: itemOptions.append(row[0])

        return render_template('query.html', itemOptions=itemOptions, categoryOptions=categoryOptions, selectedOption=category)
    
    conn = sqlite3.connect('database.db')
    cur = conn.cursor()

    cur.execute("Select ROWID, Cost, Price, Firm from COMMODITY where Name = ?", [item])
    row1 = cur.fetchone()
    if row1 is None: return render_template(url_for('show'), string="查無該筆資料！")

    cur.execute("Select Inventory from INVENTORY where Commodity = ?", [row1[0]])
    row2 = cur.fetchone()
    if row2 is None: return render_template(url_for('show'), string="查無該筆資料！")

    cur.execute("Select Name, Phone from FIRM where ROWID = ?", [row1[0]])
    row3 = cur.fetchone()
    if row3 is None: return render_template(url_for('show'), string="查無該筆資料！")

    info = [category, item, int(row2[0]), row1[1], row1[2], row3[0], row3[1]]

    return render_template('query.html', info=info, categoryOptions=categoryOptions)

def newFunction():
    category = request.form.get('category', '')
    item = request.form.get('item', '')
    firm = request.form.get('firm', '')
    phone = request.form.get('phone', '')
    cost = request.form.get('cost', '')
    price = request.form.get('price', '')

    if category == "" or item == "" or firm == "" or phone == "" or cost == "" or price == "": return render_template(url_for('show'), string="新增失敗！")

    conn = sqlite3.connect('database.db')
    cur = conn.cursor()

    cur.execute("Select ROWID, Name from FIRM where Name = ?", [firm])
    row1 = cur.fetchone()

    if row1 is None: 
        cur.execute("Insert into FIRM Values(?, ?)", (firm, phone))
        conn.commit()
        cur.execute("Select ROWID from FIRM where Name = ?", [firm])
        row1 = cur.fetchone()

    cur.execute("Select Name from COMMODITY where Name = ?", [item])
    row2 = cur.fetchone()

    if row2 is None: 
        cur.execute("Insert into COMMODITY Values(?, ?, ?, ?, ?)", (item, category, cost, price, row1[0]))
        conn.commit()

        cur.execute("Select ROWID from COMMODITY where Name = ?", [item])
        row3 = cur.fetchone()
        cur.execute("Insert into INVENTORY Values(?, ?)", (row3[0], 0))

        conn.commit()
        conn.close()
        return render_template(url_for('show'), string="新增成功！")
    
    else: 
        conn.close()
        return render_template(url_for('show'), string="品項已存在！")

def buyFunction(category):
    now = time.localtime()
    now = time.strftime("%Y/%m/%d %H:%M:%S", now)
    item = request.form.get('item', '')

    if item == '':
        itemOptions = []
        categoryID = getID(category)

        conn = sqlite3.connect('database.db')
        cur = conn.cursor()
        cur.execute("Select Name from COMMODITY where Category = ?", [str(categoryID)])
        rows = cur.fetchall()

        for row in rows: itemOptions.append(row[0])

        return render_template('buy.html', itemOptions=itemOptions, categoryOptions=categoryOptions, selectedOption=category)

    num = request.form.get('num', '')
    if num == "" or int(num) <= 0: return render_template(url_for('show'), string="數量錯誤！")

    conn = sqlite3.connect('database.db')
    cur = conn.cursor()

    cur.execute("Select ROWID, Name from COMMODITY where Name = ?", [item])
    row = cur.fetchone()

    commodityID = row[0]

    cur.execute("Select Inventory from INVENTORY where Commodity = ?", [commodityID])
    row = cur.fetchone()
    
    if row is None: 
        cur.execute("Insert into INVENTORY Values(?, ?)", (commodityID, num))
        cur.execute("Insert into RECORD Values(?, ?, ?)", (commodityID, num, now))
        conn.commit()
        conn.close()

        content = "進貨：" + item + " x " + num
        sendMail("進貨", content)

        return render_template(url_for('show'), string="已新增至庫存！")        

    inventory = row[0]
    newValue = int(inventory) + int(num)
            
    cur.execute("update INVENTORY set Inventory = ? where Commodity = ?", (newValue, commodityID))
    cur.execute("Insert into RECORD Values(?, ?, ?)", (commodityID, num, now))
    conn.commit()
    conn.close()

    content = "進貨：" + item + " x " + num
    sendMail("進貨", content)

    return render_template(url_for('show'), string="已新增至庫存！")

def saleFunction(category):
    now = time.localtime()
    now = time.strftime("%Y/%m/%d %H:%M:%S", now)    
    item = request.form.get('item', '')

    if item == '':
        itemOptions = []
        categoryID = getID(category)

        conn = sqlite3.connect('database.db')
        cur = conn.cursor()
        cur.execute("Select Name from COMMODITY where Category = ?", [str(categoryID)])
        rows = cur.fetchall()

        for row in rows: itemOptions.append(row[0])

        return render_template('sale.html', itemOptions=itemOptions, categoryOptions=categoryOptions, selectedOption=category)

    num = request.form.get('num', '')
    if num == "" or int(num) <= 0: return render_template(url_for('show'), string="數量錯誤！")

    conn = sqlite3.connect('database.db')
    cur = conn.cursor()

    cur.execute("Select ROWID, Name from COMMODITY where Name = ?", [item])
    row = cur.fetchone()

    commodityID = row[0]

    cur.execute("Select Inventory from INVENTORY where Commodity = ?", [commodityID])
    row = cur.fetchone()
    if row is None: return render_template(url_for('show'), string="無庫存！")

    inventory = row[0]
    newValue = int(inventory) - int(num)

    if newValue > 0: 
        cur.execute("update INVENTORY set Inventory = ? where Commodity = ?", (newValue, commodityID))
        cur.execute("Insert into RECORD Values(?, ?, ?)", (commodityID, -int(num), now))

    elif newValue == 0:
        cur.execute("delete from INVENTORY where Commodity = ?", [commodityID])
        cur.execute("Insert into RECORD Values(?, ?, ?)", (commodityID, -int(num), now))

    else: return render_template(url_for('show'), string="庫存不足！")

    conn.commit()
    conn.close()

    content = "售出：" + item + " x " + num
    sendMail("售出", content)

    return render_template(url_for('show'), string="已從庫存刪除！")

def recordFunction(category):
    item = request.form.get('item', '')
    inputYear = request.form.get('year', '')
    startMonth = request.form.get('startMonth', '')
    endMonth = request.form.get('endMonth', '')
    startDay = request.form.get('startDay', '')
    endDay = request.form.get('endDay', '')
 
    if item == '' or inputYear == '' or startMonth == ''  or endMonth == '' or startDay == '' or endDay == '':
        itemOptions = []
        categoryID = getID(category)

        conn = sqlite3.connect('database.db')
        cur = conn.cursor()
        cur.execute("Select Name from COMMODITY where Category = ?", [str(categoryID)])
        rows = cur.fetchall()

        for row in rows: itemOptions.append(row[0])

        return render_template('record.html', itemOptions=itemOptions, categoryOptions=categoryOptions, selectedOption=category)

    info = []
    sum = 0
    conn = sqlite3.connect('database.db')
    cur = conn.cursor()
    cur.execute("Select ROWID, Cost, Price from COMMODITY where Name = ?", [item])
    row1 = cur.fetchone()
    cost = int(row1[1])
    price = int(row1[2])

    cur.execute("Select Quantity, Time from RECORD where Commodity = ?", [row1[0]])
    row2 = cur.fetchall()

    for row in row2:
        year = int(row[1][:4])
        month = int(row[1][5:7])
        day = int(row[1][8:10])

        if year != int(inputYear): continue
        if month < int(startMonth) or month > int(endMonth): continue
        if month == int(startMonth):
            if day < int(startDay): continue
        if month == int(endMonth):
            if day > int(endDay): continue
            
        num = int(row[0])
        if num > 0: 
            string = "進貨"
            money = num * cost
            sum -= money
        else: 
            num = -num
            string = "售出"
            money = num * price
            sum += money

        tmp = [string, num, money, row[1]]
        info.append(tmp)

    if info == []: return render_template(url_for('show'), string="查無該筆資料！")

    table = PrettyTable(["進出貨", "數量", "進出帳", "時間"])
    for i in info: table.add_row(i)
    content = table.get_string()
    content += "\n" + "總金額：" + str(sum)
    sendMail("進出貨紀錄", content)  

    return render_template('record.html', info=info, categoryOptions=categoryOptions, sum=sum)

@app.route('/')
def home():
    return render_template('index.html') 

@app.route('/index.html')
def index():
    return render_template('index.html')

@app.route('/query.html', methods=['GET','POST'])
def query():
    category = request.form.get('category', '')
    if category == '':
        return render_template('query.html', categoryOptions=categoryOptions, selectedOption=category)
    else:
        return queryFunction(category)

@app.route('/new.html', methods=['GET','POST'])
def new():
    if request.method=='POST':
        return newFunction()
    else:
        return render_template('new.html')

@app.route('/buy.html', methods=['GET','POST'])
def buy():
    category = request.form.get('category', '')
    if category == '':
        return render_template('buy.html', categoryOptions=categoryOptions, selectedOption=category)
    else:
        return buyFunction(category)

@app.route('/sale.html', methods=['GET','POST'])
def sale():
    category = request.form.get('category', '')
    if category == '':
        return render_template('sale.html', categoryOptions=categoryOptions, selectedOption=category)
    else:
        return saleFunction(category)
    
@app.route('/record.html', methods=['GET','POST'])
def record():
    category = request.form.get('category', '')
    if category == '':
        return render_template('record.html', categoryOptions=categoryOptions, selectedOption=category)
    else:
        return recordFunction(category)
    
@app.route('/show.html', methods=['GET','POST'])
def show():
    if request.method=='POST':
        return render_template('index.html')
    else:
        return render_template('show.html', "")

if __name__ == "__main__":
    app.run(host='127.0.0.1', port=80, debug=True)
