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

test("length of defaultArgs shoud be 17", () =>
  expect(Puppeteer.defaultArgs(puppeteer, ())) |> toHaveLength(17)
);

test("executablePath should contains 'Chromium'", () =>
  expect(Puppeteer.executablePath(puppeteer, ()))
  |> toContainString("Chromium")
);

makeTestAsync(
  ~name="Browser > wsEndpoint",
  ~getData=
    browser => Js.Promise.resolve(Puppeteer.Browser.wsEndpoint(browser, ())),
  ~assertData=
    wsEndpoint =>
      expect(wsEndpoint)
      |> toContainString("ws://127.0.0.1:")
      |> Js.Promise.resolve
);

makeTestAsync(
  ~name="Browser > newPage",
  ~getData=
    browser => Js.Promise.resolve(Puppeteer.Browser.newPage(browser, ())),
  ~assertData=
    page =>
      expect(page)
      |> ExpectJs.toBeTruthy
      |> Js.Promise.resolve
);
