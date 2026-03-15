#define BLYNK_TEMPLATE_ID "TMPL3Bf4IE8oV"
#define BLYNK_TEMPLATE_NAME "Smart Plant"
#define BLYNK_AUTH_TOKEN "1pGcF5fsUec3cwGWxi9Jb2PRJj0Alioj"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <U8g2lib.h>
#include <Wire.h>

char ssid[] = "Yofi";
char pass[] = "@Anurag123";

#define DHT_PIN 4
#define SOIL_PIN 34
#define PIR_PIN 14
#define RELAY_PIN 5
#define BUTTON_PIN 13

#define VPIN_BUTTON_1 V12

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, 22, 21);

DHT dht(DHT_PIN, DHT11);
BlynkTimer timer;

float temperature;
float humidity;
int soilMoisture;

bool relayState = false;
bool motionDetected = false;

unsigned long pirTimer = 0;
unsigned long lastButtonPress = 0;

void updateDisplay()
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x13_tr);

  char buf[32];

  sprintf(buf,"Temp: %.1f C",temperature);
  u8g2.drawStr(0,12,buf);

  sprintf(buf,"Hum : %.1f %%",humidity);
  u8g2.drawStr(0,24,buf);

  sprintf(buf,"Soil: %d %%",soilMoisture);
  u8g2.drawStr(0,36,buf);

  sprintf(buf,"Pump:%s",relayState?"ON":"OFF");
  u8g2.drawStr(0,48,buf);

  sprintf(buf,"Motion:%s",motionDetected?"YES":"NO");
  u8g2.drawStr(0,60,buf);

  u8g2.sendBuffer();
}

void readSensors()
{
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  int raw = analogRead(SOIL_PIN);
  soilMoisture = map(raw,4095,0,0,100);

  Blynk.virtualWrite(V0,temperature);
  Blynk.virtualWrite(V1,humidity);
  Blynk.virtualWrite(V3,soilMoisture);

  updateDisplay();
}

void checkPIR()
{
  if(digitalRead(PIR_PIN)==HIGH)
  {
    motionDetected = true;
    pirTimer = millis();

    relayState = true;
    digitalWrite(RELAY_PIN,LOW);

    Blynk.virtualWrite(VPIN_BUTTON_1,relayState);
    Blynk.logEvent("pirmotion","Motion detected!");
  }

  if(motionDetected && millis()-pirTimer > 5000)
  {
    motionDetected = false;

    relayState = false;
    digitalWrite(RELAY_PIN,HIGH);

    Blynk.virtualWrite(VPIN_BUTTON_1,relayState);
  }
}

void checkButton()
{
  if(digitalRead(BUTTON_PIN)==LOW)
  {
    if(millis()-lastButtonPress > 300)
    {
      relayState = !relayState;
      digitalWrite(RELAY_PIN, relayState ? LOW : HIGH);
      Blynk.virtualWrite(VPIN_BUTTON_1,relayState);
      lastButtonPress = millis();
    }
  }
}

BLYNK_WRITE(VPIN_BUTTON_1)
{
  relayState = param.asInt();
  digitalWrite(RELAY_PIN, relayState ? LOW : HIGH);
}

void setup()
{
  Serial.begin(115200);

  Wire.begin(21,22);

  u8g2.begin();
  u8g2.setFont(u8g2_font_6x13_tr);

  u8g2.clearBuffer();
  u8g2.drawStr(15,30,"System Starting");
  u8g2.sendBuffer();

  dht.begin();

  pinMode(PIR_PIN,INPUT);
  pinMode(RELAY_PIN,OUTPUT);
  pinMode(BUTTON_PIN,INPUT_PULLUP);

  digitalWrite(RELAY_PIN,HIGH);

  WiFi.begin(ssid,pass);
  Blynk.config(BLYNK_AUTH_TOKEN);
  Blynk.connect();

  timer.setInterval(2000L,readSensors);
}

void loop()
{
  if(WiFi.status()==WL_CONNECTED)
  {
    Blynk.run();
  }

  checkButton();
  checkPIR();

  timer.run();
}