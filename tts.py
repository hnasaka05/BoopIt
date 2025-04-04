import serial
import pyttsx3

port = ""
ser = serial.Serial(port, 9600, timeout=1)
engine = pyttsx3.init()

while True:
     if ser.in_waiting > 0: 
          text = ser.readline().decode("utf-8").strip()
          print(f"Speaking: {text}")
          engine.say(text)
          engine.runAndWait()




