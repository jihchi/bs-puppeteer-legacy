open Jest;

describe("Expect Puppeteer", () => {
  open Expect;
  let puppeteer = Puppeteer.puppeteer;
  test("length of defaultArgs shoud be 17", () =>
    expect(Puppeteer.defaultArgs(puppeteer, ())) |> toHaveLength(17)
  );
  test("executablePath should contains 'Chromium'", () =>
    expect(Puppeteer.executablePath(puppeteer, ()))
    |> toContainString("Chromium")
  );
  describe("Browser", ()
    /* Puppeteer.launch(puppeteer) */
    /* Puppeteer.Browser.close(browser^, ()) */
    /* |> toContainString("ooo") */
    /* expect(Puppeteer.Browser.wsEndpoint(browser^, ())) */
    =>
      ignore()
    );
});
