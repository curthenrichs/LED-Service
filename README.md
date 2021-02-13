# LED-Service
LED strip IR blaster for Arduino ESP8266 that exposes a RESTful service.

I built this to control a IR remote-controlled LED strip that my roommate had setup around the living room window of our apartment. At the time it was only really novelty where I would send postman requests to the device. I have not set this system back up since I moved but perhaps someday in the future it will get more use.

REST API and single client server module to expose LED controller functionality to the network. The functionality is broken down to setting state of the controller either through a raw byte command or sending a message to a valid route. The other functionality is server specific such as displaying documentation, routing, and state cache.

Note that this module makes no guarantee to the actual state of the LED controller.

The REST API is inspired and devloped after the LED Controller's IR remote. Thus the features on the remote are exposed as routes in the service.

## End-Points
The following is the HTTP REST API for the documentation and state of the LED Service.
 -  GET : / : Argument[none]
 -  GET : /routes : Argument[none]
 -  GET : /cached-state : Argument[none]

The following is the HTTP REST API for the LED Controller.
 -  GET, POST : /raw : Argument["raw"=<string>,"documentation"=<bool>]
 -  GET, POST : /brightness : Argument["brightness"=<string>,"documentation"=<bool>]
 -  GET, POST : /power : Argument["power"=<string>,"documentation"=<bool>]
 -  GET, POST : /function : Argument["function"=<string>,"documentation"=<bool>]
 -  GET, POST : /color :  Argument["color"=<string>,"documentation"=<bool>]
 
### Raw Command Bytes
The following strings in "x.." can be sent to directly control the LEDs. I wrote a set of end-points that makes this a bit nicer but kept this one for debugging purposes.

| Hex Value | Name            |
| --------- | --------------- |
| x04       | Brightness-Down |
| x05       | Brightness-Up   |
| x06       | Off             |
| x07       | On              |
| x08       | ~Green          |
| x09       | ~Red            |
| x0A       | ~Blue           |
| x0B       | ~White          |
| x0C       | ~Pea Green      |
| x0D       | ~Orange         |
| x0E       | ~Dark Orchid    |
| x0F       | Flash Function  |
| x10       | ~Cyan           |
| x11       | ~Dark Yellow    |
| x12       | ~Magenta        |
| x13       | Fade Function   |
| x14       | ~Light Blue     |
| x15       | ~Yellow         |
| x16       | ~Pink           |
| x17       | Strobe Function |
| x18       | ~Sky Blue       |
| x19       | ~Light Yellow   |
| x1A       | ~Purple         |
| x1B       | Smooth Function |

#### Function Details
Special functions have a unique property depending if one send the command after it is already in the selected mode. The following lists describes this behavior.

- Pressing Flash once does same action as smooth
- Pressing Flash twice strobes between color transitions of flash 1.
- Pressing Strobe once strobes currently displayed color.
- Pressing Strobe twice smoothly changes brightness of static color.
- Pressing fade once fades between all colors.
- Pressing fade twice fades only an rgb single cycling them.
- Pressing smooth once transitions between all colors abruptly.
- Pressing smooth twice flashes only an rgb single cycling them.

Brightness adjustment is measured in ticks. To move from brightest to least will take 9 ticks.

Brightness adjustment will act as expected for static colors. However when running a special function the brightness adjustment will alter the transition speed of the current function.
- During Flash increases/decreases transition speed (9 ticks)
- During Strobe increases/decreases transition speed (9 ticks)
- During Fade increases/decreases transition speed (9 ticks)
- During Smooth increases/decreases transition speed (9 ticks)

### Brightness Controls
The brightness arguement can be either be adjusted "up" or "down" one step at a time.

### Power Controls
The power arguement can be either set to "on" or "off" mimicing the signals as if they came from the remote. Note, if the remote is used in conjuction with this controller then power state cannot be ensured.

### Special Functions Controls
The function arguement can be set to "flash", "strobe", "fade", or "smooth". These functions were pre-programmed into the LED control box itself. If a different LED strip is used these may result in different behavior.

### Color Controls
The color argument can be set to "white", "red", "orange", "dark-yellow", "yellow", "light-yellow", "green", "pea-green", "cyan", "light-blue", "sky-blue", "blue", "dark-orchid", "purple", "magenta", or "pink".

## Fork Notes
This repo was forked from an alt account that I intend to delete in the near future.
