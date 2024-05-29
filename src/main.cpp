#include <LittleFS.h>
#include <ArduinoJson.h>
JsonDocument doc;

const char *json ="{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";

DeserializationError error = deserializeJson(doc, json);
void setup()
{
  Serial.begin(115200);
  //////
  if (error)
  {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  if (!LittleFS.begin())
  {
    Serial.println("Failed to mount file system");
    return;
  }
}

void writeToFile(const char *path, const char *message)
{
  File file = LittleFS.open(path, "w");
  if (!file)
  {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print(message))
  {
    Serial.println("File written successfully");
  }
  else
  {
    Serial.println("Write failed");
  }
  file.close();
}

void readFromFile(const char *path)
{
  File file = LittleFS.open(path, "r");
  if (!file)
  {
    Serial.println("Failed to open file for reading");
    return;
  }

  while (file.available())
  {
    Serial.write(file.read());
  }
  file.close();
}
void loop()
{
  writeToFile("/example.json", json);
  readFromFile("/example.json");
  const char *sensor = doc["sensor"];
  long time = doc["time"];
  double latitude = doc["data"][0];
  double longitude = doc["data"][1];

  // Print the values
  Serial.println(sensor);
  Serial.println(time);
  Serial.println(latitude, 6);
  Serial.println(longitude, 6);
  delay(5000); // Wait for 5 seconds before repeating
}
