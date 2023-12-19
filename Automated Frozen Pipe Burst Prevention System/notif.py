import requests
import yaml
import time
from w1thermsensor import W1ThermSensor

# Threshold temperature in Fahrenheit
TEMP_THRESHOLD = 55


def main():
    # Bot token and chat id are stored in secret.yaml (not commited)
    with open('/home/pi/secret.yaml', 'r') as f:
        config = yaml.safe_load(f)

    TOKEN = str(config['token'])
    CHAT_ID = str(config['chat_id'])

    # Send initialization message
    message = "Initializing system..."
    url = f"https://api.telegram.org/bot{TOKEN}/sendMessage?chat_id={CHAT_ID}&text={message}"
    print(requests.get(url).json())

    # Initialize the sensor
    sensor = W1ThermSensor()

    # Temperature check loop
    while True:
        try:
            # Get the temperature in Fahrenheit
            temperature = sensor.get_temperature() * 9 / 5 + 32
            print(temperature)

            if temperature < TEMP_THRESHOLD:
                message = f"Your kitchen sink pipe temperature reached {temperature:.2f}°F, system activated"
                url = f"https://api.telegram.org/bot{TOKEN}/sendMessage?chat_id={CHAT_ID}&text={message}"

                # Send the notification
                print(requests.get(url).json())

                # Wait 1 minute before sending another notification
                time.sleep(60)
        except:
            print("Error reading temperature")

        # Wait between temperature checks
        time.sleep(3.1)


if __name__ == "__main__":
    main()
