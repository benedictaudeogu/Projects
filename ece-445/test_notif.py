import requests
import yaml

# Bot token and chat id are stored in secret.yaml (not commited)
with open('secret.yaml', 'r') as f:
    config = yaml.safe_load(f)

TOKEN = str(config['token'])
CHAT_ID = str(config['chat_id'])

message = "Your kitchen sink pipe temperature reached 40°F, system activated"

# url = f"https://api.telegram.org/bot{TOKEN}/getUpdates"

url = f"https://api.telegram.org/bot{TOKEN}/sendMessage?chat_id={CHAT_ID}&text={message}"

# Send the message
print(requests.get(url).json())
