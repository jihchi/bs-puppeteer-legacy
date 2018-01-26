open Jest;

open Expect;

let puppeteer = Puppeteer.puppeteer;

test("length of defaultArgs shoud be 17", () =>
  expect(Puppeteer.defaultArgs(puppeteer, ())) |> toHaveLength(17)
);

test("executablePath should contains 'Chromium'", () =>
  expect(Puppeteer.executablePath(puppeteer, ()))
  |> toContainString("Chromium")
);

testPromise("Browser > wsEndpoint", () =>
  Js.Promise.(
    Puppeteer.launch(puppeteer)
    |> then_(browser =>
         all2((
           resolve(browser),
           resolve(Puppeteer.Browser.wsEndpoint(browser, ()))
         ))
       )
    |> then_(res => {
         let (browser, wsEndpoint) = res;
         all2((Puppeteer.Browser.close(browser, ()), resolve(wsEndpoint)));
       })
    |> then_(res => {
         let (_, wsEndpoint) = res;
         expect(wsEndpoint) |> toContainString("ws://127.0.0.1:") |> resolve;
       })
  )
);
