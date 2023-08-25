# SUMMARY: This is a python script that deletes promotional gmails daily at 9PM EST using a cron job. It uses the 'poplib' and 'schedule' libraries to connect to the gmail server and run the cron job respectively. 

## How to use:
1. Create an app password for your gmail account in order to use this script.
    - [Instructions Here](https://support.google.com/accounts/answer/185833?hl=en)
2. I chose to store username and password in a secret.yaml (found in .gitignore). You can choose to do the same or just hardcode it in the script.
3. Run the script using python3.6 or higher. I used python3.11.5
4. You can also enable the scheduler manually.
