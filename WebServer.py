
import bottle

# This route is the main page of the Site
@bottle.route('/')
def index():

    #cookie = bottle.request.get_cookie("session")
    #response.set_header()

    return "Hello World!!!\nI can write 2 lines!!!"


bottle.debug(True)
bottle.run(host='0.0.0.0', port=8080)  # Start the webserver, listens
