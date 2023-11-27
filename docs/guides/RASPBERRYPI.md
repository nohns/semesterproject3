# Setup of Raspberry Pi

## Flashing

1. Download `Raspberry Pi OS imager` from this link: https://www.raspberrypi.com/software/
2. Run `Raspberry Pi OS imager` and insert the MicroSD card for flashing.
3. Choose the appropriate OS (Raspberry Pi OS 64-bit  for most recent boards RPi 3 and forwards)
4. Configure the board, by enabling SSH, set the username and password (write them down otherwise you forget them). Also, setup the WiFi connection.
5. Flash it!
6. Eject the MicroSD card and put it in the Raspberry pi, and try powering it on. 

## Accessing the Raspberry pi over SSH

For downloading source files and further configuration on the Raspberry Pi, we need to SSH into it, with the credentials created previously.

1. Power on the Raspberry Pi
2. Go to a computer on the same WiFi as the Raspberry Pi
3. Open a terminal/git bash and write `ssh <username>@raspberrypi.local`. You will be prompted for the credentials, so enter those.

You can now run commands on the Raspberry Pi!

## Installing Node 

>Might not be needed, as we perhaps have to host the UI on the PC.

Follow this guide on installing node via `apy`:
https://pimylifeup.com/raspberry-pi-nodejs/

## FAQ:

### Open the browser on the touchscreen via Terminal

`DISPLAY=:0 chromium-browser --kiosk http://172.20.10.2:5173/`

>NOTICE: Here the IP probably has to be changed to match where the UI is hosted 
