import json
import os
import tempfile
from paho.mqtt import client as mqtt_client
from gtts import gTTS

SAMPLE_RATE = 24000 

def say(text: str, lang: str = "en", tld: str = "com"):
    """
    Converts text to speech, processes it for HDMI compatibility, and plays it.
    """
    text = text.strip()
    if not text:
        return

    # Create temporary file paths to avoid SD card clutter
    with tempfile.NamedTemporaryFile(suffix=".mp3", delete=False) as f:
        mp3_path = f.name

    wav_path = mp3_path[:-4] + ".wav"

    try:
        # Generate MP3 via Google TTS API (requires internet)
        tts = gTTS(text=text, lang=lang, tld=tld)
        tts.save(mp3_path)

        # Convert to WAV (PCM) using FFmpeg
        # Forced to 24kHz Mono to ensure the HDMI driver accepts the format
        cmd_convert = f'ffmpeg -loglevel error -y -i "{mp3_path}" -ar {SAMPLE_RATE} -ac 1 "{wav_path}"'
        rc = os.system(cmd_convert)
        
        if rc != 0:
            print("{*} Error: FFmpeg failed. Install it with: sudo apt install ffmpeg")
            return

        # Play using ALSA's default player
        os.system(f'aplay -D plughw:2,0 -q "{wav_path}"')

    finally:
        # Cleanup: Remove temporary files
        for p in (mp3_path, wav_path):
            if os.path.exists(p):
                try:
                    os.remove(p)
                except OSError:
                    pass

# --- MQTT Logic ---

def on_message(client, userdata, msg):
    """Callback function triggered when a new MQTT message arrives."""
    try:
        # Decode the incoming JSON payload
        payload = json.loads(msg.payload.decode())
        
        # Extract fields with default fallbacks
        message = payload.get("message", "")
        language = payload.get("lang", "en")
        accent = payload.get("tld", "com")
        
        if message:
            print(f">> Playing: {message} ({language})")
            say(message, lang=language, tld=accent)
            
    except Exception as e:
        print(f"Failed to process JSON: {e}")

# Setup MQTT Client
client = mqtt_client.Client(mqtt_client.CallbackAPIVersion.VERSION2)
client.on_message = on_message

# Connect to the local broker (localhost)
client.connect("localhost", 1883, 60)

# Subscribe to the command topic
client.subscribe("home/voice")
print(" ▄█▀▀▀▄█                           ▀██                            █▀▀██▀▀█ █▀▀██▀▀█  ▄█▀▀▀▄█  ")
print(" ██▄▄  ▀  ▄▄▄ ▄▄▄    ▄▄▄▄   ▄▄▄▄    ██  ▄▄    ▄▄▄▄  ▄▄▄ ▄▄           ██       ██     ██▄▄  ▀  ")
print("  ▀▀███▄   ██▀  ██ ▄█▄▄▄██ ▀▀ ▄██   ██ ▄▀   ▄█▄▄▄██  ██▀ ▀▀          ██       ██      ▀▀███▄  ")
print("▄     ▀██  ██    █ ██      ▄█▀ ██   ██▀█▄   ██       ██      ████    ██       ██    ▄     ▀██ ")
print("█▀▄▄▄▄█▀   ██▄▄▄▀   ▀█▄▄▄▀ ▀█▄▄▀█▀ ▄██▄ ██▄  ▀█▄▄▄▀ ▄██▄            ▄██▄     ▄██▄   █▀▄▄▄▄█▀  ")
print("           ██                                                                                 ")
print("          ▀▀▀▀                                                                                ")
print("{*}Created By: Onassis Monzalvo,Steban Ramirez,Adrian Larenas,Illich Estrada")
print("{+}Waiting for messages on 'home/voice'...")
client.loop_forever()
