# Full Stack Budget Tracker Web App - Started 10/2023
  * Utilizing Plaid API to fetch real banking data
      * First developing in sandbox environment
  * Building in Java/Springboot and React
  * Looking to use Oracle Sql Developer (Setting up now)
  * Goal is to achieve something better than YNAB, but for free

## Features To Add
1. Income Streams tracker
2. Bank balance displayed
3. Latest 10 transactions shown when account selected
4. Login/Sign up
    * Plaids 'Link Authorization' required so I can avoid needing to store banking credentials
       * I beleieve, if not the case, will delete inputs after certain amount of time
    * Security - hashing app account passwords
    * Prevent entering other links from login until login/sign-up completed
5. Goal setting abilities
    * Graphs/Bars to show progress status
6. Content Security Policy (CSP) - Security Standard
    * [Guide](https://www.stackhawk.com/blog/spring-content-security-policy-guide-what-it-is-and-how-to-enable-it/#:~:text=Luckily%2C%20it's%20pretty%20simple%20to,a%20configuration%20that%20enables%20CSP.)
  

## Current Status
1. Can retrieve transactions and access tokens
2. Currently setting up database to persist json
3. Will flesh out other features once I am able to save the data
