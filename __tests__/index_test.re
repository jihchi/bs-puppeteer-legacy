open Jest;

open Expect;

let puppeteer = Puppeteer.puppeteer;

let makeTestAsync = (~name, ~getData, ~assertData) =>
  testPromise(name, () =>
    Js.Promise.(
      Puppeteer.launch(puppeteer)
      |> then_(browser => all2((resolve(browser), getData(browser))))
      |> then_(res => {
           let (browser, data) = res;
           all2((Puppeteer.Browser.close(browser, ()), resolve(data)));
         })
      |> then_(res => {
           let (_, data) = res;
           assertData(data);
         })
    )
  );

test(
  "Puppeteer.defaultArgs(): The default flags that Chromium will be launched with.",
  () =>
  expect(Puppeteer.defaultArgs(puppeteer, ())) |> toHaveLength(17)
);

test(
  "Puppeteer.executablePath(): A path where Puppeteer expects to find bundled Chromium.",
  () =>
  expect(Puppeteer.executablePath(puppeteer, ()))
  |> toContainString("chromium")
);

makeTestAsync(
  ~name="Browser.wsEndpoint(): Browser websocket url.",
  ~getData=
    browser => Js.Promise.resolve(Puppeteer.Browser.wsEndpoint(browser, ())),
  ~assertData=
    wsEndpoint =>
      expect(wsEndpoint)
      |> toContainString("ws://127.0.0.1:")
      |> Js.Promise.resolve
);

makeTestAsync(
  ~name="Browser.newPage(): Get a new Page object.",
  ~getData=
    browser => Js.Promise.resolve(Puppeteer.Browser.newPage(browser, ())),
  ~assertData=page => expect(page) |> ExpectJs.toBeTruthy |> Js.Promise.resolve
);

makeTestAsync(
  ~name=
    "Page.$(): The method runs document.querySelector within the page. (FAIL)",
  ~getData=
    browser =>
      Js.Promise.(
        Puppeteer.Browser.newPage(browser, ())
        |> then_(page => Puppeteer.Page.dollar(page, "#does-not-exists"))
      ),
  ~assertData=
    elementHandle =>
      expect(elementHandle) |> ExpectJs.toBeFalsy |> Js.Promise.resolve
);

makeTestAsync(
  ~name="Page.$(): The method runs document.querySelector within the page.",
  ~getData=
    browser =>
      Js.Promise.(
        Puppeteer.Browser.newPage(browser, ())
        |> then_(page => Puppeteer.Page.dollar(page, "body"))
      ),
  ~assertData=
    elementHandle =>
      expect(elementHandle) |> ExpectJs.toBeTruthy |> Js.Promise.resolve
);

makeTestAsync(
  ~name=
    "Page.content(): gets the full HTML contents of the page, including the doctype.",
  ~getData=
    browser =>
      Js.Promise.(
        Puppeteer.Browser.newPage(browser, ())
        |> then_(page => Puppeteer.Page.content(page, ()))
      ),
  ~assertData=
    content =>
      expect(content)
      |> ExpectJs.toBe("<html><head></head><body></body></html>")
      |> Js.Promise.resolve
);

makeTestAsync(
  ~name=
    "Page.$$(): The method runs document.querySelectorAll within the page.",
  ~getData=
    browser =>
      Js.Promise.(
        Puppeteer.Browser.newPage(browser, ())
        |> then_(page => Puppeteer.Page.dollarDollar(page, "html,body"))
      ),
  ~assertData=
    elementHandles =>
      expect(elementHandles) |> ExpectJs.toHaveLength(2) |> Js.Promise.resolve
);

makeTestAsync(
  ~name=
    "Page.$$eval(): This method runs document.querySelectorAll within the page and passes it as the first argument to pageFunction.",
  ~getData=
    browser =>
      Js.Promise.(
        Puppeteer.Browser.newPage(browser, ())
        |> then_(page => {
             let eval = [%raw
               {| function (elements) { return elements.length; } |}
             ];
             Puppeteer.Page.dollarDollarEval(page, "html,body", eval, [||]);
           })
      ),
  ~assertData=
    serializable => expect(serializable) |> toBe(2) |> Js.Promise.resolve
);

makeTestAsync(
  ~name=
    "Page.$eval(): This method runs document.querySelector within the page and passes it as the first argument to pageFunction.",
  ~getData=
    browser =>
      Js.Promise.(
        Puppeteer.Browser.newPage(browser, ())
        |> then_(page => {
             let eval = [%raw
               {| function (element) { return element.outerHTML; } |}
             ];
             Puppeteer.Page.dollarEval(page, "html", eval, [||]);
           })
      ),
  ~assertData=
    serializable =>
      expect(serializable)
      |> toBe("<html><head></head><body></body></html>")
      |> Js.Promise.resolve
);

makeTestAsync(
  ~name="Page.$x(): The method evluates the XPath expression.",
  ~getData=
    browser =>
      Js.Promise.(
        Puppeteer.Browser.newPage(browser, ())
        |> then_(page => Puppeteer.Page.dollarX(page, "/html/body"))
      ),
  ~assertData=
    elementHandles =>
      expect(elementHandles) |> toHaveLength(1) |> Js.Promise.resolve
);

