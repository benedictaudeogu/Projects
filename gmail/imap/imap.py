"""STATUS: CURRENTLY NOT DELETING PROMOTIONAL EMAILS, ONLY IMAP COPY OF PROMOTIONAL EMAILS DELETED - THE EMAILS ARE STILL IN THE INBOX"""

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
# status, messages = imap.select("[Imap]/Promotions")
status, messages = imap.select("[Gmail]/Spam")

# total number of emails
messages = int(messages[0])

# delete all emails
for i in range(messages, 0, -1):
    imap.store(str(i), "+FLAGS", "\\Deleted")
    imap.expunge()
    print("deleted: " + str(i))

# close the connection and logout
imap.close()
imap.logout()
