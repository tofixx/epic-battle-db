#!/usr/bin/env python
# -*- coding: utf-8 -*-
import pyhdb
import config

# Creates the desired databases

try:
	connection = pyhdb.connect(
		host=config.login["host"],
		port=config.login["port"],
		user=config.login["user"],
		password=config.login["password"]
	)
#return connection
except Exception as e:
	print('Connection Failed!\nError Code is %s;\nError Content is %s;' % (e.args[0],e.args[1]))	

# cursor = connection.cursor()
# cursor.execute("SELECT 'Hello Python World' FROM DUMMY")
# cursor.fetchone()

# connection.close()