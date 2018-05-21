import paho.mqtt.client as mqtt #import the client1
import time
import random
import profile_vars as prof

# Home
# broker_address="192.168.1.104"
broker_address="192.168.100.81"

# Office
# broker_address="192.168.1.89" 

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

a = 1

while a:
	
	the_input = input('->')
	profileCommand, profileNoCommand, varCommand, argument = the_input.split()
	command = profileCommand + "/" + profileNoCommand + "/" + varCommand	
	client.publish(command, argument) #publish
	print("Publishing : " + command + " " + argument)
	#time.sleep(1)
		
	'''
	# a = 1
	a = a - 1
	b = 0
	argumentList = ["ON", "OFF"]
	for i in range(0, 21):
		for indx in range(0, len(prof.varCodeProfile)):
			b = b + 1
			command = "profile" + "/" + str(i) + "/" + prof.varCodeProfile[indx] + "--> " + str(b)
			argument = argumentList[0]
			random.shuffle(argumentList)
			client.publish(command, argument) #publish
			print("Publishing : " + command + " " + argument)
			#time.sleep(0.1)	
	'''