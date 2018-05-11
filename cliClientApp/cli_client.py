import paho.mqtt.client as mqtt #import the client1
import time

# Home
#broker_address="192.168.100.81"

# Office
broker_address="192.168.1.89" 

# broker_address = "m14.cloudmqtt.com"
# username = "icqulyad"
# password = "Fyk1fuYGR_PO"
# port = 18772

#broker_address="iot.eclipse.org" #use external broker
client = mqtt.Client("P1") #create new instance

#client.username_pw_set(username, password)
#client.connect(broker_address, port) #connect to broker

client.connect(broker_address)

print("Connected to the broker !!!", broker_address)

while True:
	
	the_input = input('->')
	profileCommand, profileNoCommand, varCommand, argument = the_input.split()
	command = profileCommand + "/" + profileNoCommand + "/" + varCommand
	client.publish(command, argument) #publish
	print("Publishing : " + command + " " + argument)
	time.sleep(1)
	
