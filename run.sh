#!/bin/sh

# Set config
RELAY_ADDR='http://127.0.0.1:8080'
PASSWORD='boop'

# Set path
SHELL_PATH=`pwd -P`

CLIENT="${SHELL_PATH}/memory-client"
RELAY="${SHELL_PATH}/relay-server"
WEB="${SHELL_PATH}/web"

# Kill process already excuted
pkill -9 'python3'
pkill -9 'node'
pkill -9 'TarkovInjector'

# Run RELAY server
echo "Run ${RELAY}"
node ${RELAY}/index.js &

# Run WEB
cd ${WEB}
echo ${WEB}
echo "Run ${WEB}"
python3 -m http.server &

# Wait activate interface server
sleep 1

# Run memory CLIENT
echo "Run ${CLIENT}"
${CLIENT}/TarkovInjector ${RELAY_ADDR} ${PASSWORD} -s
