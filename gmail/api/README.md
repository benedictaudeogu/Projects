# Delete promotional emails using Gmail API and Cron job
1. Dependencies
    ```Python
    pip3 install google
    ```
    ```Python
    pip3 install --upgrade google-api-python-client google-auth-httplib2 google-auth-oauthlib
    ```
2. Access the Gmail API from IDE using OAuth 2.0 token
    - [Enable API](https://support.google.com/googleapi/answer/6158841?hl=en)
    - [Get Token](https://support.google.com/googleapi/answer/6158849?hl=en&ref_topic=7013279&sjid=15952990207606155705-NA)
        - **'New Credentials'** === **'Create Credentials'**
3. Download JSON and rename to 'credentials.json', store in project directory
4. Set up a job using crontab
         ```Python
         00 19 * * * cd <path to script> && usr/local/bin/python3 api.py
         ```

### Error Message Handling:
- Receive a push notification on Telegram if the script fails to run.
<img src=notification.jpeg>


