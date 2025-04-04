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

Receiving a response indicating user creation
```HTTP
POST /users HTTP/1.1
Host: example.com
Content-Type: application/json

{
  "firstName": "Brian",
  "lastName": "Smith",
  "email": "brian.smith@example.com"
}
```

After a successful user creatin, the 201 Created response will look like this:
```HTTP
POST /users HTTP/1.1
Host: example.com
Content-Type: application/json

{
  "firstName": "Brian",
  "lastName": "Smith",
  "email": "brian.smith@example.com"
}
```

* 202 Accepted 

The request has been received but processing has not been completed or may not have started. It is noncommittal, since there is no way in HTTP to later send an asynchronous response indicating the outcome of the request. It is intended for cases where another process or server handles the request, or for batch processing.

* 203 Non-Authoritative Information 

his response code means the returned metadata is not exactly the same as is available from the origin server, but is collected from a local or a third-party copy. This is mostly used for mirrors or backups of another resource. Except for that specific case, the [`200 OK`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/200) response is preferred to this status.

* 204 No Content

There is no content to send for this request, but the headers are useful. The user agent may update its cached headers for this resource with the new ones.

A 204 response is cacheable by default, and an Etag header in such cases. 

* 205 Resent Content

The HTTP 205 Reset Content successful response status code indicates that the request has been successfully processed and the client should rest the document view.

Note that the response must not include any content or the content-length header. The empty response may also be indicates using Transfer-encoding: Chucked header with an empty chunk. 

* 206 Partial Content

