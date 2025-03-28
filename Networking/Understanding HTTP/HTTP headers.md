HTTP headers let the client and the server pass additional information with a message in a request or response 

Headers can be grouped according to their contexts:

### Requests headers

Contain more information about the resource to be fetched, or the client requesting the resource.

A request header is an HTTP header that can be used in an HTTP request to provide information about the request context , so that can tailor the response. 

Not all headers that can appear in a request are referred to as request headers by the specification. For example, the Content-Type header is referred to as a representation header.

The HTTP message below shows a few request headers after a GET request.

```HTTP
GET /home.html HTTP/1.1
Host: developer.mozilla.org
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.9; rv:50.0) Gecko/20100101 Firefox/50.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate, br
Referer: https://developer.mozilla.org/testpage.html
Connection: keep-alive
Upgrade-Insecure-Requests: 1
If-Modified-Since: Mon, 18 Jul 2016 02:36:04 GMT
If-None-Match: "c561c68d0ba92bbeb8b0fff2a9199f722e3a621a"
Cache-Control: max-age=0

```

#### Response Header

A response header is an HTTP header that can be used in an HTTP response and that does not relate to the content of the message. Response headers, like Age, Location or Server are used to give a more detailed context of the response

Not all headers appearing in a response are categorized as response headers by the specification. The following shows a few response and presentation headers after a get request. 

```HTTP
200 OK
Access-Control-Allow-Origin: *
Connection: Keep-Alive
Content-Encoding: gzip
Content-Type: text/html; charset=utf-8
Date: Mon, 18 Jul 2016 16:06:00 GMT
Etag: "c561c68d0ba92bbeb8b0f612a9199f722e3a621a"
Keep-Alive: timeout=5, max=997
Last-Modified: Mon, 18 Jul 2016 02:36:04 GMT
Server: Apache
Set-Cookie: my-key=my value; expires=Mon, 17-Jul-2017 16:06:00 GMT; Max-Age=31449600; Path=/; secure
Transfer-Encoding: chunked
Vary: Cookie, Accept-Encoding
X-Backend-Server: developer2.webapp.scl3.mozilla.com
X-Cache-Info: not cacheable; meta data too large
X-kuma-revision: 1085259
x-frame-options: DENY

```

#### Representation header

A representation header is an HTTP header that describes how to interpret data contained in the message. 

For example. the content in a particular message might be encoded for transport, the whole resource might be formatted as a particular media type such XML, JSON, HTML or Markdown. localized to a particular written language or geographical region, and/or compressed using a particular algorithm. The representation headers allow the underlying data to be extracted or understood. The underlying resource is semantically the same in each case, but is representation is different. 

While representations are different forms of resources, representations can themselves also be transmitted in various forms.

Clients specify the forms that they prefer to be sent during Content Negotiation (using Accept-* headers), and the representation header tell the client the form of the selected representation they received

Representation headers may be present in both HTTP request and response message with various method. If sent as a response to a HEAD request, they describe the body content representation that would be selected if the resource was requested with a get request. 

Representation headers include
- Content-Length 
- Content-Range
- Content-Type
- Content-Encoding 
- Content-Location
- Content-Language
- Validators used in conditional request, such as:
- Last-Modified
- ETag

#### Payload header

A payload header is an HTTP header that describes the payload information related to safe transport and reconstruction of the original resource representation, from one or more messages. This includes information like the length of the message payload, which is part of the resource is carried in the payload, any encoding applied for transport, message integrity checks etc. 

Payload headers may be present in both HTTP request and response messages. 

The payload headers include: Content-Length, Content-Range, Trailer and Transfer-Encoding. 

### HTPP headers types

### Authentication

**WWW-Authenticate:** Defines the authentication method that should be used to access a resources

**Proxy-Authenticate:** Defines the authentication method that should be used to access a resource behind proxy server. 