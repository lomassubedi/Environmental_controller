import paho.mqtt.client as mqtt #import the client1
import time

# broker_address="192.168.100.81" 
broker_address="192.168.1.89" 

#broker_address="iot.eclipse.org" #use external broker
client = mqtt.Client("P1") #create new instance


client.connect(broker_address) #connect to broker

while True:
	client.publish("profile/light","LIGHT") #publish
	print("Publishing : profile/light " + "LIGHT")
	time.sleep(1)
	