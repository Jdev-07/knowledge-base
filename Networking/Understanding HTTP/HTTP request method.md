HTTP defines a set of **request methods** to indicate the purpose of the request and what is expected if the request is successful. Although they can also be nouns, these request methods are sometimes referred to as _HTTP verbs_. Each request method has its own semantics, but some characteristics are shared across multiple methods, specifically request methods can be [safe](https://developer.mozilla.org/en-US/docs/Glossary/Safe/HTTP), [idempotent](https://developer.mozilla.org/en-US/docs/Glossary/Idempotent), or [cacheable](https://developer.mozilla.org/en-US/docs/Glossary/Cacheable).

[`GET`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods/GET)

The `GET` method requests a representation of the specified resource. Requests using `GET` should only retrieve data and should not contain a request [content](https://developer.mozilla.org/en-US/docs/Glossary/HTTP_Content).

This is an example of request/response asking for the resource example.com/contact 
```HTTP
GET /contact HTTP/1.1
Host: example.com
User-Agent: curl/8.6.0
Accept: */*

HTTP/1.1 200 OK
Content-Type: text/html; charset=UTF-8
Date: Fri, 21 Jun 2024 14:18:33 GMT
Last-Modified: Thu, 17 Oct 2019 07:18:26 GMT
Content-Length: 1234

<!doctype html>
<!-- HTML content follows -->

```

[`HEAD`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods/HEAD)

The `HEAD` method asks for a response identical to a `GET` request, but without a response body.

The HEAD HTTP method requests the metadata of a resource in the form of headers that server would have sent if the GET method was used instead. 

A good example is creating a HEAD request with the curl command
```BASH
curl --head example.com
```

The curl command creates the request shown below and gets the response with a 200 OK

```HTTP
HEAD / HTTP/1.1
Host: example.com
User-Agent: curl/8.6.0
Accept: */*

HTTP/1.1 200 OK
Content-Type: text/html; charset=UTF-8
Date: Wed, 04 Sep 2024 10:33:11 GMT
Content-Length: 1234567

```

[`POST`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods/POST)

The `POST` method submits an entity to the specified resource, often causing a change in state or side effects on the server.

The difference between [`PUT`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods/PUT) and `POST` is that `PUT` is [idempotent](https://developer.mozilla.org/en-US/docs/Glossary/Idempotent): calling it once is no different from calling it several times successively (there are no _side_ effects). Successive identical `POST` requests may have additional effects, such as creating the same order several times.

The following is an example of URL-encoded form submission

```HTTP
POST /test HTTP/1.1
Host: example.com
Content-Type: application/x-www-form-urlencoded
Content-Length: 27

field1=value1&field2=value2
```

Also, here is an example of a Multipart form submission. The multipart/form-data encoding is used when a form includes files or a lot of data.
``` HTTP
POST /test HTTP/1.1
Host: example.com
Content-Type: multipart/form-data;boundary="delimiter12345"

--delimiter12345
Content-Disposition: form-data; name="field1"

value1
--delimiter12345
Content-Disposition: form-data; name="field2"; filename="example.txt"

value2
--delimiter12345--
```


[`PUT`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods/PUT)

The `PUT` method replaces all current representations of the target resource with the request [content](https://developer.mozilla.org/en-US/docs/Glossary/HTTP_Content).

Here are some examples.
Successfully creating a resource using a PUT request.

```HTTP
PUT /new.html HTTP/1.1
Host: example.com
Content-type: text/html
Content-length: 16

<p>New File</p>
```

If the target resource does not have a current representation and the PUT request successfully creates one, then the origin server must send a 201 - Created response

```HTTP
HTTP/1.1 201 Created
Content-Location: /new.html
```

If the target resource does have a current representation and the representation is successfully modified with the state in the request, the origin server must send either a 200 or a 204 no content to indicate successful completion of the request

[`DELETE`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods/DELETE)

The `DELETE` method deletes the specified resource. If the request is successful, there are several possible successful response status codes. 

Successfully deleting a resource.

```HTTP
DELETE /file.html HTTP/1.1
Host: example.com
```

a 204 No-Content response means the request was successful and no additional information needs to be sent back to the client. 

```HTTP
HTTP/1.1 204 No Content
Date: Wed, 04 Sep 2024 10:16:04 GMT
```

A 200 OK response means the request was successful and the response body includes a representation describing the outcome
```HTTP
HTTP/1.1 200 OK
Content-Type: text/html; charset=UTF-8
Date: Fri, 21 Jun 2024 14:18:33 GMT
Content-Length: 1234

<html>
  <body>
    <h1>File "file.html" deleted.</h1>
  </body>
</html>
```

A 202 Accepted response means the request has been accepted and will probably succeed, but the the resource has not yet been deleted by the server
```HTTP
HTTP/1.1 202 Accepted
Date: Wed, 26 Jun 2024 12:00:00 GMT
Content-Type: text/html; charset=UTF-8
Content-Length: 1234

<html>
  <body>
    <h1>Deletion of "file.html" accepted.</h1>
    <p>See <a href="http://example.com/tasks/123/status">the status monitor</a> for details.</p>
  </body>
</html>
```

[`CONNECT`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods/CONNECT)

The `CONNECT` method establishes a tunnel to the server identified by the target resource.

[`OPTIONS`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods/OPTIONS)

The `OPTIONS` method describes the communication options for the target resource.
This can be used to test the allowed HTTP methods for a request, or to determine whether a request would succeed when making a CORS preflighted request. A client can specify a URL with this method, or an asterisk (`*`) to refer to the entire server.

[`TRACE`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods/TRACE)

The `TRACE` method performs a message loop-back test along the path to the target resource.

[`PATCH`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods/PATCH)

The `PATCH` method applies partial modifications to a resource. PATCH is somewhat analogous to the "update" concept found in CRUD.
In comparison with [`PUT`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods/PUT), a `PATCH` serves as a set of instructions for modifying a resource, whereas `PUT` represents a complete replacement of the resource. A `PUT` request is always [idempotent](https://developer.mozilla.org/en-US/docs/Glossary/Idempotent) (repeating the same request multiple times results in the resource remaining in the same state), whereas a `PATCH` request may not always be idempotent. For instance, if a resource includes an auto-incrementing counter, a `PUT` request will overwrite the counter (since it replaces the entire resource), but a `PATCH` request may not.

Like [`POST`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods/POST), a `PATCH` request can potentially have side effects on other resources.

Example. Assume there is a resource on the server representing a user with a numeric ID in the following format:
```JSON
{
  "firstName": "Example",
  "LastName": "User",
  "userId": 123,
  "signupDate": "2024-09-09T21:48:58Z",
  "status": "active",
  "registeredDevice": {
    "id": 1,
    "name": "personal",
    "manufacturer": {
      "name": "Hardware corp"
    }
  }
}

```

Instead of sending a JSON object to fully overwrite a resource, a `PATCH` modifies only specific parts of the resource. This request updates the `status` field:
```HTTP
PATCH /users/123 HTTP/1.1
Host: example.com
Content-Type: application/json
Content-Length: 27
Authorization: Bearer ABC123

{
  "status": "suspended"
}

```

The interpretation and authentication of the `PATCH` request depend on the implementation. Success can be indicated by any of the [successful response status codes](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status#successful_responses). In this example, a [`204 No Content`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status/204) is used as there's no need to transmit a body with additional context about the operation. An [`ETag`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Headers/ETag) is provided so the caller can perform a [conditional request](https://developer.mozilla.org/en-US/docs/Web/HTTP/Guides/Conditional_requests) in future: