#!/usr/bin/python
                                                                                                                        
import sys
import os
import re


if sys.argv[1] == "-d":
   make_obj = 1
else:
   make_obj = 0

ofile = sys.stdout

if make_obj == 0:
   iname = sys.argv[1]
else:
   iname = sys.argv[2]

iname = os.path.abspath(iname)
ifile = open(iname)
lines = ifile.readlines()
ifile.close()

decl_re = re.compile('@[a-zA-Z_]+@')
deff_re = re.compile('^[a-zA-Z0-9_]*')
vale_re = re.compile('[ ]*[xa-f0-9]+[ ]*')

def die (msg):
   print ("ERROR: %s" % msg)
   sys.exit(1)

print ("/* This file is automatically generated from the dwf_spec.txt *")
print (" * file.  Any changes made to this file, will we overwritten. */\n")

if make_obj == 1:
   print ("#include \"dwf_spec.h\"\n\n")

else:
   print ("#ifndef _DWF_SPEC_H_")
   print ("#define _DWF_SPEC_H_\n")
   print ("struct StringLUT {")
   print ("   unsigned int id;")
   print ("   const char* name;")
   print ("};\n")

cur = ""
reallines = []
for L in lines:
   L = L.strip()

   # Skip empty lines
   if len(L) == 0:
      continue

   reallines.append(L)

numlines = len(reallines)

str = None

for L in reallines:
   # Declare enumerations
   m = decl_re.match(L)
   if m != None:
      if str:
         if make_obj == 1 and cur != "":
            print (str+",")
         else:
            print (str)
         str = None
      if make_obj == 1:
         if cur != "":
            print ("  {  %-36s %-37s  }\n};\n" % ("0,","0"))
         cur = m.group()
         cur = cur[1:-1]
         if cur != "":
            print ("StringLUT globl_%s_lut[]  = {" % cur)
         continue

      if cur != "":
         print ("};\n")

      cur = m.group()
      cur = cur[1:-1]
      print ("extern StringLUT globl_%s_lut[];\n" % cur)
      print ("enum %s {" % cur)
      continue

   if str:
      print (str+",")

   # Hereafter, must be define
   if cur == "":
      die("no class")

   m = deff_re.match(L)
   if m == None:
      die("no define")
   nm = m.group()

   vl = L[m.end()+1:]
   vl = vl.strip()

   if make_obj == 1:
      str = "  {  %-36s \"%-36s  }" % (nm+',',nm+"\"")
   else:
      str = "   %-43s = %s" % (nm,vl)

if str:
   if make_obj == 1:
       print (str+",")
   else:
       print (str)

if make_obj == 1:
   print ("  {  %-36s %-37s  }" % ("0,","0"))

if cur != "":
   print ("};\n")

if make_obj == 0:
   print ("\n#endif")
