#!/usr/bin/env python
# -*- coding: utf-8 -*-

from random import randint, seed, uniform
import random

seed(0)
# Create Schemata:

def create_data (amount):
    print('create data...')
    insertData = []
    for x in range(0, amount):
        entryDict = dict()
        data = createChangedData(x)
        entryDict['BKPF'] = BKPFentry(data)
        bseg1, bseg2 = BSEGentry(data)
        entryDict['BSEG1'] = bseg1
        entryDict['BSEG2'] = bseg2
        entryDict['GLT0'] = data['HSL']
        acdoca1, acdoca2 = ACDOCAentry(data)
        
        entryDict['ACDOCA1'] = acdoca1
        entryDict['ACDOCA2'] = acdoca2
        insertData.append(entryDict)
    return insertData


def BKPFentry(data):
    return "800, 1000, %s, 2016, %s, %s, 'EUR', 'USD', 1.12, 'EUR'" % (data['BELNR'], str(data['BUDAT']), data['MONAT'])  

def BSEGentry(data):
    entry1 =  "800, 1000, %s, 2016, 2, 1000, 'S', %s, %s, '-', 1000, '-', '?', 893015, 1000, 'P-100', 1000, %s, 'ST', %s, 1010, 'MANF', %s, %s, 893015" % (data['BELNR'],data['DMBTR'],data['WRBRT'],data['MENGE'], data['AUFNR'],data['VBELN'], data['VBEL2'])
    entry2 =  "800, 1000, %s, 2016, 1, 1000, 'H', %s, %s, '-', 1000, '-', '?', 792000, 1000, 'P-100', 1000, %s, 'ST', %s, 1010, 'MANF', %s, %s, 792000" % (data['BELNR'],data['DMBTR'],data['WRBRT'],data['MENGE'], data['AUFNR'],data['VBELN'], data['VBEL2'])
    return entry1, entry2

def GLT0entry(data):
    entry1 = "800, 1, 'OL', 2016, 893015, 1000, 'S', 1, %s, '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', 0   , %s, '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', 0" % (data['HSL'], data['KSL1']) 
    entry2 = "800, 1, 'OL', 2016, 792000, 1000, 'H', 1, %s, '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', 3000, %s, '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', 0" % (data['HSL'], data['KSL1']) 
    
    return entry1, entry2

def ACDOCAentry(data):
    entry1 = "800, 'OL', 1000, 2016, %s, %s, 2016, %s, 'EUR', 'USD', 'ST', 893015,  '',  '', 1000, 1000,  '',  '', '', '', '', %s, %s, %s, 'S', '', '', %s, '', '', '', '', '', %s, '', '', '', '', ''" % (data['BELNR'], data['DOCLN'], data['VBELN'], data['DMBTR'], data['KSL'], data['MSL'], data['BUDAT'], data['KDAUF'] )
    entry2 = "800, 'OL', 1000, 2016, %s, %s, 2016, %s, 'EUR', 'USD', 'ST', 792000,  '',  '', 1000, 1000,  '',  '', '', '', '', %s, %s, %s, 'H', '', '', %s, '', '', '', '', '', %s, '', '', '', '', ''" % (data['BELNR'], data['DOCLN2'], data['VBELN'], data['DMBTR'], data['KSL'], data['MSL'], data['BUDAT'], data['KDAUF'] )
    return entry1, entry2

def createRandomFloat(lower_limit,upper_limit):
    return random.uniform(lower_limit, upper_limit)

def createRandomInt(lower_limit, upper_limit):
    return  randint(lower_limit, upper_limit)

def createChangedData(x):
    month = createRandomInt(1,12)
    dmbtr = createRandomFloat(1000,4000)
    data = dict()
    data['BELNR'] = 4900000000 + x
    data['BUDAT'] = str(createRandomInt(1,28)) + "-" + str(month) + "-2016"
    data['MONAT'] = str(month)
    data['DMBTR'] = dmbtr
    data['WRBRT'] = dmbtr
    data['AUFNR'] = createRandomInt(4000,10000)
    data['MENGE'] = createRandomInt(1,20)
    data['VBELN'] = createRandomInt(80000000,80090000)
    data['VBEL2'] = createRandomInt(10000,20000)
    data['DOCLN'] = 2 * x
    data['DOCLN2'] = 2 * x + 1
    data['HSL'] = createRandomInt(1,1000) + dmbtr
    data['KSL1'] = createRandomInt(1,1000) + (dmbtr * 1.2)
    data['KSL'] = createRandomInt(1,100000)
    data['MSL'] = createRandomInt(1,100000)
    data['KDAUF'] = data['VBEL2']
    return data



