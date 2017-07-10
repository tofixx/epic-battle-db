#!/usr/bin/env python
# -*- coding: utf-8 -*-
import pyhdb
import config

class HanaConnector:

    def connect(self):
        try:
            connection = pyhdb.connect(
                host=config.login["host"],
                port=config.login["port"],
                user=config.login["user"],
                password=config.login["password"]
            )
            print('connected to hana...')
            return connection
        except Exception as e:
            print('Connection Failed!\nError Code is %s;\nError Content is %s;' % (e.args[0],e.args[1]))

    def __init__(self):
        print('create connection...')
        self.connection = self.connect()

    def close(self):
        self.connection.close()
        print('connection closed...')

    
    def execute(self,query):
        cursor = self.connection.cursor()
        print(query)
        cursor.execute(query)
        cursor.close()

    # Returns a cursor
    def executeFetchCursor(self,query):
        cursor = self.connection.cursor()
        cursor.execute(query)
        return cursor

    def truncateTable(self,schema,table_name):
        sql = "TRUNCATE TABLE " + schema + table_name
        self.execute(sql)

    def dropTable(self,schema, table_name):
        sql = "DROP TABLE " + schema + table_name
        self.execute(sql)

    def dropSchema(self,schema_name):
        sql = "DROP SCHEMA " + schema_name + " CASCADE"
        self.execute(sql)    

    # cursor = connection.cursor()
    # cursor.execute("SELECT 'Hello Python World' FROM DUMMY")
    # cursor.fetchone()
