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
 -  GET, POST : /raw : Argument["raw"=<byte>,"documentation"=<bool>]
 -  GET, POST : /brightness : Argument["brightness"=<string>,"documentation"=<bool>]
 -  GET, POST : /power : Argument["power"=<string>,"documentation"=<bool>]
 -  GET, POST : /function : Argument["function"=<string>,"documentation"=<bool>]
 -  GET, POST : /color :  Argument["color"=<string>,"documentation"=<bool>]

## Fork Notes
This repo was forked from an alt account that I intend to delete in the near future.
