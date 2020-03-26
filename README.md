# CSV-to-XML
It is a convertor program that converts .csv format file to .xml format file with several seperator and end line character options.<br>

● CSV2XML tool takes the following command line arguments: <br>
○ -separator <br>
defines separator between each datum (1=comma, 2=tab, 3=semicolon) <br>
○ -opsys <br>
defines the end of line character format (1=windows, 2=linux, 3=macos) <br>
○ -h <br>
print information to screen about how other arguments can be used. <br>
<br>
● Usage of CSV2XML file as follows: <br>
CSV2XML <inputfile> <outputfile> [-separator <P1>][-opsys <P2>][-h] <br>
  <br>
● The sample command line usage converting from CSV to XML as follows: <br> 
./CVS2XML Contacts.csv Contacts.xml -separator 1 -opsys 1 <br> 
<br>
CVS2XML will produce an XML file in basic form. Please check the example in the repository.

