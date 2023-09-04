# Delete promotional emails using Gmail API and Cron job. Runs 7PM daily.

## How to use:
1. Install dependencies
    ```Python
    pip3 install --upgrade google-api-python-client google-auth-httplib2 google-auth-oauthlib
    ```
    ```Python
    pip3 install google
    ```
    ```Python
    pip3 install pyinstaller
    ```
2. Access the Gmail API from IDE using OAuth 2.0 token
    - [Enable API](https://support.google.com/googleapi/answer/6158841?hl=en)
    - [Get Token](https://support.google.com/googleapi/answer/6158849?hl=en&ref_topic=7013279&sjid=15952990207606155705-NA)
        - **'New Credentials'** === **'Create Credentials'**
3. Download JSON and rename to 'credentials.json', store in project directory
4. Set up a job using crontab
     - [Setup Link](https://www.ostechnix.com/a-beginners-guide-to-cron-jobs/)
     - I chose to run the script at 7PM daily. My command looks like this:
         ```Python
         0 19 * * * usr/bin/python3 <path to exceutable>
         ```
     - To edit the cronjob, run `crontab -e` in the terminal.
     - To verify if the cronjob was created, run `crontab -l` in the terminal.


### Trouble Shooting:
1. [Alternate Link For Full Set Up](https://developers.google.com/gmail/api/quickstart/python)
2. [If receiving an **Access Blocked** message](https://stackoverflow.com/questions/75454425/access-blocked-project-has-not-completed-the-google-verification-process)
<img src=error.png>

3. SyntaxError: Non-UTF-8 code starting with '\xcf' in file <path to exceutable> on line 1, but no encoding declared; see http://python.org/dev/peps/pep-0263/ for details
    ```Python
        #Insert at the top of script - will look like comments
        #!/usr/bin/python3
        # -*- coding: latin-1 -*-
    ```
4. from googleapiclient.discovery import build ModuleNotFoundError: No module named 'googleapiclient'
    ```Python
    pip3 install --upgrade google-api-python-client google-auth-httplib2 google-auth-oauthlib
    ```


### Alternatives:
To create a new executable of the script (if changes are made)
1. Go into directory of api.py in terminal --> api folder
2. Run:
```Python
pyinstaller --onefile api.py
# An executable is created int the `dist` folder
```