# Delete gmails using IMAP protocol

## How to use:
1. Create an app password for your gmail account in order for your IDE to have access to Gmail.
    - [Generate Password](https://support.google.com/accounts/answer/185833?hl=en)
        - I chose to store my username and password in my secret.yaml file (.gitignore). You can choose to do the same or just hardcode.
2. Expose the promotional emails to IMAP. 
    - [Expose to IMAP](https://superuser.com/questions/719677/how-to-use-gmail-tabs-with-imap)
        - Any email with IMAP access can be deleted by this script.

## Status: 
- Since there isn't one already, I created an imap of promotions but this creates a copy and does not delete the original. I need to find a way to delete the original.
    - Used google api instead to resolve this issue
- Will work with any listed email types otherwise 
    ```
    print(imap.list())
    ```


