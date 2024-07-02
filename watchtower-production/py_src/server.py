# -----------------------------------
#
# Python code for the HTTP server
#
# Contributors: Arturo, Arkadiusz, Kyril, Hans
# The Als Rocketry Club
# Sonderborg, Denmark
#
# -----------------------------------

from flask import Flask, request, jsonify
from backend import echoCommand
app = Flask(__name__)

@app.route('/command', methods=['POST'])
def handleCommand():
    commandData = request.get_json()
    # Command data format: {"command": "launch", "value": 3}
    print(f"Received command: {commandData['command']} with value: {commandData['value']}")

    # Call backend processing function
    # Example: Echo the command back to the client
    return jsonify(echoCommand(commandData))

if __name__ == '__main__':
    app.run(debug=True, port=5000)