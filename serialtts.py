import serial
from playsound import playsound

port = "/dev/cu.usbmodem1401"

ser = serial.Serial(port, 9600, timeout=1)
#engine = pyttsx3.engine()
print("listening for input")
while True:
    if ser.in_waiting > 0: 
        text = ser.readline().decode('utf-8').strip()
        if(text == "Touch It"): 
            print("playing touch.mp3")
            playsound("touch.mp3")

        elif(text == "Twist It"):
            print("playing twist.mp3")
            playsound("twist.mp3")

        elif(text == "Scream It"): 
            print("playing scream.mp3")
            playsound("scream.mp3")

        elif(text == "Caress It"): 
            print("play caress.mp3")
            playsound("caress.mp3")

        elif(text == "start"):
            print("playing start.mp3")
            playsound("start.mp3")

        elif(text == "lose"):
            print("playing you lose")
            playsound("lose.mp3")