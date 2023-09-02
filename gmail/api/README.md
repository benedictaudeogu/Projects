# Delete promotional emails using Gmail API and Cron job. Runs 8PM daily.

## How to use:
1. Install dependencies
    ```Python
    pip3 install --upgrade google-api-python-client google-auth-httplib2 google-auth-oauthlib
    ```
2. Access the Gmail API from IDE using OAuth 2.0 token
    - [Enable API](https://support.google.com/googleapi/answer/6158841?hl=en)
    - [Get Token](https://support.google.com/googleapi/answer/6158849?hl=en&ref_topic=7013279&sjid=15952990207606155705-NA)
        - **'New Credentials'** === **'Create Credentials'**
3. Download JSON and rename to 'credentials.json', store in project directory
4. Set up a cron job
     - [Setup Link](https://www.ostechnix.com/a-beginners-guide-to-cron-jobs/)
     - I chose to run the script at 9PM daily. My cronjob looks like this:
         ```
         0 21 * * * /usr/bin/python3 <path to script>
         ```
     - To edit the cronjob, run `crontab -e` in the terminal.
     - To check if the cronjob is running, run `crontab -l` in the terminal.


### Trouble Shooting:
1. [Alternate Link For Full Set Up](https://developers.google.com/gmail/api/quickstart/python)
2. [If receiving an **Access Blocked** message](https://stackoverflow.com/questions/75454425/access-blocked-project-has-not-completed-the-google-verification-process)
<img src=error.png>