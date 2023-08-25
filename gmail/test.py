# objective access gmail account and auto delete promotional emails daily
from distutils.util import rfc822_escape
import poplib
from io import StringIO
import yaml
import logging

username = yaml.safe_load(open('secret.yaml'))['username']
password = yaml.safe_load(open('secret.yaml'))['password']

# configure
server = poplib.POP3_SSL('pop.gmail.com', 995)
server.user(username)
server.pass_(password)

print("configured!")

# list items on server
logging.debug('listing emails')
resp, items, octets = server.list()

# download the first message in the list
# id, size = string.split(items[0])
# id, size = items[0].split()
id, size = int(items[0].split()[0]), int(items[0].split()[1])
resp, text, octets = server.retr(id)

# convert list to Message object
text = b"\n".join(text)
# file = StringIO(text)
file = StringIO(text.decode('utf-8'))
message = rfc822_escape.Message(file)

# output message
print(message['From']),
print(message['Subject']),
print(message['Date']),
#print(message.fp.read())  