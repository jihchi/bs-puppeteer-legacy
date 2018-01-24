module Browser = {
  type t;
  [@bs.send] external close : (t, unit) => Js.Promise.t(unit) = "";
};

module Puppeteer = {
  type t;
  [@bs.val] [@bs.module] external puppeteer : t = "";
  [@bs.obj]
  external makeLaunchOption :
    (
      ~ignoreHTTPSErrors: Js.boolean=?,
      ~headless: Js.boolean=?,
      ~executablePath: string=?,
      ~slowMo: int=?,
      ~args: array(string)=?,
      ~ignoreDefaultArgs: Js.boolean=?,
      ~handleSIGINT: Js.boolean=?,
      ~handleSIGTERM: Js.boolean=?,
      ~handleSIGHUP: Js.boolean=?,
      ~timeout: int=?,
      ~dumpio: Js.boolean=?,
      ~userDataDir: string=?,
      ~env: Js.t({..})=?,
      ~devtools: Js.boolean=?,
      unit
    ) =>
    _ =
    "";
  [@bs.send] external launch : (t, Js.t({..})) => Js.Promise.t(Browser.t) = "";
  [@bs.obj]
  external makeConnectOption :
    (~ignoreHTTPSErrors: Js.boolean=?, ~browserWSEndpoint: string=?, unit) => _ =
    "";
  [@bs.send]
  external connect : (t, Js.t({..})) => Js.Promise.t(Browser.t) = "";
  [@bs.send] external defaultArgs : (t, unit) => array(string) = "";
  [@bs.send] external executablePath : (t, unit) => string = "";
};

let puppeteer = Puppeteer.puppeteer;

let defaultArgs = Puppeteer.defaultArgs;

let executablePath = Puppeteer.executablePath;

let launch =
    (
      ~ignoreHTTPSErrors: option(Js.boolean)=?,
      ~headless: option(Js.boolean)=?,
      ~executablePath: option(string)=?,
      ~slowMo: option(int)=?,
      ~args: option(array(string))=?,
      ~ignoreDefaultArgs: option(Js.boolean)=?,
      ~handleSIGINT: option(Js.boolean)=?,
      ~handleSIGTERM: option(Js.boolean)=?,
      ~handleSIGHUP: option(Js.boolean)=?,
      ~timeout: option(int)=?,
      ~dumpio: option(Js.boolean)=?,
      ~userDataDir: option(string)=?,
      ~env: option(Js.t({..}))=?,
      ~devtools: option(Js.boolean)=?,
      puppeteer
    ) =>
  Puppeteer.launch(
    puppeteer,
    Puppeteer.makeLaunchOption(
      ~ignoreHTTPSErrors?,
      ~headless?,
      ~executablePath?,
      ~slowMo?,
      ~args?,
      ~ignoreDefaultArgs?,
      ~handleSIGINT?,
      ~handleSIGTERM?,
      ~handleSIGHUP?,
      ~timeout?,
      ~dumpio?,
      ~userDataDir?,
      ~env?,
      ~devtools?,
      ()
    )
  );

let connect =
    (
      ~ignoreHTTPSErrors: option(Js.boolean)=?,
      ~browserWSEndpoint: option(string)=?,
      puppeteer
    ) =>
  Puppeteer.connect(
    puppeteer,
    Puppeteer.makeConnectOption(~ignoreHTTPSErrors?, ~browserWSEndpoint?, ())
  );
