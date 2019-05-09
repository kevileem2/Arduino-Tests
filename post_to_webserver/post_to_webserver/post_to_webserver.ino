
// Load Wi-Fi library
#include <WiFi.h>
// similar webpage on 1 line , use minify ?? http://minifycode.com/html-minifier/

//const char* ssid = "DESKTOP-ID7JU42 8285";
//const char* password =  "X782$5w9";

//const char* ssid = "Arduino-CVO";
//const char* password = "";

const char* ssid = "WiFi-2.4-E918";
const char* password =  "wudz36zwrkb63";
const byte red_button = 13;
const byte green_button = 12;

const char indexpage[] = "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Post to Web Server | CVO Leerstad - Arduino II | Index</title><link rel=\"stylesheet\" href=\"assets/css/main.css\"><link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0/css/materialize.min.css\"><link rel=\"stylesheet\" href=\"https://fonts.googleapis.com/icon?family=Material+Icons\"> <script src=\"assets/js/main.js\"></script> </head><body> <header> <nav><div class=\"nav-wrapper red darken-1\"> <a href=\"index.html\" class=\"brand-logo center\"><i class=\"material-icons\">all_inclusive</i>Arduino</a></div> </nav> </header> <main><div class=\"container\"><div class=\"row justify-content-center\"><div class=\"col s12 l6\"><h4>Here is where the state of the first button will be send to:</h4> <span id=\"button1_state\"></span></div><div class=\"col s12 l6\"><h4>Here is where the state of the second button will be send to:</h4> <span id=\"button2_state\"></span></div></div></div> </main> <footer class=\"page-footer\"><div class=\"container\"><div class=\"row\"><div class=\"col l6 s12\"><h5 class=\"white-text\">Information</h5><p class=\"grey-text text-lighten-4\">This Website is made in a school environment and is not used for commercial purposes.</p></div></div></div><div class=\"footer-copyright z-depth-1 red darken-1\"><div class=\"container\"> © 2019 Kevin Leemans</div></div> </footer></body></html>";
const char styles[] = "body {\n    display: flex;\n    min-height: 100vh;\n    flex-direction: column;\n    background-color: #EEE;\n  }\n  \n  main {\n    flex: 1 0 auto;\n  }";
const char script[] = "document.addEventListener('DOMContentLoaded', function() {\n    setInterval(() => {\n        var xhttp = new XMLHttpRequest()\n        xhttp.onreadystatechange = function() {\n            if (this.readyState == 4 && this.status == 200) {\n            document.getElementById(\"button1_state\").innerHTML = this.responseText\n            }\n        }\n        xhttp.open(\"GET\", \"firstbutton\", true)\n        xhttp.send()\n    }, 100)\n    setInterval(() => {\n        var xhttp = new XMLHttpRequest()\n        xhttp.onreadystatechange = function() {\n            if (this.readyState == 4 && this.status == 200) {\n            document.getElementById(\"button2_state\").innerHTML = this.responseText\n            }\n        }\n        xhttp.open(\"GET\", \"secondbutton\", true)\n        xhttp.send()\n    }, 100)\n})";


// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

void setup() {
  Serial.begin(115200);
  
  pinMode(red_button, INPUT_PULLUP);
  pinMode(green_button, INPUT_PULLUP);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    //header = "";
    while (client.connected()) {            // loop while the client's connected

      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character every line coming from browser ended by CRLF  or \r\n
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:

          if (currentLine.length() == 0) {

            if (header.indexOf("GET /index.html") >= 0) {
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.print("Content-length:");client.println(sizeof(indexpage)-1);
              client.println("Connection:close");
              client.println("");
              client.print(indexpage);
              
              Serial.println("ESP sended index page to client");
              
            }else if (header.indexOf("GET /assets/css/main.css") >= 0) {
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/css");
              client.print("Content-length:");client.println(sizeof(styles)-1);
              client.println("Connection:close");
              client.println("");
              client.print(styles);
              
              Serial.println("ESP sended css file to client");

            }else if (header.indexOf("GET /firstbutton") >= 0) {
              client.print("HTTP/1.1 200 OK\r\nContent-Length:1\r\n\r\n");client.print(digitalRead(red_button));
              Serial.println("ESP sended state of red button to server"); 

            }else if (header.indexOf("GET /secondbutton") >= 0) {
              client.print("HTTP/1.1 200 OK\r\nContent-Length:1\r\n\r\n");client.print(digitalRead(green_button));
              Serial.println("ESP sended state of green button to server"); 

            }else if (header.indexOf("GET /assets/js/main.js") >= 0) {
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/javascript");
              client.print("Content-length:");client.println(sizeof(script)-1);
              client.println("Connection:close");
              client.println("");
              client.print(script);
              
              Serial.println("ESP sended javascript file to client");

            }else if (header.indexOf("GET /") >= 0) {
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.print("Content-length:");client.println(sizeof(indexpage)-1);
              client.println("Connection:close");
              client.println("");
              client.print(indexpage);
              
              Serial.println("ESP sended index page to client");
              
            }
            break; // jumps out of closed loop .. here the while( client.connected)

          } else { // if you got a newline, then clear currentLine

            currentLine = "";

          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
    delay(250);
  }
}
