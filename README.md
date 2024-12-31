# Iot_Project_1
Proyectos de IoT usando C++, Python y Mosquitto


Como ejecutar los scripts ?

1.- tener el broker en ejecucion -> mosquitto -v
2.- iniciar el primer suscriptor -> mqtt_consumer.cpp
3.- iniciar el primer publicador -> publicar.py
4.- iniciar el segundo suscriptor -> mqtt_consumer_avg.cpp

notas:
  mqtt_consumer.cpp actua como sub y pub , cada diez segundos manda un promedio de temperaturas a quienes se hayan suscrito al topico. 
