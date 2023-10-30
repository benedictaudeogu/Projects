# Full Stack Finance Management Web App - Started 10/2023
  * Utilizing Plaid API developer access to fetch real banking data
      * First developing in sandbox environment
  * Frontend in React
  * Backend in Java/Springboot
  * Database is MySQL
  * Goal is to achieve result similar to YNAB without spending money
     * Project will be centered around my use case then potentially grown to fit the amount of users I can have with developer access (to still be $0)

## Features To Add
1. Bank balance displayed for main (chosen) account
  1.1 Can view others separately
3. Income Streams viewer
4. Latest 10 transactions shown
5. Login/Sign up
    * Plaids 'Link Authorization' required so I can avoid needing to store banking credentials
    * Security - hashing login passwords
    * Prevent entering other links from login until login/sign-up completed
6. Goal setting abilities
    * Graphs/Bars to show progress status
7. Would be nice to have a credit score tracker but may need another api like experian for this (will look into free options)
8. Content Security Policy (CSP) - Security Standard
    * [Guide](https://www.stackhawk.com/blog/spring-content-security-policy-guide-what-it-is-and-how-to-enable-it/#:~:text=Luckily%2C%20it's%20pretty%20simple%20to,a%20configuration%20that%20enables%20CSP.)
9. Display list of institutions offered for connection
  
**Extra:** View student loans (need to check if these institutions are in scope by Plaid)
  
## Current Status: Functional front end connected to backend and displaying api call requests
1. Looking through Plaid's availability to decide which features should be implemented
2. Able to grab and display previous transactions and available insitutions
3. Continual work on React side as api calls added to controller file

## Future
* Containerize with docker
* Deploy
* Host on raspberry pi