makeTestAsync(
  ~name=
    "Page.addScriptTag(): Adds a <script> tag into the page with the desired url or content.",
  ~getData=
    browser =>
      Js.Promise.(
        Puppeteer.Browser.newPage(browser, ())
        |> then_(page =>
             all2((
               Puppeteer.Page.addScriptTag(
                 ~url=
                   "https://cdnjs.cloudflare.com/ajax/libs/jquery/3.3.1/jquery.min.js",
                 page
               ),
               resolve(page)
             ))
           )
        |> then_(((_elementHandle, page)) => Puppeteer.Page.content(page, ()))
      ),
  ~assertData=
    content =>
      expect(content)
      |> toBe(
           "<html><head><script src=\"https://cdnjs.cloudflare.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script></head><body></body></html>"
         )
      |> Js.Promise.resolve
);

makeTestAsync(
  ~name=
    "Page.addStyleTag(): Adds a <link rel=\"stylesheet\"> tag into the page with the desired url or a <style type=\"text/css\"> tag with the content.",
  ~getData=
    browser =>
      Js.Promise.(
        Puppeteer.Browser.newPage(browser, ())
        |> then_(page =>
             all2((
               Puppeteer.Page.addStyleTag(
                 ~url=
                   "https://cdnjs.cloudflare.com/ajax/libs/twitter-bootstrap/4.0.0/css/bootstrap.min.css",
                 page
               ),
               resolve(page)
             ))
           )
        |> then_(((_elementHandle, page)) => Puppeteer.Page.content(page, ()))
      ),
  ~assertData=
    content =>
      expect(content)
      |> toBe(
           "<html><head><link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/twitter-bootstrap/4.0.0/css/bootstrap.min.css\"></head><body></body></html>"
         )
      |> Js.Promise.resolve
);

makeTestAsync(
  ~name="Page.authenticate(): Provide credentials for http authentication.",
  ~getData=
    browser =>
      Js.Promise.(
        Puppeteer.Browser.newPage(browser, ())
        |> then_(page =>
             Puppeteer.Page.authenticate(
               page,
               Js.Null.return({"username": "foo", "password": "bar"})
             )
           )
      ),
  ~assertData=() => pass |> Js.Promise.resolve
);

makeTestAsync(
  ~name="Page.bringToFront(): Brings page to front (activates tab).",
  ~getData=
    browser =>
      Js.Promise.(
        Puppeteer.Browser.newPage(browser, ())
        |> then_(page => Puppeteer.Page.bringToFront(page, ()))
      ),
  ~assertData=() => pass |> Js.Promise.resolve
);

makeTestAsync(
  ~name=
    "Page.click(): This method fetches an element with selector, scrolls it into view if needed, and then uses page.mouse to click in the center of the element. If there's no element matching selector, the method throws an error.",
  ~getData=
    browser =>
      Js.Promise.(
        Puppeteer.Browser.newPage(browser, ())
        |> then_(page => Puppeteer.Page.click(page, "body", Js.undefined))
      ),
  ~assertData=() => pass |> Js.Promise.resolve
);

makeTestAsync(
  ~name="Page.coverage",
  ~getData=browser => Puppeteer.Browser.newPage(browser, ()),
  ~assertData=
    page => expect(page##coverage) |> ExpectJs.toBeTruthy |> Js.Promise.resolve
);

makeTestAsync(
  ~name="Page.deleteCookie()",
  ~getData=
    browser =>
      Js.Promise.(
        Puppeteer.Browser.newPage(browser, ())
        |> then_(page => Puppeteer.Page.deleteCookie(page, [||]))
      ),
  ~assertData=() => pass |> Js.Promise.resolve
);

makeTestAsync(
  ~name="Page.emulate(): Emulates given device metrics and user agent.",
  ~getData=
    browser =>
      Js.Promise.(
        Puppeteer.Browser.newPage(browser, ())
        |> then_(page =>
             all2((
               Puppeteer.Page.emulate(
                 page,
                 {
                   "viewport": {
                     "width": 320,
                     "height": 480,
                     "deviceScaleFactor": 2,
                     "isMobile": Js.true_,
                     "hasTouch": Js.true_,
                     "isLandscape": Js.true_
                   },
                   "userAgent": ""
                 }
               ),
               resolve(page)
             ))
           )
      ),
  ~assertData=
    (((), page)) =>
      Puppeteer.Page.viewport(page, ())
      |> expect
      |> ExpectJs.toMatchObject({
           "width": 320,
           "height": 480,
           "deviceScaleFactor": 2,
           "isMobile": Js.true_,
           "hasTouch": Js.true_,
           "isLandscape": Js.true_
         })
      |> Js.Promise.resolve
);

makeTestAsync(
  ~name=
    "Page.emulateMedia(): Changes the CSS media type of the page. The only allowed values are 'screen', 'print' and null. Passing null disables media emulation.",
  ~getData=
    browser =>
      Js.Promise.(
        Puppeteer.Browser.newPage(browser, ())
        |> then_(page => Puppeteer.Page.emulateMedia(page, "print"))
      ),
  ~assertData=() => pass |> Js.Promise.resolve
);

makeTestAsync(
  ~name=
    "Page.evaluate(): If the function, passed to the page.evaluate, returns a Promise, then page.evaluate would wait for the promise to resolve and return its value.",
  ~getData=
    browser =>
      Js.Promise.(
        Puppeteer.Browser.newPage(browser, ())
        |> then_(page => {
             let eval = [%raw
               {| function () { return Promise.resolve("ok"); } |}
             ];
             Puppeteer.Page.evaluate(page, eval, [||]);
           })
      ),
  ~assertData=
    serializable =>
      serializable
      |> Js.Json.decodeString
      |> Js.Option.getWithDefault("")
      |> expect
      |> toBe("ok")
      |> Js.Promise.resolve
);
