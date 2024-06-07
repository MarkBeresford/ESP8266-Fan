#!/usr/bin/env bash
MTQQ_PORT=1883
MTQQ_HOST=localhost
MTQQ_SUB () {
    mosquitto_sub -h $MTQQ_HOST -p $MTQQ_PORT -t ${1}
}
MTQQ_PUB () {

  EXPECTED_NUM_ARGS=2
  if [[ "$#" -ne ${EXPECTED_NUM_ARGS} ]]; then
    echo "NOT ENOUGH ARGS SUPPLIED, call func as follows: MTQQ_PUB <topic> <command> e.g MTQQ_PUB fan/topic ON"
  else {
    TOPIC=${1}
    COMMAND=${2}
    VALID_FAN_COMMANDS=("ON", "OFF", "FLIP")

    if [[ ${VALID_FAN_COMMANDS[@]} =~ $COMMAND ]] || ([[ $COMMAND =~ ^[0-9]+$ ]] && [[ $COMMAND -ge -1 ]] && [[ $COMMAND -le 256 ]]); then
      mosquitto_pub -h $MTQQ_HOST -p $MTQQ_PORT -t $TOPIC -m "$COMMAND"
      echo "${COMMAND} has been published to the fan topic"
    else
       echo "${COMMAND} is not a number (between 0 and 255) or valid command (${VALID_FAN_COMMANDS[*]})"
    fi
  }
  fi
}
alias MTQQ_START='brew services start mosquitto'
