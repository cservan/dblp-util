import urllib.request
import subprocess

database_url   = 'http://dblp.uni-trier.de/xml/dblp.xml.gz'
xml_file_name  = 'dblp.xml'
gz_file_name   = xml_file_name + '.gz'

urllib.request.urlretrieve(database_url, gz_file_name)
subprocess.call(['gzip', '-d', gz_file_name])
subprocess.call(['rm', gz_file_name])
