// Start by `#include`-ing the Mosquitto MQTT Library and other standard libraries.
#include <mqtt/client.h>  // Mosquitto client.
#include <ostream>  // std::cout.
#include <regex>
#include <vector>



float get_value(std::string message)
{
    std::regex numberRegex(R"((\d+\.\d+))");
    std::smatch match;

    // Buscar el primer número decimal
    if (std::regex_search(message, match, numberRegex)) {
        // Convertir el número encontrado a float
        float temperature = std::stof(match.str(1));
        return temperature;
    }

    return 0.0;
}

float get_avg(std::vector<float> tmps)
{
    float sum = 0.0; // Suma acumulativa
    for (float num : tmps) {
        sum += num; // Sumar cada valor
    }

    // Dividir la suma total por el número de elementos
    float average = sum / tmps.size();

    return average;
}
 
// With the library header files included, continue by defining a main function.
int main()
{
    // In order to connect the mqtt client to a broker, 
    // Define an Ip address pointing to a broker. In this case, the localhost on port 1883.
    std::string ip = "localhost:1883";
    // Then, define an ID to be used by the client when communicating with the broker.
    std::string id = "consumer";

    std::vector<float> temperatures;
 
    // Construct a client using the Ip and Id, specifying usage of MQTT V5.
    mqtt::client client(ip, id, mqtt::create_options(MQTTVERSION_5));
    // Use the connect method of the client to establish a connection to the broker.
    client.connect();
    // In order to receive messages from the broker, specify a topic to subscribe to.
    client.subscribe("sensor/temperature");
    

    //tambien se  vuelve publicador
    mqtt::message_ptr timeLeftMessagePointer = mqtt::make_message("sensor/temperature_avg", "");
    // Begin the client's message processing loop, filling a queue with messages.


    client.start_consuming();
 
    bool running = true;
    int count=0;

    while (running)
    {
        // Construct a message pointer to hold an incoming message.
        mqtt::const_message_ptr messagePointer;
 
        // Try to consume a message, passing messagePointer by reference.
        // If a message is consumed, the function will return `true`, 
        // allowing control to enter the if-statement body.
        if (client.try_consume_message(&messagePointer))
        {
            // Construct a string from the message payload.
            std::string messageString = messagePointer -> get_payload_str();
            // Print payload string to console (debugging).
            std::cout << messageString << std::endl;
            count++;


            float temp = get_value(messageString);            
            temperatures.push_back(temp);

            if(count%10==0){
                timeLeftMessagePointer->set_payload(std::to_string(get_avg(temperatures)));
                client.publish(timeLeftMessagePointer);
            }
            temperatures.clear();
        }
    }
 
    return 0;
}