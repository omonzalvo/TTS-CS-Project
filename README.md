Speak-TTS MQTT Service
Authors:Onassis Monzalvo,Steban Ramirez,Adrian Larenas,Illich Estrada.

A Python-based Text-to-Speech (TTS) service designed for Raspberry Pi. This service listens for messages over the MQTT protocol and converts them into clear audio using the Google Text-to-Speech (gTTS) API, specifically optimized for ALSA audio drivers.

Dependences:
sudo apt update
sudo apt install ffmpeg alsa-utils -y

Python Libraries:
pip install paho-mqtt gtts

Configuration and Use:
The script is configured to use the hardware device plughw:2,0.Verify your device index using aplay -1 and update the following line in gtts_say.py if neccessary:
os.system(f'aplay -D plughw:2,0 -q "{wav_path}"')

Running the script:
python gtts_say.py

How To Start The Connection

Python
cd /home/raspberrypi/tts-proj
Create the environment
python3 -m venv venv
Activate it
source venv/bin/activate

Mosquitto
Start it and make sure it runs on every boot
sudo systemctl enable mosquitto
sudo systemctl start mosquitto

Check if it is running (it should say "active (running)")
sudo systemctl status mosquitto

mosquitto_pub -h localhost -t "home/voice" -m '{"message": "The message you are going to run", "lang": "en", "tld": "com"}'
