'''
OBJECTIVE: Access gmail account and auto delete promotional emails daily
*TODO:*
- [x] a̶c̶c̶e̶s̶s̶ g̶m̶a̶i̶l̶ a̶c̶c̶o̶u̶n̶t̶
- [x] a̶c̶c̶e̶s̶s̶ p̶r̶o̶m̶o̶t̶i̶o̶n̶a̶l̶ e̶m̶a̶i̶l̶s̶
- [x] d̶e̶l̶e̶t̶e̶ t̶o̶p̶ p̶r̶o̶m̶o̶t̶i̶o̶n̶a̶l̶ e̶m̶a̶i̶l̶
- [x] set up a cron job to run daily
'''

import imaplib
import yaml

# account credentials
username = yaml.safe_load(open('secret.yaml'))['username']
password = yaml.safe_load(open('secret.yaml'))['password']

# email provider's IMAP server
imap_server = 'imap.gmail.com'

# create an IMAP4 class with SSL 
imap = imaplib.IMAP4_SSL(imap_server)

# authenticate
imap.login(username, password)

#view all mailboxes
# print(imap.list())

# select mailbox to access
status, messages = imap.select("[Imap]/Promotions")
# status, messages = imap.select("[Gmail]/Spam")

# total number of emails
messages = int(messages[0])
before = messages # beginning number of emails
print("before: " + str(before))

# delete all emails
for i in range(messages, 0, -1):
    imap.store(str(i), "+FLAGS", "\\Deleted")
    imap.expunge()
    print("deleted: " + str(i))

print("after: " + str(messages))

# close the connection and logout
imap.close()
imap.logout()