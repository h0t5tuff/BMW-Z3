Simply I wanted to open my BMW Z3 door from my phone via bluetooth, or use my fingerprint. So i did that and here's the code. just make sure u use a chip with a hard serial USART (i.e. arduino nano every or esp32) because that's how i hooked the finger print sensor to the chip. The bluetooth module is connected via a soft serial UART to the chip. I could have used two soft serials for this but it doesn't seem worth it because two soft serials is never a good idea. but if your chip doesn't have an avalible hard serial (i.e arduino uno) then good luck with the code for two soft serials. 
soon i will post a james bond themed video of the results :).

use the "enroll" example in adafruit finger print library to flash you desired finger prints to the finger print sensor.
