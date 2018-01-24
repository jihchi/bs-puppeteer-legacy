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
       Js.log("got browser");
       Puppeteer.Browser.close(browser, ());
     })
  |> Js.Promise.then_(() => {
       Js.log("browser closed");
       Js.Promise.resolve();
     })
  |> ignore;
});
