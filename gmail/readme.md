# This is a python script that deletes promotional gmails daily at 9PM EST using a cron job. It uses the 'imap' protocol to connect to the Gmail server.

## How to use:
1. Create an app password for your gmail account in order for your IDE to have access to Gmail.
    - [Instructions Here](https://support.google.com/accounts/answer/185833?hl=en)
    - I chose to store my username and password in my secret.yaml file (.gitignore). You can choose to do the same or just hardcode.
2. Expose the promotional emails to IMAP. 
    - [Follow This](https://superuser.com/questions/719677/how-to-use-gmail-tabs-with-imap)
3. Run the script using python3.6 or higher. I used python3.11.5

## Status: 
- The script needs me to make an imap of promotions but this creates a copy and does not delete the original. I need to find a way to delete the original.
- Have not set up scheduler as I want to test the script first.