from django.http import HttpResponse

import os
import tempfile
import time
import urllib.error
import urllib.request

TARGET_HOST = 'pl.wikipedia.org'
dropped_headers = ['Connection', 'Content-Length', 'Content-Type', 'Date', 'Keep-Alive', 'Proxy-Authenticate', 'Proxy-Authorization', 'TE', 'Trailers', 'Transfer-Encoding', 'Upgrade']

def traincase(word):
    return '-'.join(map(lambda x: x.title(), word.split('_')))

def address(request):
    addr = '{}://{}{}'.format(request.scheme, TARGET_HOST, request.path)
    query = request.META['QUERY_STRING']
    if query:
        addr += '?' + query
    return addr

def request_to_target(request):
    addr = address(request)
    target_request = urllib.request.Request(addr)
    for key in request.META:
        if key.startswith('HTTP_') and key != 'HTTP_HOST':
            target_request.add_header(traincase(key[5:]), request.META[key])
            print(traincase(key[5:]) + ': ' + request.META[key])
    return target_request

def response(target_response):
    resp = HttpResponse(target_response.read(), content_type=target_response.getheader('Content-Type'))
    for header in target_response.info():
        if header not in dropped_headers:
            resp[header] = target_response.info()[header]
            print(header + ' -> ' + target_response.info()[header])
    return resp

def log(request):
    if request.body:
        handle = tempfile.mkstemp(prefix='{}-'.format(time.time()), dir=os.getcwd())[0]
        f = os.fdopen(handle, mode='wb')
        f.write(address(request).encode())
        f.write('\n'.encode())
        f.write(request.body)
        f.close()

def proxy(request):
    log(request)
    req = request_to_target(request)
    try:
        target_response = urllib.request.urlopen(req)
    except urllib.error.HTTPError as e:
        return HttpResponse(status=e.code)
    resp = response(target_response)
    return resp

