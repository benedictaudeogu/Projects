# Delete gmails using IMAP protocol

Creating an app password for your gmail account in order for your IDE to have access to Gmail:
    - [Generate Password](https://support.google.com/accounts/answer/185833?hl=en)
        - I chose to store my username and password in my secret.yaml file (.gitignore)

## Status: 
- Since there isn't one already, I created an imap of promotions but this creates a copy and does not delete the original. Dont have fix for this yet.
    - Ended up using gmail api
- Will work with any listed email types otherwise 
    - This includes any IMAP labels google has predefined
    ```
    print(imap.list())
    ```
    
## .gitignore contents:
1. `secret.yaml` --> gmail username and app password - IMAP
2. `credentials.json` --> google api json credentials
3. `token.pickle` --> google api token
4. `cron.xml` --> potential scheduler with my file paths 
