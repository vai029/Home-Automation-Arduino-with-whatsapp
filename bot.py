from flask import Flask, request
import requests
from twilio.twiml.messaging_response import MessagingResponse
import serial
ser = serial.Serial('COM5',9600)                 
import time

app = Flask(__name__)


@app.route('/bot', methods=['POST'])
def bot():
    msg = request.form.get('Body', '').lower()
    resp = MessagingResponse()
    responded = False
    if 'status' in msg:   
        ser.write(b'3')
        msg1 = ser.readline().decode()
        msg2 = ser.readline().decode()
        msg3 = ser.readline().decode()
        resp.message(msg1 + msg2 + msg3)
        responded = True
    if 'fan on' in msg:
        resp.message("Message is sent to the system to turn on the Fan")
        ser.write(b'1')
        responded = True
    if 'fan off' in msg:
        resp.message("Message is sent to the system to turn off the Fan")
        ser.write(b'2')
        responded = True
    if not responded:
        resp.message("Not Valid option")
    return str(resp)


if __name__ == '__main__':
    app.run(port=4000)
