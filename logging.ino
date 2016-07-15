char body[]="v=1&t=event&tid=UA-77033033-1&cid=9eccb690-93aa-4513-835a-9a4f0f0e2a71&ec=ManelCategory&ea=action&el=label&ev=1&an=iot_app&av=1.0&ul=en-us&cd1=linux&cd2=1.2&cd3=RPi%2F2&cd4=arm&cd5=rust%20test&cd6=20160320123456&cd7=2016-05-25%2022:36:57";
#include <string.h>
#define DOMAIN "google-analytics.com"
TCPClient client;
bool connecte = false;
void setup()
{
  delay(1000);
  Serial.begin(9600);
  while(!Serial.available()) SPARK_WLAN_Loop();
  Serial.println("connecting....");
  int cnx = client.connect(DOMAIN, 80);
    //Serial.println("connected");
    if (cnx == 1) {
            Serial.println("connexion ok.");
            connecte = true;
            client.println("POST /collect HTTP/1.1");
            client.println("Host: " DOMAIN);
            client.print("Content-Length: ");
            client.println(strlen(body));
            client.println("");
            client.println(body);
            Serial.println(strlen(body));
        } else {
            Serial.println("connexion echouee, erreur : ");
            Serial.print(cnx, DEC);
        }


}

void loop() {
  if (connecte) {
        if (client.available()) {
            char c = client.read();
            Serial.print(c);
        }
        if (!client.connected()) {
            Serial.println();
            Serial.println("deconnexion.");
            connecte = false;
            client.stop();
        }
    }
}
