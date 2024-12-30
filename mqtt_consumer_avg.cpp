// Start by `#include`-ing the Mosquitto MQTT Library and other standard libraries.
#include <mqtt/client.h>  // Mosquitto client.
#include <ostream>  // std::cout.
#include <regex>


int main()
{
    // In order to connect the mqtt client to a broker, 
    // Define an Ip address pointing to a broker. In this case, the localhost on port 1883.
    std::string ip = "localhost:1883";
    // Then, define an ID to be used by the client when communicating with the broker.
    std::string id = "consumer_avg";
 
    // Construct a client using the Ip and Id, specifying usage of MQTT V5.
    mqtt::client client(ip, id, mqtt::create_options(MQTTVERSION_5));
    // Use the connect method of the client to establish a connection to the broker.
    client.connect();
    // In order to receive messages from the broker, specify a topic to subscribe to.
    client.subscribe("sensor/temperature_avg");
    // Begin the client's message processing loop, filling a queue with messages.
    client.start_consuming();
 
    int count=0;
    bool running = true;
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
            std::cout << "Promedio "<<std::to_string(count)<<": "<<messageString<< std::endl;
            count++;

            // Perform processing on the string.
            // This is where message processing can be passed onto different
            // functions for parsing. 
            // Here, we break the loop and exit the program if a `quit` is received.
            //if (messageString == "quit")
            //{
            //    running = false;
            //} 
        }
    }
 
    return 0;
}