The HTTP **`206 Partial Content`** [successful response](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status#successful_responses) status code is sent in response to a [range request](https://developer.mozilla.org/en-US/docs/Web/HTTP/Guides/Range_requests). The response body contains the requested ranges of data as specified in the [`Range`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Headers/Range) header of the request.
The format of the response depends on the number of ranges requested. If a single range is requested, the [`Content-Type`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Headers/Content-Type) of the entire response is set to the type of the document, and a [`Content-Range`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Headers/Content-Range) is provided. If several ranges are requested, the [`Content-Type`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Headers/Content-Type) is set to `multipart/byteranges`, and each fragment covers one range, with its own [`Content-Range`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Headers/Content-Range) and [`Content-Type`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Headers/Content-Type) headers describing it.

* 207 Multi-status

The HTTP **`207 Multi-Status`** [successful response](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status#successful_responses) status code indicates a mixture of responses. This response is used exclusively in the context of Web Distributed Authoring and Versioning ([WebDAV](https://developer.mozilla.org/en-US/docs/Glossary/WebDAV)).

The response body is a `text/xml` or `application/xml` HTTP entity with a `multistatus` root element that lists individual response codes.

* 208 Already Reported

The HTTP **`208 Already Reported`** [successful response](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status#successful_responses) status code is used in a [`207 Multi-Status`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/207) response to save space and avoid conflicts. This response is used exclusively in the context of Web Distributed Authoring and Versioning ([WebDAV](https://developer.mozilla.org/en-US/docs/Glossary/WebDAV)).

If the same resource is requested several times (for example, as part of a collection) with different paths, only the first one is reported with [`200`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/200). Responses for all other bindings will report with this `208` status code, so no conflicts are created and the response stays shorter.

* 226 IM Used

The HTTP **`226 IM Used`** [successful response](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status#successful_responses) status code indicates that the server is returning a [delta](https://developer.mozilla.org/en-US/docs/Glossary/Delta) in response to a [`GET`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods/GET) request. It is used in the context of _HTTP delta encodings_.

IM stands for _instance manipulation_, which refers to the algorithm generating a _delta_. In delta encoding, a client sends a [`GET`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods/GET) request with two headers: `A-IM:`, which indicates a preference for a differencing algorithm, and [`If-None-Match`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Headers/If-None-Match), which specifies the version of a resource it has. The server responds with deltas relative to a given base document, rather than the document in full. This response uses the `226` status code, an `IM:` header that describes the differencing algorithm used, and may include a `Delta-Base:` header with the [`ETag`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Headers/ETag) matching the base document associated to the delta.

## Redirection Message

[`300 Multiple Choices`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/300)

In [agent-driven content negotiation](https://developer.mozilla.org/en-US/docs/Web/HTTP/Guides/Content_negotiation#agent-driven_negotiation), the request has more than one possible response and the user agent or user should choose one of them. There is no standardized way for clients to automatically choose one of the responses, so this is rarely used.

[`301 Moved Permanently`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/301)

The URL of the requested resource has been changed permanently. The new URL is given in the response.

Example response

```HTTP
HTTP/2 301
cache-control: max-age=2592000,public
location: /en-US/docs/Learn_web_development/Core/Scripting/Network_requests
content-type: text/plain; charset=utf-8
date: Fri, 19 Jul 2024 12:57:17 GMT
content-length: 97

Moved Permanently. Redirecting to /en-US/docs/Learn_web_development/Core/Scripting/Network_requests

```

[`302 Found`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/302)

This response code means that the URI of requested resource has been changed _temporarily_. Further changes in the URI might be made in the future, so the same URI should be used by the client in future requests.

Example request/response

```HTTP
GET /profile HTTP/1.1
Host: www.example.com

HTTP/1.1 302 Found
Location: https://www.example.com/new-profile-url
Content-Type: text/html; charset=UTF-8
Content-Length: 0

```

[`303 See Other`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/303)

The server sent this response to direct the client to get the requested resource at another URI with a [`GET`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods/GET) request.

This response code is often sent back as a result of [`PUT`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods/PUT) or [`POST`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods/POST) methods so the client may retrieve a confirmation, or view a representation of a real-world object (see [HTTP range-14](https://en.wikipedia.org/wiki/HTTPRange-14)). The method to retrieve the redirected resource is always [`GET`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods/GET).

Example of request/response on form submission 

```HTTP
POST /subscribe HTTP/1.1
Host: example.com
Content-Type: application/x-www-form-urlencoded
Content-Length: 50

name=Brian%20Smith&email=brian.smith%40example.com

HTTP/1.1 303 See Other
Location: https://www.example.com/confirmation/event/123
Content-Type: text/html; charset=UTF-8
Content-Length: 0
```
[`304 Not Modified`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/304)

This is used for caching purposes. It tells the client that the response has not been modified, so the client can continue to use the same [cached](https://developer.mozilla.org/en-US/docs/Web/HTTP/Guides/Caching) version of the response.

This response code is sent when the request is a [conditional](https://developer.mozilla.org/en-US/docs/Web/HTTP/Guides/Conditional_requests) [`GET`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods/GET) or [`HEAD`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods/HEAD) request with an [`If-None-Match`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Headers/If-None-Match) or an [`If-Modified-Since`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Headers/If-Modified-Since) header and the condition evaluates to 'false'. It confirms that the resource cached by the client is still valid and that the server would have sent a [`200 OK`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/200) response with the resource if the condition evaluated to 'true'. See [HTTP caching](https://developer.mozilla.org/en-US/docs/Web/HTTP/Guides/Caching) for more information.

Example of request/response to conditional requests

```BASH
curl --http1.1 -I --header 'If-Modified-Since: Tue, 21 Nov 2050 08:00:00 GMT' \
 https://developer.mozilla.org/en-US/
```

```HTTP
GET /en-US/ HTTP/1.1
Host: developer.mozilla.org
User-Agent: curl/8.7.1
Accept: */*
If-Modified-Since: Tue, 21 Nov 2050 08:00:00 GMT

GET /en-US/ HTTP/1.1
Host: developer.mozilla.org
User-Agent: curl/8.7.1
Accept: */*
If-Modified-Since: Tue, 21 Nov 2050 08:00:00 GMT

```

[`305 Use Proxy` Deprecated](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status#305_use_proxy)

Defined in a previous version of the HTTP specification to indicate that a requested response must be accessed by a proxy. It has been deprecated due to security concerns regarding in-band configuration of a proxy.

[`306 unused`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status#306_unused)

This response code is no longer used; but is reserved. It was used in a previous version of the HTTP/1.1 specification.

[`307 Temporary Redirect`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/307)

The server sends this response to direct the client to get the requested resource at another URI with the same method that was used in the prior request. This has the same semantics as the `302 Found` response code, with the exception that the user agent _must not_ change the HTTP method used: if a [`POST`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods/POST) was used in the first request, a `POST` must be used in the redirected request.

The HTTP **`307 Temporary Redirect`** [redirection response](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status#redirection_messages) status code indicates that the resource requested has been temporarily moved to the URL in the [`Location`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Headers/Location) header.

The difference between `307` and [`302`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/302) is that `307` guarantees that the client **will not change** the request method and body when the redirected request is made. With `302`, older clients incorrectly changed the method to [`GET`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods/GET). `307` and `302` responses are identical when the request method is [`GET`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods/GET).

Example of a request/response to a moved resource
```HTTP
GET /en-US/docs/AJAX HTTP/2
Host: developer.mozilla.org
User-Agent: curl/8.6.0
Accept: */*

HTTP/2 307
location: /en-US/docs/Learn_web_development/Core/Scripting/Network_requests
content-type: text/plain; charset=utf-8
date: Fri, 19 Jul 2024 12:57:17 GMT

```

[`308 Permanent Redirect`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/308)

This means that the resource is now permanently located at another URI, specified by the [`Location`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Headers/Location) response header. This has the same semantics as the `301 Moved Permanently` HTTP response code, with the exception that the user agent _must not_ change the HTTP method used: if a [`POST`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods/POST) was used in the first request, a `POST` must be used in the second request.

The request method and the body **will not be modified** by the client in the redirected request. A [`301 Moved Permanently`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/301) requires the request method and the body to remain unchanged when redirection is performed, but this is incorrectly handled by older clients to use the [`GET`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods/GET) method instead.

Example of a response to a moved resource

```HTTP
GET /featured HTTP/1.1
Host: www.example.org

HTTP/1.1 308 Permanent Redirect
Location: http://www.example.com/featured
Content-Length: 0
```

## Client Errors

[`400 Bad Request`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/400)

The server cannot or will not process the request due to something that is perceived to be a client error (e.g., malformed request syntax, invalid request message framing, or deceptive request routing).

Example of a request/response 
```HTTP
POST /users HTTP/1.1
Host: example.com
Content-Type: application/json
Content-Length: 38

{
  "email": "b@example.com
",
  "username": "b.smith"
}

HTTP/1.1 400 Bad Request
Content-Type: application/json
Content-Length: 71

{
  "error": "Bad request",
  "message": "Request body could not be read properly.",
}
```

[`401 Unauthorized`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/401)

Although the HTTP standard specifies "unauthorized", semantically this response means "*unauthenticated*". That is, the client must authenticate itself to get the requested response.

An example where expecting for authentication header:

```HTTP
GET /admin HTTP/1.1
Host: example.com

HTTP/1.1 401 Unauthorized
Date: Tue, 02 Jul 2024 12:18:47 GMT
WWW-Authenticate: Bearer

```

[`402 Payment Required`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/402)

The initial purpose of this code was for digital payment systems, however this status code is rarely used and no standard convention exists.

[`403 Forbidden`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/403)

The client does not have access rights to the content; that is, it is unauthorized, so the server is refusing to give the requested resource. Unlike `401 Unauthorized`, the client's identity is known to the server. 

[`404 Not Found`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/404)

The server cannot find the requested resource. In the browser, this means the URL is not recognized. In an API, this can also mean that the endpoint is valid but the resource itself does not exist. Servers may also send this response instead of `403 Forbidden` to hide the existence of a resource from an unauthorized client. This response code is probably the most well known due to its frequent occurrence on the web.

[`405 Method Not Allowed`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/405)

The [request method](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods) is known by the server but is not supported by the target resource. For example, an API may not allow `DELETE` on a resource, or the `TRACE` method entirely.

[`406 Not Acceptable`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/406)

This response is sent when the web server, after performing [server-driven content negotiation](https://developer.mozilla.org/en-US/docs/Web/HTTP/Guides/Content_negotiation#server-driven_content_negotiation), doesn't find any content that conforms to the criteria given by the user agent.

[`407 Proxy Authentication Required`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/407)

This is similar to `401 Unauthorized` but authentication is needed to be done by a proxy.

[`408 Request Timeout`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/408)

This response is sent on an idle connection by some servers, even without any previous request by the client. It means that the server would like to shut down this unused connection. This response is used much more since some browsers use HTTP pre-connection mechanisms to speed up browsing. Some servers may shut down a connection without sending this message.

[`409 Conflict`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/409)

This response is sent when a request conflicts with the current state of the server. In [WebDAV](https://developer.mozilla.org/en-US/docs/Glossary/WebDAV) remote web authoring, `409` responses are errors sent to the client so that a user might be able to resolve a conflict and resubmit the request.

[`410 Gone`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/410)

This response is sent when the requested content has been permanently deleted from server, with no forwarding address. Clients are expected to remove their caches and links to the resource. The HTTP specification intends this status code to be used for "limited-time, promotional services". APIs should not feel compelled to indicate resources that have been deleted with this status code.

[`411 Length Required`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/411)

Server rejected the request because the [`Content-Length`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Headers/Content-Length) header field is not defined and the server requires it.

[`412 Precondition Failed`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/412)

In [conditional requests](https://developer.mozilla.org/en-US/docs/Web/HTTP/Guides/Conditional_requests), the client has indicated preconditions in its headers which the server does not meet.

[`413 Content Too Large`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/413)

The request body is larger than limits defined by server. The server might close the connection or return an [`Retry-After`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Headers/Retry-After) header field.

[`414 URI Too Long`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/414)

The URI requested by the client is longer than the server is willing to interpret.

[`415 Unsupported Media Type`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/415)

The media format of the requested data is not supported by the server, so the server is rejecting the request.

[`416 Range Not Satisfiable`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/416)

The [ranges](https://developer.mozilla.org/en-US/docs/Web/HTTP/Guides/Range_requests) specified by the `Range` header field in the request cannot be fulfilled. It's possible that the range is outside the size of the target resource's data.

[`417 Expectation Failed`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/417)

This response code means the expectation indicated by the [`Expect`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Headers/Expect) request header field cannot be met by the server.

[`418 I'm a teapot`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/418)

The server refuses the attempt to brew coffee with a teapot.

[`421 Misdirected Request`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/421)

The request was directed at a server that is not able to produce a response. This can be sent by a server that is not configured to produce responses for the combination of scheme and authority that are included in the request URI.

[`422 Unprocessable Content`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/422) ([WebDAV](https://developer.mozilla.org/en-US/docs/Glossary/WebDAV))

The request was well-formed but was unable to be followed due to semantic errors.

[`423 Locked`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/423) ([WebDAV](https://developer.mozilla.org/en-US/docs/Glossary/WebDAV))

The resource that is being accessed is locked.

[`424 Failed Dependency`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/424) ([WebDAV](https://developer.mozilla.org/en-US/docs/Glossary/WebDAV))

The request failed due to failure of a previous request.

[`425 Too Early`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/425) Experimental

Indicates that the server is unwilling to risk processing a request that might be replayed.

[`426 Upgrade Required`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/426)

The server refuses to perform the request using the current protocol but might be willing to do so after the client upgrades to a different protocol. The server sends an [`Upgrade`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Headers/Upgrade) header in a 426 response to indicate the required protocol(s).

[`428 Precondition Required`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/428)

The origin server requires the request to be [conditional](https://developer.mozilla.org/en-US/docs/Web/HTTP/Guides/Conditional_requests). This response is intended to prevent the 'lost update' problem, where a client [`GET`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods/GET)s a resource's state, modifies it and [`PUT`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods/PUT)s it back to the server, when meanwhile a third party has modified the state on the server, leading to a conflict.

[`429 Too Many Requests`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/429)

The user has sent too many requests in a given amount of time ([rate limiting](https://developer.mozilla.org/en-US/docs/Glossary/Rate_limit)).

[`431 Request Header Fields Too Large`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/431)

The server is unwilling to process the request because its header fields are too large. The request may be resubmitted after reducing the size of the request header fields.

[`451 Unavailable For Legal Reasons`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/451)

The user agent requested a resource that cannot legally be provided, such as a web page censored by a government.