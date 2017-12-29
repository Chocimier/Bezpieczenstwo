#!/usr/bin/env python3
from bank.wsgi import application
from flup.server.fcgi import WSGIServer
WSGIServer(application).run()
