# Arduino Fan/MQTT message broker
Fun small project for making a fan spin using a local MQTT message broker [mosquitto](https://mosquitto.org/).

## Set Up
- Mosquitto installed using [brew](https://formulae.brew.sh/formula/mosquitto)
- Source `fan.sh` script
- Create a `secrets.h` file in the same directory as the `fan.ino` script with the following format:
```
#define SECRET_SSID "<WIFI SSID>"
#define SECRET_PASSWORD "<WIFI password>"
#define SECRET_MQTT_BROKER "<IP address of network>"
#define SECRET_MQTT_PORT <MQTT port>
```

## Start fan topic
Run `MQTT_START`

## Sub to fan topic
Run `MQTT_SUB fan/topic`

## Pub to fan topic
Run `MQTT_SUB fan/topic <message>`

### Accepted pub messages
| Message    | Outcome | Outcome |
| -------- | ------- | ------- |
| 0 $\leq$ x $\leq$ 255  | Sets fan duty cycle to x    | MQTT_SUB fan/topic 100 |
| ON | set duty cycle to 100     | MQTT_SUB fan/topic ON |
| OFF    | set duty cycle to 0    | MQTT_SUB fan/topic OFF |
| FLIP    | reverse rotation of fan, keeps same duty cycle    | MQTT_SUB fan/topic FLIP |

Note: The accepted messages must either be between 0 and 255 or match `ON`, `OFF`, or `FLIP` exactly (case sensitive).

## Components used
- [ESP8266 board](https://www.amazon.co.uk/gp/product/B0754LZ73Z/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
- Fan blade and 3-6V motor
- [L298N](https://www.amazon.co.uk/DollaTek-Stepper-Controller-Module-Arduino/dp/B07DK6Q8F9/ref=sr_1_5?crid=3D4CMLAJXWRTK&dib=eyJ2IjoiMSJ9.2vtjk9gxmQTTucxhwg0bx_SjMWZtBd5Tdpd2DJZjZtwLDZdxRFvlz84YzkbmoSpX_-8euoEeAPaSuclqmWXOXGwv-WH-alttbH-aFAnC0cJTfe0cdS4MGnNbWu1ACAyhInnOrHAHiJfH6kOW4nmnxf-ol0gp1mpizm3N26TeklJhui5arH_1qFO7Nbp3MY0u1gsmajskh4e2zO6EctTCMaZdCnmiEkBZvEWPAI7dDJBs3G51VJxKe9vRBO1SO-QMTe_I9_oPUgjQZP6p8aXPC0GBl9FXnap67lYF3yOwRoI.y6lY8SRdb9lUk6K7uguZ-rmXuian5M3fmYFangHLO7Q&dib_tag=se&keywords=L298n&qid=1717776000&s=industrial&sprefix=l298%2Cindustrial%2C84&sr=1-5)
- [Power connector](https://www.amazon.co.uk/dp/B0D2P1PF8J?psc=1&ref=ppx_yo2ov_dt_b_product_details)
- 104pF Ceramic Capacitor

## Resources used
- [For the circuitry](https://randomnerdtutorials.com/esp8266-nodemcu-dc-motor-l298n-motor-driver-control-speed-direction/)
