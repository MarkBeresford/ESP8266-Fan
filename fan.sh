#!/usr/bin/env bash
MQTT_PORT=1883
MQTT_HOST=localhost
MQTT_SUB () {
    mosquitto_sub -h $MQTT_HOST -p $MTQQ_PORT -t ${1}
}
MQTT_PUB () {

  EXPECTED_NUM_ARGS=2
  if [[ "$#" -ne ${EXPECTED_NUM_ARGS} ]]; then
    echo "NOT ENOUGH ARGS SUPPLIED, call func as follows: MQTT_PUB <topic> <command> e.g MTQQ_PUB fan/topic ON"
  else {
    TOPIC=${1}
    COMMAND=${2}
    VALID_FAN_COMMANDS=("ON", "OFF", "FLIP")

    if [[ ${VALID_FAN_COMMANDS[@]} =~ $COMMAND ]] || ([[ $COMMAND =~ ^[0-9]+$ ]] && [[ $COMMAND -ge -1 ]] && [[ $COMMAND -le 256 ]]); then
      mosquitto_pub -h $MQTT_HOST -p $MTQQ_PORT -t $TOPIC -m "$COMMAND"
      echo "${COMMAND} has been published to the fan topic"
    else
       echo "${COMMAND} is not a number (between 0 and 255) or valid command (${VALID_FAN_COMMANDS[*]})"
    fi
  }
  fi
}
alias MQTT_START='brew services start mosquitto'
