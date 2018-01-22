type puppet;

module Browser = {
  type t;
  [@bs.send] external close : (t, unit) => Js.Promise.t(unit) = "";
};

[@bs.val] [@bs.module] external puppeteer : puppet = "";

[@bs.obj] external makeLaunchOption : (
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
) => _ = "";

[@bs.send] external launch : (puppet, Js.t({..})) => Js.Promise.t(Browser.t) = "";

[@bs.obj] external makeConnectOption : (
  ~ignoreHTTPSErrors: Js.boolean=?,
  ~browserWSEndpoint: string=?,
  unit
) => _ = "";

[@bs.send] external connect : (puppet, Js.t({..})) => Js.Promise.t(Browser.t) = "";

[@bs.send] external defaultArgs : (puppet, unit) => array(string) = "";

[@bs.send] external executablePath : (puppet, unit) => string = "";

