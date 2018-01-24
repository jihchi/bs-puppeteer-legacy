open Jest;

describe("Expect Puppeteer", () => {
  open Expect;
  test("Dummy test", () =>
    expect(1 + 2) |> toBe(3)
  );
  let puppeteer = Puppeteer.puppeteer;
  test("defaultArgs", () =>
    expect(Puppeteer.defaultArgs(puppeteer, ())) |> toBe([|"headless"|])
  );
  test("executablePath", () =>
    expect(Puppeteer.executablePath(puppeteer, ())) |> toBe("chrome")
  );
  Puppeteer.launch(puppeteer)
  |> Js.Promise.then_(browser => {
       test("Browser wsEndpoint", () =>
         expect(Puppeteer.Browser.wsEndpoint(browser, ())) |> toBe("ws")
       );
       Js.Promise.all2((
         Puppeteer.Browser.newPage(browser, ()),
         Js.Promise.resolve(browser)
       ));
     })
  |> Js.Promise.then_(((page, browser)) =>
       Js.Promise.all2((
         Puppeteer.Browser.pages(browser, ()),
         Js.Promise.resolve(browser)
       ))
     )
  |> Js.Promise.then_(((pages, browser)) => {
       test("Pages count", () =>
         expect(Array.length(pages)) |> toBe(2)
       );
       Js.Promise.resolve(browser);
     })
  |> Js.Promise.then_(browser => Puppeteer.Browser.close(browser, ()))
  |> ignore;
});
