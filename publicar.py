import paho.mqtt.client as mqtt
from paho.mqtt.properties import Properties
from paho.mqtt.packettypes import PacketTypes
import random
import time

BROKER = "localhost"
PORT = 1883
TOPIC = "sensor/temperature"
CLIENT_ID = "temperature_sensor_publisher"

def generate_temperature_data():
    temperature = round(random.uniform(20.0, 30.0), 2)
    timestamp = time.strftime("%Y-%m-%d %H:%M:%S")
    return f"Temperature: {temperature} °C, Timestamp: {timestamp}"

# Crear cliente MQTT con ID
client = mqtt.Client(client_id=CLIENT_ID, protocol=mqtt.MQTTv5)

# Conexión al broker
client.connect(BROKER, PORT, 60)

try:
    while True:
        # Generar datos de temperatura
        temperature_data = generate_temperature_data()
        print(f"Enviando datos: {temperature_data}")

        # Crear propiedades del paquete MQTT
        properties = Properties(PacketTypes.PUBLISH)
        properties.UserProperty = [("client_id", CLIENT_ID)]  # Propiedad personalizada
        
        # Publicar datos con propiedades
        client.publish(TOPIC, payload=temperature_data, properties=properties)
        time.sleep(1)

except KeyboardInterrupt:
    print("Publicador detenido")

finally:
    client.disconnect()
