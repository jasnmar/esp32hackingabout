
import bottle

# This route is the main page of the Site
@bottle.route('/')
def index():

    #cookie = bottle.request.get_cookie("session")


    return "text"


bottle.debug(True)
bottle.run(host='0.0.0.0', port=8080)  # Start the webserver, listens
