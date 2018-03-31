import paho.mqtt.client as mqtt #import the client1
import time

broker_address="192.168.100.81" 
# broker_address="192.168.1.89" 

#broker_address="iot.eclipse.org" #use external broker
client = mqtt.Client("P1") #create new instance

client.connect(broker_address) #connect to broker

print("Connected to the broker !!!")

while True:
	
	the_input = input('->')
	profileCommand, profileNoCommand, varCommand, argument = the_input.split()
	command = profileCommand + "/" + profileNoCommand + "/" + varCommand
	client.publish(command, argument) #publish
	print("Publishing : " + command + " " + argument)
	time.sleep(1)
	