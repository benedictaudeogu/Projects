import os
import time
import pickle
from schedule import repeat, every
import schedule

# Gmail API utils
from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request

# Request all access (permission to read/send/receive emails, manage the inbox, and more)
access = ['https://mail.google.com/']

def authenticate():
    creds = None
    # token.pickle stores the user's access and refresh tokens, created automatically when the authorization flow completes for the first time
    if os.path.exists("token.pickle"):
        with open("token.pickle", "rb") as token:
            creds = pickle.load(token)
    # if there are no valid credentials availablle, let the user log in
    if not creds or not creds.valid:
        if creds and creds.expired and creds.refresh_token:
            creds.refresh(Request())
        else:
            flow = InstalledAppFlow.from_client_secrets_file('credentials.json', access)
            creds = flow.run_local_server(port=0)
        # save the credentials for the next run
        with open("token.pickle", "wb") as token:
            pickle.dump(creds, token)
    return build('gmail', 'v1', credentials=creds)


# get the Gmail API service
service = authenticate()

# gather all email messages
def find(service, query):
    result = service.users().messages().list(userId='me',q=query).execute()
    messages = []
    if 'messages' in result:
        messages.extend(result['messages'])
    while 'nextPageToken' in result:
        page_token = result['nextPageToken']
        result = service.users().messages().list(userId='me',q=query, pageToken=page_token).execute()
        if 'messages' in result:
            messages.extend(result['messages'])
    return messages

# number of promotional emails
# print(len(find(service, 'in:promotions')))

# delete promotional emails
def delete(service, query):
    messages_to_delete = find(service, query)
    # to delete a single message with the delete API: service.users().messages().delete(userId='me', id=msg['id'])
    return service.users().messages().batchDelete(
      userId='me',
      body={
          'ids': [ msg['id'] for msg in messages_to_delete]
      }
    ).execute()

delete(service, 'in:promotions')

# automate
# if __name__ == '__main__':
#     schedule.every().day.at("09:00").do(authenticate)
#     service = authenticate()
#     schedule.every().day.at("09:01").do(find, service, 'in:promotions')
#     schedule.every().day.at("09:02").do(delete, service, 'in:promotions')
#     while True:
#         schedule.run_pending()
#         time.sleep(1)
