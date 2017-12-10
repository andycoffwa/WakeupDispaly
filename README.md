# WakeupDispaly
Wake up timer for the kids. This version includes the display.

## Build


## Upload firmware

Update paths to bin file and also usbserial.

```bash
python ~/esptool-master/esptool.py -p /dev/cu.usbserial-DN026EBJ -b 512000  write_flash 0x00000 /Users/andrew/Documents/PlatformIO/Projects/WakeupDisplay-thingdev/.pioenvs/thingdev/firmware.bin
```

## Serial monitoring

```bash
pio device monitor --port /dev/cu.usbserial-DN026EBJ --baud 115200
```
## Device config

Device reads an online config file from s3 located here `s3-ap-southeast-2.amazonaws.com/wakeup-timer/config.json`.

This must be read over https.

Config file is in the format:

```json
{
  "timezone" : "Australia/Sydney",
  "location" : "Bondi",
  "wake-up-time" : "07:00:00"
}
```

## Time API

The app uses the timezoneDB API `api.timezonedb.com`. Details and instructions for the use of timezone API are here `https://timezonedb.com/references/get-time-zone`

API url with zone hardcoded: `/v2/get-time-zone?key=5T7J6OVIZGUW&format=json&zone=Australia/Sydney&by=zone`

## Weather API

The WakeupDisplay uses the openweathermap API.

API output is:

```json
{"cod":"200","message":0.0073,"cnt":6,"list":[{"dt":1512939600,"main":{"temp":20.63,"temp_min":20.53,"temp_max":20.63,"pressure":1027.8,"sea_level":1033.9,"grnd_level":1027.8,"humidity":75,"temp_kf":0.1},"weather":[{"id":800,"main":"Clear","description":"clear sky","icon":"01d"}],"clouds":{"all":0},"wind":{"speed":1.61,"deg":0.000915527},"sys":{"pod":"d"},"dt_txt":"2017-12-10 21:00:00"},{"dt":1512950400,"main":{"temp":25.43,"temp_min":25.35,"temp_max":25.43,"pressure":1027.24,"sea_level":1033.33,"grnd_level":1027.24,"humidity":57,"temp_kf":0.08},"weather":[{"id":800,"main":"Clear","description":"clear sky","icon":"01d"}],"clouds":{"all":0},"wind":{"speed":1.56,"deg":35.5011},"sys":{"pod":"d"},"dt_txt":"2017-12-11 00:00:00"},{"dt":1512961200,"main":{"temp":27.73,"temp_min":27.68,"temp_max":27.73,"pressure":1024.9,"sea_level":1031.11,"grnd_level":1024.9,"humidity":48,"temp_kf":0.05},"weather":[{"id":800,"main":"Clear","description":"clear sky","icon":"01d"}],"clouds":{"all":0},"wind":{"speed":2.36,"deg":71.0023},"sys":{"pod":"d"},"dt_txt":"2017-12-11 03:00:00"},{"dt":1512972000,"main":{"temp":26.55,"temp_min":26.52,"temp_max":26.55,"pressure":1024.37,"sea_level":1030.28,"grnd_level":1024.37,"humidity":51,"temp_kf":0.03},"weather":[{"id":801,"main":"Clouds","description":"few clouds","icon":"02d"}],"clouds":{"all":12},"wind":{"speed":3.02,"deg":75.5004},"sys":{"pod":"d"},"dt_txt":"2017-12-11 06:00:00"},{"dt":1512982800,"main":{"temp":23.11,"temp_min":23.11,"temp_max":23.11,"pressure":1025.81,"sea_level":1031.75,"grnd_level":1025.81,"humidity":62,"temp_kf":0},"weather":[{"id":801,"main":"Clouds","description":"few clouds","icon":"02n"}],"clouds":{"all":20},"wind":{"speed":2.51,"deg":78.5011},"sys":{"pod":"n"},"dt_txt":"2017-12-11 09:00:00"},{"dt":1512993600,"main":{"temp":21.31,"temp_min":21.31,"temp_max":21.31,"pressure":1027.06,"sea_level":1033.27,"grnd_level":1027.06,"humidity":77,"temp_kf":0},"weather":[{"id":802,"main":"Clouds","description":"scattered clouds","icon":"03n"}],"clouds":{"all":48},"wind":{"speed":2.36,"deg":79.5031},"sys":{"pod":"n"},"dt_txt":"2017-12-11 12:00:00"}],"city":{"id":6619279,"name":"City of Sydney","coord":{"lat":-33.8678,"lon":151.2084},"country":"AU"}}
```
