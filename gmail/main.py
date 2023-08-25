'''
OBJECTIVE: Access gmail account and auto delete promotional emails daily

*TODO:*
- [x] access gmail account
- [x] access promotional emails
- [x] set up a cron job to run daily
- [x] delete promotional emails

'''
import poplib
from io import StringIO
import yaml
import email
# import schedule

username = yaml.safe_load(open('secret.yaml'))['username']
password = yaml.safe_load(open('secret.yaml'))['password']

# configure
server = poplib.POP3_SSL('pop.gmail.com', 995)
server.user(username)
server.pass_(password)
print("check 1")

# list items on server
resp, items, octets = server.list()
print("check 2")

# download the first message in the list
# id, size = int(items[0].split()[0]), int(items[0].split()[1])
# resp, text, octets = server.retr(id)

#download the latest message
id, size = int(items[-1].split()[0]), int(items[-1].split()[1])
resp, text, octets = server.retr(id)

#download based on date
# for i in range(1, len(items)):
#     id, size = int(items[i].split()[0]), int(items[i].split()[1])
#     resp, text, octets = server.retr(id)
#     message = email.message_from_string(text)
#     date = message['date']
#     if date == 'Fri, 25 Aug 2023 15:00:00 +0000':
#         print("found!")
#         break

# convert list to Message object
text = b"\n".join(text)
file = StringIO(text.decode('utf-8'))

message = email.message_from_file(file)

#print message from a specific date
print(message['date'])


