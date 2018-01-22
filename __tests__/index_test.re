open Jest;

describe("Expect Puppeteer", () => {
  open Expect;

  test("Dummy test", () => expect(1 + 2) |> toBe(3));

  let puppet = Puppeteer.puppeteer;

  test("defaultArgs", () => expect(
    Puppeteer.defaultArgs(puppet, ())
  ) |> toBe([|"headless"|]));

  test("executablePath", () => expect(
    Puppeteer.executablePath(puppet, ())
  ) |> toBe("chrome"));

  Puppeteer.launch(puppet, Puppeteer.makeLaunchOption())
  |> Js.Promise.then_(browser => {
    Js.log("got browser");
    Puppeteer.Browser.close(browser, ());
  })
  |> Js.Promise.then_(() => {
    Js.log("browser closed");
    Js.Promise.resolve(());
  })
  |> ignore;

});
