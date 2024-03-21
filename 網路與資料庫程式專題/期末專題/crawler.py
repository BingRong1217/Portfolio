import requests
import datetime

def crawl():
    url = "https://opendata.cwa.gov.tw/fileapi/v1/opendataapi/O-A0001-001?Authorization=CWA-5F2E9993-538C-4071-BAA5-5CCEB5102B9A&downloadType=WEB&format=JSON"
    data = requests.get(url)
    data_json = data.json()
    station = data_json['cwaopendata']['dataset']
    station = station['Station']

    for i in station:
        name = i['StationName']                                     # 測站地點

        if name == '中壢':
            temp = i['WeatherElement']['AirTemperature']            # 氣溫
            humd = i['WeatherElement']['RelativeHumidity']          # 相對濕度
            r24 = i['WeatherElement']['Now']['Precipitation']       # 累積雨量
            windDir = i['WeatherElement']['WindDirection']          # 風向
            windSpeed = i['WeatherElement']['WindSpeed']            # 風
            time = i['ObsTime']['DateTime']                         # 日期
            break

    if temp == 'X' or temp == '-99': temp = '25'
    if humd == 'X' or humd == '-99': humd = '60'
    if r24 == 'X' or r24 == 'T' or r24 == '-99' or r24 == '-98': r24 = '0'
    if windDir == 'X' or windDir == '-99' or windDir == '999': windDir = '0'
    if windSpeed == 'X' or windSpeed == '-99': windSpeed = '0'

    today = datetime.date.today()
    day_of_year = today.strftime("%j")
    time = day_of_year

    print(name, time, temp, humd, windSpeed, windDir, r24)
    return time, temp, humd, windSpeed, windDir, r24

def future():
    from datetime import datetime

    url = "https://opendata.cwa.gov.tw/fileapi/v1/opendataapi/F-D0047-005?Authorization=CWA-5F2E9993-538C-4071-BAA5-5CCEB5102B9A&downloadType=WEB&format=JSON"
    data = requests.get(url)
    data_json = data.json()
    location = data_json['cwaopendata']['dataset']['locations']
    location = location['location']

    for i in location:
        if i['locationName'] == '中壢區':
            elements = i['weatherElement']
            break

    PoP = 0
    for j in elements:
        arr = []
        if j['elementName'] == 'PoP6h':
            currentDay = datetime.now().day # 取出現在時間的日期 (day of month)
            for begPoP6h in range(0, 12):
                starttime = j['time'][begPoP6h]['startTime']    # 取出 6H 的開始時間
                # Convert the string to a datetime object
                dt = datetime.strptime(starttime, '%Y-%m-%dT%H:%M:%S%z')
                day = dt.day
                if currentDay != day:   # 表示找到明天的第一個6H
                    break
  
            endPoP6h = begPoP6h + 4

            for k in range(begPoP6h, endPoP6h):
                sub = []
                starttime = j['time'][k]['startTime']   
                endtime = j['time'][k]['endTime']        
                PoP6h = j['time'][k]['elementValue']['value']
                print(k, starttime, endtime, PoP6h, '%')
                starttime = starttime[:10] + ' ' + starttime[11:19]
                endtime = endtime[:10] + ' ' + endtime[11:19]
                sub.append(starttime + ' ~ ' + endtime)
                sub.append(PoP6h + '%')
                arr.append(sub)
                PoP += int(PoP6h)
            break

    if PoP > 0: tomorrowRain = True
    else:  tomorrowRain = False

    print('明天中壢會下雨嗎?', tomorrowRain)
    print(arr)
    return arr

if __name__ == '__main__':
    crawl()
    future()

