# -----------------------------------
#
# Python code for the backend processing
#
# Contributors: Arturo, Arkadiusz, Kyril, Hans
# The Als Rocketry Club
# Sonderborg, Denmark
#
# -----------------------------------

def echoCommand(commandData):
    # Process the command data
    # Example: Echo the command back to the client
    response = {'status': 'success', 
                'command': commandData['command'],
                'value': commandData['value']}
    return response