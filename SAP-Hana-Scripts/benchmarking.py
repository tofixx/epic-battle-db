#!/usr/bin/env python
# -*- coding: utf-8 -*-

from connector import HanaConnector 
import createInsertData as cid
import time
from random import randint, seed

seed(0)

conn = HanaConnector()

def insert(table_name, values):
    query = "INSERT INTO %s VALUES(%s)" % (table_name, values)
    conn.execute(query)

# TODO needs to be defined
def update(table_name, columns, values, id):
    query = "UPDATE %s SET %s = %s + '%s', %s = %s + '%s' where 'RACCT' = '%s'" % (table_name, columns[0], columns[0], values[0], columns[1], columns[1], values[1], id)
    conn.execute(query)  

def benchmark(iterations, fun, *args):
    start = time.time()
    for x in range(0, iterations):
        fun( *args )
    end = time.time()
    total_time = end - start
    iteration_time= total_time / iterations
    print ("Total time %.2fs, %.2fs average per iteration" % (total_time, iteration_time))

def benchmark_old_schema(iterations, data):
    start = time.time()
    for x in range(0, iterations):
        #print(x,"iteration", data[x]['BKPF'])
        insert(schema_old + ".BKPF_R", data[x]['BKPF'])
        insert(schema_old + ".BSEG_R", data[x]['BSEG1'])
        insert(schema_old + ".BSEG_R", data[x]['BSEG2'])
        hsl = float(data[x]['GLT0'])
        ksl = hsl * 1.12

        update(schema_old + ".GLT0_R", ["HSL01", "KSL01"],[hsl, ksl], 893015)
        update(schema_old + ".GLT0_R", ["HSL01", "KSL01"],[hsl, ksl], 792000)

    end = time.time()
    total_time = end - start
    iteration_time= total_time / iterations
    print ("Total time %.2fs, %.5fs average per iteration" % (total_time, iteration_time))
    return iteration_time

def benchmark_new_schema(iterations, data):
    start = time.time()
    for x in range(0, iterations):
        #print(x,"iteration", data[x]['BKPF'])
        insert(schema_new + ".ACDOCA_R", data[x]['ACDOCA1'])
        insert(schema_new + ".ACDOCA_R", data[x]['ACDOCA2'])
    end = time.time()
    total_time = end - start
    iteration_time= total_time / iterations
    print ("Total time %.2fs, %.5fs average per iteration" % (total_time, iteration_time))  
    return iteration_time         



schema_old = "TEAM1_OLD"
schema_new = "TEAM1_NEW"


def truncateTables():
    conn.truncateTable('TEAM1_OLD.', 'BKPF_R')
    conn.truncateTable('TEAM1_OLD.', 'BSEG_R')
    conn.truncateTable('TEAM1_OLD.', 'GLT0_R')
    conn.truncateTable('TEAM1_NEW.', 'ACDOCA_R')

def initialInsert():
    # Initial Insert GLT0
    data = dict()
    data['HSL'] = 1456
    data['KSL1'] = data['HSL'] * 1456
    glt01, glt02 = cid.GLT0entry(data)
    insert(schema_old + ".GLT0_R", glt01)
    insert(schema_old + ".GLT0_R", glt02)

def benchmark(iterations):
    data = cid.create_data(iterations)
    print('run old benchmark...')
    old_time = benchmark_old_schema(iterations, data)
    print('run new benchmark...')
    new_time = benchmark_new_schema(iterations, data)
    print("new schema improvement %.5f percent" % (old_time/new_time*100))


truncateTables()
initialInsert()
benchmark(10)
conn.close()
exit()
