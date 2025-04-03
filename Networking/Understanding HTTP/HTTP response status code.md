HTTP response status codes indicate whether a specific HTTP request has been successfully completed. Response are grouped in five classes:

* Informational responses: 100 - 199
* Successful responses: 200 - 299
* Redirection messages: 300 - 399
* Client error responses: 400 - 499
* Server error response: 500 - 599
## Informational responses

* [`100 Continue`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/100)

This interim response indicates that the client should continue the request or ignore the response if the request is already finished.

* [`101 Switching Protocols`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/101)

This code is sent in response to an [`Upgrade`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Headers/Upgrade) request header from the client and indicates the protocol the server is switching to.

* [`102 Processing`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/102) Deprecated

This code was used in [WebDAV](https://developer.mozilla.org/en-US/docs/Glossary/WebDAV) contexts to indicate that a request has been received by the server, but no status was available at the time of the response.

* [`103 Early Hints`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/103)

This status code is primarily intended to be used with the [`Link`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Headers/Link) header, letting the user agent start [preloading](https://developer.mozilla.org/en-US/docs/Web/HTML/Attributes/rel/preload) resources while the server prepares a response or [preconnect](https://developer.mozilla.org/en-US/docs/Web/HTML/Attributes/rel/preconnect) to an origin from which the page will need resources.

## Successful responses

* 200 OK

The request succeeded. The result and meaning of "success" depends on the HTTP method:

GET: The resource has been fetched and transmitted in message body.
HEAD: Representation headers are included in the message body. 
PUT or POST: The resource describing the results of the actions is transmitted in the message body.
TRACE: The message body contains the request as received by the server.

* 201 Created

The request succeeded, and a new resource was created as a result. This is typically the response sent after [`POST`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods/POST) requests, or some [`PUT`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods/PUT) requests.

* 202 Accepted 

The request has been received but not yet acted upon. It is noncommittal, since there is no way in HTTP to later send an asynchronous response indicating the outcome of the request. It is intended for cases where another process or server handles the request, or for batch processing.