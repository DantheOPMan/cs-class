import xml.dom.minidom
import sys
import mysql.connector

doc = xml.dom.minidom.parse(sys.argv[1])
stateName = (sys.argv[1])[-8:-6]
cityName = ""
date = ""
dayOrNight = ""
temp = ""

div_nodes = doc.getElementsByTagName('div')
for div in div_nodes:
    if div.getAttribute('id') == 'current-conditions':
        for h2_node in div.getElementsByTagName('h2'):
            if h2_node.getAttribute('class') == 'panel-title':
                cityName = h2_node.firstChild.nodeValue.strip()
                if ',' in cityName:
                    cityName = cityName[:cityName.find(',')]
                else:
                    cityName = cityName[:cityName.find(' ')]

for div in div_nodes:
    if div.getAttribute('id') == 'current_conditions_detail':
        for td in div.getElementsByTagName('td'):
            if td.firstChild.nodeValue == None:
                continue
            if "am" in td.firstChild.nodeValue.lower() or "pm" in td.firstChild.nodeValue.lower():
                date = td.firstChild.nodeValue.strip()
                time = date[date.find(':')-2:date.find(':')+3].strip()
                end = date[-6:-3].lower().strip()
                if(end == "am"):
                    if int(time[:time.find(':')]) < 6 or int(time[:time.find(':')]) == 12:
                        dayOrNight = "Night"
                    else:
                        dayOrNight = "Day"
                if(end == "pm"):
                    if int(time[:time.find(':')]) >= 6 or int(time[:time.find(':')]) != 12:
                        dayOrNight = "Night"
                    else:
                        dayOrNight = "Day"
                date = date[0:6]

for div in div_nodes:
    for p_node in div.getElementsByTagName('p'):
        if p_node.getAttribute('class') == 'myforecast-current-lrg':
            temp = p_node.firstChild.nodeValue.strip()

shortDescriptionPeriodName = []
shortDescription = []
shortDescriptionTemp = []
for div in div_nodes:
    if div.getAttribute('class') == 'tombstone-container':
        for p_node in div.getElementsByTagName('p'):
            if p_node.getAttribute('class') == 'period-name':
                input = ""
                for text in p_node.childNodes:
                    if text.nodeValue != None:
                        input  += text.nodeValue.strip() + " "
                shortDescriptionPeriodName.append(input.strip())
            if p_node.getAttribute('class') == 'short-desc':
                input = ""
                for text in p_node.childNodes:
                    if text.nodeValue != None:
                        input  += text.nodeValue.strip() + " "
                shortDescription.append(input.strip())
            if p_node.getAttribute('class') == 'temp temp-high' or p_node.getAttribute('class') == 'temp temp-low':
                input = ""
                for text in p_node.childNodes:
                    if text.nodeValue != None:
                        input  += text.nodeValue.strip() + " "
                shortDescriptionTemp.append(input.strip())

longDescriptionPeriodName = []
longDescription = []
for div in div_nodes:
    if div.getAttribute('class') == 'row row-odd row-forecast' or div.getAttribute('class') == 'row row-even row-forecast':
        for dnode in div.getElementsByTagName('div'):
            if dnode.getAttribute('class') == 'col-sm-2 forecast-label':
                longDescriptionPeriodName.append(dnode.getElementsByTagName('b')[0].firstChild.nodeValue.strip())
            if dnode.getAttribute('class') == 'col-sm-10 forecast-text':
                input = ""
                for text in dnode.childNodes:
                    if text.nodeValue != None:
                        input  += text.nodeValue.strip() + " "
                longDescription.append(input.strip())
            

#print(cityName, ",", stateName, ",", date, ",", dayOrNight, ",", temp)
#print(shortDescriptionPeriodName)
#print(shortDescriptionImage)
#print(shortDescription)
#print(shortDescriptionTemp)
#print(longDescriptionPeriodName)
#print(longDescription)

def createWeatherTable(cursor):
    cursor.execute("SHOW TABLES")
    tables = cursor.fetchall()
    table_exists = False
    for table in tables:
      if table[0] == "weather":
        table_exists = True
        break
    if not table_exists:
      cursor.execute("CREATE TABLE weather (cityName VARCHAR(255) PRIMARY KEY, stateName VARCHAR(255), date VARCHAR(255), dayOrNight VARCHAR(255), temp VARCHAR(255), shortDescriptionPeriodName TEXT, shortDescription TEXT, shortDescriptionTemp TEXT, longDescriptionPeriodName TEXT, longDescription TEXT)")

def clearRepeatState(cityName, cursor):
    sql_check = "SELECT cityName FROM weather WHERE cityName = %s"
    cursor.execute(sql_check, (cityName,))
    result = cursor.fetchone()
    
    if result:
        sql_delete = "DELETE FROM weather WHERE cityName = %s"
        cursor.execute(sql_delete, (cityName,))

def insert(cursor):
    sql_insert = "INSERT INTO weather (cityName, stateName, date, dayOrNight, temp, shortDescriptionPeriodName, shortDescription, shortDescriptionTemp, longDescriptionPeriodName, longDescription) VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s)"
    values = (cityName, stateName, date, dayOrNight, temp, str(shortDescriptionPeriodName), str(shortDescription), str(shortDescriptionTemp), str(longDescriptionPeriodName), str(longDescription))
    cursor.execute(sql_insert, values)

try:
    cnx = mysql.connector.connect(host='localhost', user='user', password='Password', database='weather')
    cursor = cnx.cursor()
    createWeatherTable(cursor)
    cnx.commit()

    clearRepeatState(cityName, cursor)
    cnx.commit()

    insert(cursor)
    cnx.commit()

    cursor.close()

except mysql.connector.Error as err:
    print(err)
finally:
    try:
        cnx
    except NameError:
        pass
    else:
        cnx.close()
