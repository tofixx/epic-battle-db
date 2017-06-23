#!/usr/bin/env python
# -*- coding: utf-8 -*-
import pyhdb
import config



def connect():
    try:
        connection = pyhdb.connect(
            host=config.login["host"],
            port=config.login["port"],
            user=config.login["user"],
            password=config.login["password"]
        )
        return connection
    except Exception as e:
        print('Connection Failed!\nError Code is %s;\nError Content is %s;' % (e.args[0],e.args[1]))

####
def execute(query):
    connection = connect()
    cursor = connection.cursor()
    cursor.execute(query)
    cursor.close


# Returns a cursor
def executeFetchCursor(query):
    result_list = []        
    connection = connect()
    cursor = connection.cursor()
    cursor.execute(query)
    return cursor

def dropTable(schema, table_name):
    sql = "DROP TABLE " + schema + table_name
    execute(sql)

def dropSchema(schema_name):
    sql = "DROP SCHEMA " + schema_name + " CASCADE"
    execute(sql)    


# cursor = connection.cursor()
# cursor.execute("SELECT 'Hello Python World' FROM DUMMY")
# cursor.fetchone()
