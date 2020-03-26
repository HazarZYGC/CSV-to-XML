# CSV-to-XML
It is a convertor program that converts .csv format file to .xml format file with several seperator and end line character options.

● CSV2XML tool takes the following command line arguments:
○ -separator
defines separator between each datum (1=comma, 2=tab, 3=semicolon)
○ -opsys
defines the end of line character format (1=windows, 2=linux, 3=macos)
○ -h
print information to screen about how other arguments can be used.

● Usage of CSV2XML file as follows:
CSV2XML <inputfile> <outputfile> [-separator <P1>][-opsys <P2>][-h]
  
● The sample command line usage converting from CSV to XML as follows:
./CVS2XML Contacts.csv Contacts.xml -separator 1 -opsys 1

CVS2XML will produce an XML file looks like the following:
<contacts>
  <row id=”1”>
    <first_name>James</first_name>
    <last_name>Butt</last_name>
    <email>jbutt@gmail.com</email>
    <phone_number>504-845-1427</phone_number>
    <address/>
  </row>
  ...
</contacts>
