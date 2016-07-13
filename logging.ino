char body[]="v=1&t=event&tid=UA-77033033-1&cid=9eccb690-93aa-4513-835a-9a4f0f0e2a71&ec=category&ea=action&el=label&ev=1&an=iot_app&av=1.0&ul=en-us&cd1=linux&cd2=1.2&cd3=RPi%2F2&cd4=arm&cd5=rust%20test&cd6=20160320123456&cd7=2016-05-25%2022:36:57";
#include <string.h>
TCPClient client;
void setup()
{
  Serial.begin(9600);
  while(!Serial.available()) Particle.process();
  Serial.println("connecting....");
  if (client.connect("https://www.google-analytics.com/collect", 80))
  {
    Serial.println("connected");
    client.println("POST /update HTTP/1.0");
    client.println("Host: https://www.google-analytics.com/collect");
    client.println("Content-Length: ");
    client.println(strlen(body)+14);
    client.println();
    client.println(body);
  }
  else
  {
    Serial.println("connection failed");
  }
}

void loop() {
  if (client.available())
    {
      char c = client.read();
      Serial.print(c);
    }

    if (!client.connected())
    {
      Serial.println();
      Serial.println("disconnecting.");
      client.stop();
      for(;;);
    }

}
