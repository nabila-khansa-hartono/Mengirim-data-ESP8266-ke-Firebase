//Memasukkan Library yang diperlukan
#include <FirebaseESP8266.h>
#include <DHT.h>
#include <ESP8266WiFi.h>

//Mendefinisikan pin dan tipe sensor DHT
#define DHTPIN D1
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//Diisikan sesuai dengan perangkat masing-masing
#define FIREBASE_HOST "https://alamatdatabasefirebasekalian"
#define FIREBASE_AUTH "cbdiyfia27164nfnxffmqfqsynsdjhfsajf37y"
#define WIFI_SSID "XXXXXX"
#define WIFI_PASSWORD "YYYYYYYY"

//Define FirebaseESP8266 data object
FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);
  dht.begin();
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop(){
  //Sensor DHT11 membaca suhu dan kelembaban
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  //Memeriksa apakah sensor berhasil membaca suhu dan kelembaban
  if (isnan(h) || isnan(t)) {
    Serial.println("Gagal membaca sensor DHT11");
    return;
  }

  //Menampilkan suhu dan kelembaban pada serial monitor
  Serial.print("Kelembaban: ");
  Serial.print(h);
  Serial.println("%");
  Serial.print("Suhu: ");
  Serial.print(t);
  Serial.print("*C");

//Memberikan status suhu dan kelembaba kepada firebase
if (Firebase.setFloat(firebaseData, "/Hasil_Pembacaan/suhu", t))
  {
    Serial.println("Suhu terkirim");
  }
  else
  {
    Serial.println("Suhu tidak terkirim");
    Serial.println("Karena: " + firebaseData.errorReason());
  }
  
  if (Firebase.setFloat(firebaseData, "/Hasil_Pembacaan/kelembaban", h))
  {
    Serial.println("Kelembaban terkirim");
  }
  else
  {
    Serial.println("Kelembaban tidak terkirim");
    Serial.println("Karena: " + firebaseData.errorReason());
  }
  delay (1000);
}
