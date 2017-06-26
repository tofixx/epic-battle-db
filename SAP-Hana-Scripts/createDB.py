#!/usr/bin/env python
# -*- coding: utf-8 -*-

import connector
from random import randint, seed

seed(0)
# Create Schemata:

def create_table (table_name, table_type, columns, primary_keys):
    column_query = " Integer, ".join(columns) + " Integer, "
    primary_key_query = ", ".join(primary_keys)
    query = "create %s table %s (%s PRIMARY KEY(%s));" % (table_type, table_name, column_query, primary_key_query)
    connector.execute(query)

def dummy_insert(table_name, columns):
    values = ",".join([ str(randint(0, 100)) for i in range(len(columns))])
    query = "INSERT INTO %s VALUES(%s)" % (table_name, values)
    connector.execute(query)
    

bkpf_columns = [ "MANDT","BUKRS","BELNR","GJAHR","BLART","BLDAT","BUDAT","MONAT","CPUDT","CPUTM","AEDAT","UPDDT","WWERT","USNAM","TCODE","BVORG","XBLNR","DBBLG","STBLG","STJAH","BKTXT","WAERS","KURSF","KZWRS","KZKRS","BSTAT","XNETB","FRATH","XRUEB","GLVOR","GRPID","DOKID","ARCID","IBLAR","AWTYP","AWKEY","FIKRS","HWAER","HWAE2","HWAE3","KURS2","KURS3","BASW2","BASW3","UMRD2","UMRD3","XSTOV","STODT","XMWST","CURT2","CURT3","KUTY2","KUTY3","XSNET","AUSBK","XUSVR","DUEFL","AWSYS","TXKRS","LOTKZ","XWVOF","STGRD","PPNAM","BRNCH","NUMPG","ADISC","XREF1_HD","XREF2_HD","XREVERSAL","REINDAT","RLDNR","LDGRP","PROPMANO","XBLNR_ALT","VATDATE","PSOTY","PSOAK","PSOKS","PSOSG","PSOFN","INTFORM","INTDATE","PSOBT","PSOZL","PSODT","PSOTM","FM_UMART","CCINS","CCNUM","SSBLK","BATCH","SNAME","SAMPLED","EXCLUDE_FLAG","BLIND","OFFSET_STATUS","OFFSET_REFER_DAT","PENRC","KNUMV"]
bkpf_primary_keys = ["MANDT","BUKRS","BELNR","GJAHR"]

