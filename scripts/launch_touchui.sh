#!/bin/bash
DISPLAY=:0 chromium-browser --kiosk --disk-cache-dir=/dev/null --disk-cache-size=1 --media-cache-size=1 http://touch.pi.local/