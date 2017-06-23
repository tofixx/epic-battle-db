#!/usr/bin/env python
# -*- coding: utf-8 -*-

import connector

# Create Schemata:

schema_old = "TEAM1_OLD"
schema_new = "TEAM1_NEW"

query_schema_1 = """ CREATE SCHEMA TEAM1_OLD """ 
query_schema_2 = """ CREATE SCHEMA TEAM1_NEW """

connector.execute(query_schema_1)
connector.execute(query_schema_2)
 

# Creates the desired databases
create_database = """ 
    CREATE COLUMN TABLE TEAM1_NEW.TABLE1 (
        ID INTEGER,
        NAME VARCHAR(10),
        DESCRIPTION VARCHAR(100),
        PRIMARY KEY (ID) ); 
     """

connector.execute(create_database)   

connector.dropTable('TEAM1_NEW.', 'TABLE1')

connector.dropSchema(schema_old)
connector.dropSchema(schema_new)