bseg_columns = [ "MANDT","BUKRS","BELNR","GJAHR","BUZEI","BUZID","AUGDT","AUGCP","AUGBL","BSCHL","KOART","UMSKZ","UMSKS","ZUMSK","SHKZG","GSBER","PARGB","MWSKZ","QSSKZ","DMBTR","WRBTR","KZBTR","PSWBT","PSWSL","TXBHW","TXBFW","MWSTS","WMWST","HWBAS","FWBAS","HWZUZ","FWZUZ","SHZUZ","STEKZ","MWART","TXGRP","KTOSL","QSSHB","KURSR","GBETR","BDIFF","BDIF2","VALUT","ZUONR","SGTXT","ZINKZ","VBUND","BEWAR","ALTKT","VORGN","FDLEV","FDGRP","FDWBT","FDTAG","FKONT","KOKRS","KOSTL","PROJN","AUFNR","VBELN","VBEL2","POSN2","ETEN2","ANLN1","ANLN2","ANBWA","BZDAT","PERNR","XUMSW","XHRES","XKRES","XOPVW","XCPDD","XSKST","XSAUF","XSPRO","XSERG","XFAKT","XUMAN","XANET","XSKRL","XINVE","XPANZ","XAUTO","XNCOP","XZAHL","SAKNR","HKONT","KUNNR","LIFNR","FILKD","XBILK","GVTYP","HZUON","ZFBDT","ZTERM","ZBD1T","ZBD2T","ZBD3T","ZBD1P","ZBD2P","SKFBT","SKNTO","WSKTO","ZLSCH","ZLSPR","ZBFIX","HBKID","BVTYP","NEBTR","MWSK1","DMBT1","WRBT1","MWSK2","DMBT2","WRBT2","MWSK3","DMBT3","WRBT3","REBZG","REBZJ","REBZZ","REBZT","ZOLLT","ZOLLD","LZBKZ","LANDL","DIEKZ","SAMNR","ABPER","VRSKZ","VRSDT","DISBN","DISBJ","DISBZ","WVERW","ANFBN","ANFBJ","ANFBU","ANFAE","BLNBT","BLNKZ","BLNPZ","MSCHL","MANSP","MADAT","MANST","MABER","ESRNR","ESRRE","ESRPZ","KLIBT","QSZNR","QBSHB","QSFBT","NAVHW","NAVFW","MATNR","WERKS","MENGE","MEINS","ERFMG","ERFME","BPMNG","BPRME","EBELN","EBELP","ZEKKN","ELIKZ","VPRSV","PEINH","BWKEY","BWTAR","BUSTW","REWRT","REWWR","BONFB","BUALT","PSALT","NPREI","TBTKZ","SPGRP","SPGRM","SPGRT","SPGRG","SPGRV","SPGRQ","STCEG","EGBLD","EGLLD","RSTGR","RYACQ","RPACQ","RDIFF","RDIF2","PRCTR","XHKOM","VNAME","RECID","EGRUP","VPTNR","VERTT","VERTN","VBEWA","DEPOT","TXJCD","IMKEY","DABRZ","POPTS","FIPOS","KSTRG","NPLNR","AUFPL","APLZL","PROJK","PAOBJNR","PASUBNR","SPGRS","SPGRC","BTYPE","ETYPE","XEGDR","LNRAN","HRKFT","DMBE2","DMBE3","DMB21","DMB22","DMB23","DMB31","DMB32","DMB33","MWST2","MWST3","NAVH2","NAVH3","SKNT2","SKNT3","BDIF3","RDIF3","HWMET","GLUPM","XRAGL","UZAWE","LOKKT","FISTL","GEBER","STBUK","TXBH2","TXBH3","PPRCT","XREF1","XREF2","KBLNR","KBLPOS","STTAX","FKBER","OBZEI","XNEGP","RFZEI","CCBTC","KKBER","EMPFB","XREF3","DTWS1","DTWS2","DTWS3","DTWS4","GRICD","GRIRG","GITYP","XPYPR","KIDNO","ABSBT","IDXSP","LINFV","KONTT","KONTL","TXDAT","AGZEI","PYCUR","PYAMT","BUPLA","SECCO","LSTAR","CESSION_KZ","PRZNR","PPDIFF","PPDIF2","PPDIF3","PENLC1","PENLC2","PENLC3","PENFC","PENDAYS","PENRC","GRANT_NBR","SCTAX","FKBER_LONG","GMVKZ","SRTYPE","INTRENO","MEASURE","AUGGJ","PPA_EX_IND","ZZSPREG","ZZBUSPARTN","ZZCHAN","ZZPRODUCT","ZZLOCA","ZZLOB","ZZUSERFLD1","ZZUSERFLD2","ZZUSERFLD3","ZZSTATE","ZZREGION","DOCLN","SEGMENT","PSEGMENT","PFKBER","HKTID","KSTAR","XLGCLR","PEROP_BEG","PEROP_END","FASTPAY","PRODPER"]
bseg_primary_keys = [ "MANDT","BUKRS","BELNR","GJAHR","BUZEI"]

schema_old = "TEAM1_OLD"
schema_new = "TEAM1_NEW"

query_schema_1 = """ CREATE SCHEMA TEAM1_OLD """ 
query_schema_2 = """ CREATE SCHEMA TEAM1_NEW """

connector.execute(query_schema_1)
connector.execute(query_schema_2)
 
# Creates the desired databases
create_table(schema_old + ".BKPF", "ROW", bkpf_columns, bkpf_primary_keys)
create_table(schema_old + ".BSEG", "ROW", bseg_columns, bseg_primary_keys)
create_table(schema_new + ".BKPF", "COLUMN", bkpf_columns, bkpf_primary_keys)
create_table(schema_new + ".BSEG", "COLUMN", bseg_columns, bseg_primary_keys)

dummy_insert(schema_old + ".BKPF", bkpf_columns)
dummy_insert(schema_old + ".BSEG", bseg_columns)
dummy_insert(schema_new + ".BKPF", bkpf_columns)
dummy_insert(schema_new + ".BSEG", bseg_columns)

connector.dropTable('TEAM1_OLD.', 'BKPF')
connector.dropTable('TEAM1_OLD.', 'BSEG')
connector.dropTable('TEAM1_NEW.', 'BKPF')
connector.dropTable('TEAM1_NEW.', 'BSEG')

connector.dropSchema(schema_old)
connector.dropSchema(schema_new)