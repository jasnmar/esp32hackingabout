
import bottle

# This route is the main page of the Site
@bottle.route('/')
def index():

    bottle.response.set_cookie("temperature", "True")
    #response.set_header()

    return "I'm on a boat "


bottle.debug(True)
bottle.run(host='0.0.0.0', port=8080)  # Start the webserver, listens
