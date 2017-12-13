#!/usr/bin/env bash

CAP=$(xset q | grep Caps | tr -s " " | awk '{print $4}')

if [[ "$CAP" == "off" ]]
then
	notify-send 'Caps Lock' 'Disabled' -i /usr/share/icons/Adwaita/48x48/status/user-invisible.png
else
	notify-send 'Caps Lock' 'Enabled' -i /usr/share/icons/Adwaita/48x48/status/user-invisible.png 
fi
