type puppeteerFunction = unit => Js.Promise.t(unit);

type viewport = {
  .
  width: int,
  height: int,
  deviceScaleFactor: int,
  isMobile: Js.boolean,
  hasTouch: Js.boolean,
  isLandscape: Js.boolean
};

type cookie = {
  .
  name: string,
  value: string,
  domain: string,
  path: string,
  expires: float,
  httpOnly: Js.boolean,
  secure: Js.boolean,
  session: Js.boolean,
  sameSite: string
};

module Tracing = {
  type t;
};

module Touchscreen = {
  type t;
};

module Buffer = {
  type t;
};

module Mouse = {
  type t;
};

module JSHandle = {
  type t;
};

type args =
  | Serializable(Js.Json.t)
  | JSHandle(JSHandle.t);

module Keyboard = {
  type t;
};

module Coverage = {
  type t;
};

module ElementHandle = {
  type t = {. [@bs.meth] "toString": unit => string};
};

module Response = {
  type t;
};

module Request = {
  type t;
};

module Frame = {
  type t;
};

module Error = {
  type t;
};

module Dialog = {
  type t;
};

module ConsoleMessage = {
  type t;
};

module Target = {
  type t;
};

module Page = {
  type t = {
    .
    touchscreen: Touchscreen.t,
    tracing: Tracing.t
  };
  type tagOptions = {
    .
    "content": Js.undefined(string),
    "path": Js.undefined(string),
    "url": string
  };
  [@bs.obj]
  external makeTagOptions :
    (~url: string, ~path: string=?, ~content: string=?, unit) => _ =
    "";
  [@bs.send.pipe : t]
  external on :
    (
    [@bs.string]
    [
      | `console(ConsoleMessage.t => unit)
      | `dialog(Dialog.t => unit)
      | `error(Error.t => unit)
      | `frameattached(Frame.t => unit)
      | `framedetached(Frame.t => unit)
      | `framenavigated(Frame.t => unit)
      | `load(unit => unit)
      | `metrics(
          {
            .
            title: string,
            metrics: Js.Dict.t(float)
          } =>
          unit
        )
      | `pageerror(string => unit)
      | `request(Request.t => unit)
      | `requestfailed(Request.t => unit)
      | `requestfinished(Request.t => unit)
      | `response(Response.t => unit)
    ]
    ) =>
    Js.Promise.t(unit) =
    "";
  [@bs.send]
  external dollar : (t, string) => Js.Promise.t(option(ElementHandle.t)) = "$";
  [@bs.send]
  external dollarDollar : (t, string) => Js.Promise.t(array(ElementHandle.t)) =
    "$$";
  [@bs.send]
  external dollarDollarEval :
    (t, string, unit => unit, [@bs.splice] array(args)) => Js.Promise.t('a) =
    "$$eval";
  [@bs.send]
  external dollarEval :
    (t, string, unit => unit, [@bs.splice] array(args)) => Js.Promise.t('a) =
    "$eval";
  [@bs.send]
  external dollarX : (t, string) => Js.Promise.t(array(ElementHandle.t)) =
    "$x";
  [@bs.send]
  external _addScriptTag : (t, tagOptions) => Js.Promise.t(ElementHandle.t) =
    "addScriptTag";
  let addScriptTag =
      (~url: string, ~path: option(string)=?, ~content: option(string)=?, t) =>
    _addScriptTag(t, makeTagOptions(~url, ~path?, ~content?, ()));
  [@bs.send]
  external _addStyleTag : (t, tagOptions) => Js.Promise.t(ElementHandle.t) =
    "addStyleTag";
  let addStyleTag =
      (~url: string, ~path: option(string)=?, ~content: option(string)=?, t) =>
    _addStyleTag(t, makeTagOptions(~url, ~path?, ~content?, ()));
  [@bs.send]
  external authenticate :
    (
      t,
      Js.Null.t({
        .
        "username": string,
        "password": string
      })
    ) =>
    Js.Promise.t(unit) =
    "";
  [@bs.send] external bringToFront : (t, unit) => Js.Promise.t(unit) = "";
  [@bs.send]
  external click :
    (
      t,
      string,
      Js.undefined({
        .
        "button": string,
        "clickCount": int,
        "delay": int
      })
    ) =>
    Js.Promise.t(unit) =
    "";
  [@bs.send] external close : (t, unit) => Js.Promise.t(unit) = "";
  [@bs.send] external content : (t, unit) => Js.Promise.t(string) = "";
  [@bs.send] [@bs.splice]
  external cookies : (t, array(string)) => Js.Promise.t(array(cookie)) = "";
  [@bs.send] external coverage : (t, unit) => Coverage.t = "";
  [@bs.send] [@bs.splice]
  external deleteCookie : (t, array(cookie)) => Js.Promise.t(unit) = "";
  [@bs.send]
  external emulate :
    (
      t,
      {
        .
        viewport: viewport,
        userAgent: string
      }
    ) =>
    Js.Promise.t(unit) =
    "";
  [@bs.send]
  external emulateMedia : (t, Js.Nullable.t(string)) => Js.Promise.t(unit) =
    "";
  [@bs.send]
  external evaluate :
    (t, unit => unit, [@bs.splice] array(args)) => Js.Promise.t(Js.Json.t) =
    "";
  [@bs.send]
  external evaluateHandle :
    (t, unit => unit, [@bs.splice] array(args)) => Js.Promise.t(JSHandle.t) =
    "";
  [@bs.send]
  external evaluateOnNewDocument :
    (t, unit => unit, [@bs.splice] array(args)) => Js.Promise.t(unit) =
    "";
  [@bs.send]
  external exposeFunction :
    (t, string, puppeteerFunction) => Js.Promise.t(unit) =
    "";
  [@bs.send] external focus : (t, string) => Js.Promise.t(unit) = "";
  [@bs.send] external frames : (t, unit) => array(Frame.t) = "";
  [@bs.send]
  external goBack :
    (
      t,
      {
        .
        timeout: int,
        waitUntil: array(string)
      }
    ) =>
    Js.Promise.t(option(Response.t)) =
    "";
  [@bs.send]
  external goForward :
    (
      t,
      {
        .
        timeout: int,
        waitUntil: array(string)
      }
    ) =>
    Js.Promise.t(option(Response.t)) =
    "";
  [@bs.send]
  external goto :
    (
      t,
      string,
      {
        .
        timeout: int,
        waitUntil: array(string)
      }
    ) =>
    Js.Promise.t(option(Response.t)) =
    "";
  [@bs.send] external hover : (t, string) => Js.Promise.t(unit) = "";
  [@bs.send] external keyboard : (t, unit) => Keyboard.t = "";
  [@bs.send] external mainFrame : (t, unit) => Frame.t = "";
  /* TODO: Upper case */
  [@bs.send]
  external metrics :
    (t, unit) =>
    Js.Promise.t({
      .
      timestamp: float,
      documents: float,
      frames: float,
      jSEventListeners: float,
      nodes: float,
      layoutCount: float,
      recalcStyleCount: float,
      layoutDuration: float,
      recalcStyleDuration: float,
      scriptDuration: float,
      taskDuration: float,
      jSHeapUsedSize: float,
      jSHeapTotalSize: float
    }) =
    "";
  [@bs.send] external mouse : (t, unit) => Js.Promise.t(Mouse.t) = "";
  [@bs.send]
  external pdf :
    (
      t,
      {
        .
        path: string,
        scale: int,
        displayHeaderFooter: Js.boolean,
        headerTemplate: string,
        footerTemplate: string,
        printBackground: Js.boolean,
        landscape: Js.boolean,
        pageRanges: string,
        format: string,
        width: string,
        height: string,
        margin: {
          .
          top: string,
          right: string,
          bottom: string,
          left: string
        }
      }
    ) =>
    Js.Promise.t(Buffer.t) =
    "";
  [@bs.send]
  external queryObjects : (t, JSHandle.t) => Js.Promise.t(JSHandle.t) = "";
  [@bs.send]
  external reload :
    (
      t,
      {
        .
        timeout: int,
        waitUntil: array(string)
      }
    ) =>
    Js.Promise.t(Response.t) =
    "";
  [@bs.send]
  external screenshot :
    (
      t,
      array({
        .
        path: string,
        type_: string,
        quality: int,
        fullPage: Js.boolean,
        clip: {
          .
          x: int,
          y: int,
          width: int,
          height: int
        },
        omitBackground: Js.boolean
      })
    ) =>
    Js.Promise.t(Buffer.t) =
    "";
  [@bs.send]
  external select :
    (t, string, [@bs.splice] array(string)) => Js.Promise.t(array(string)) =
    "";
  [@bs.send] external setContent : (t, string) => Js.Promise.t(unit) = "";
  [@bs.send]
  external setCookie : (t, array(cookie)) => Js.Promise.t(unit) = "";
  [@bs.send] external setDefaultNavigationTimeout : (t, int) => unit = "";
  [@bs.send]
  external setExtraHTTPHeaders : (t, {..}) => Js.Promise.t(unit) = "";
  [@bs.send]
  external setJavaScriptEnabled : (t, Js.boolean) => Js.Promise.t(unit) = "";
  [@bs.send]
  external setOfflineMode : (t, Js.boolean) => Js.Promise.t(unit) = "";
  [@bs.send]
  external setRequestInterception : (t, Js.boolean) => Js.Promise.t(unit) = "";
  [@bs.send] external setUserAgent : (t, string) => Js.Promise.t(unit) = "";
  [@bs.send] external setViewport : (t, viewport) => Js.Promise.t(unit) = "";
  [@bs.send] external tap : (t, string) => Js.Promise.t(unit) = "";
  [@bs.send] external target : (t, unit) => Target.t = "";
  [@bs.send] external title : (t, unit) => Js.Promise.t(string) = "";
  [@bs.send]
  external type_ : (t, string, string, {. delay: int}) => Js.Promise.t(unit) =
    "";
  [@bs.send] external url : (t, unit) => string = "";
  [@bs.send] external viewport : (t, unit) => viewport = "";
  [@bs.send]
  external waitFor :
    (
      t,
      [@bs.unwrap] [ | `Str(string) | `Int(int) | `Fn(unit => unit)],
      {..},
      [@bs.splice] array(args)
    ) =>
    Js.Promise.t(JSHandle.t) =
    "";
  [@bs.send]
  external waitForFunction :
    (
      t,
      unit => unit,
      {
        .
        polling: [@bs.unwrap] [ | `Str(string) | `Int(int)],
        timeout: int
      },
      [@bs.splice] array(args)
    ) =>
    Js.Promise.t(JSHandle.t) =
    "";
  [@bs.send]
  external waitForNavigation :
    (
      t,
      {
        .
        timeout: int,
        waitUntil: array(string)
      }
    ) =>
    Js.Promise.t(Response.t) =
    "";
  external waitForSelector :
    (
      t,
      string,
      {
        .
        timeout: int,
        waitUntil: array(string)
      }
    ) =>
    Js.Promise.t(ElementHandle.t) =
    "";
};

module Browser = {
  type t;
  [@bs.send.pipe : t]
  external on :
    (
    [@bs.string]
    [
      | `disconnected(unit => unit)
      | `targetchanged(Target.t => unit)
      | `targetcreated(Target.t => unit)
      | `targetdestroyed(Target.t => unit)
    ]
    ) =>
    Js.Promise.t(unit) =
    "";
  [@bs.send] external close : (t, unit) => Js.Promise.t(unit) = "";
  [@bs.send] external disconnect : (t, unit) => unit = "";
  [@bs.send] external newPage : (t, unit) => Js.Promise.t(Page.t) = "";
  [@bs.send] external pages : (t, unit) => Js.Promise.t(array(Page.t)) = "";
  [@bs.send] external targets : (t, unit) => array(Page.t) = "";
  [@bs.send] external userAgent : (t, unit) => Js.Promise.t(string) = "";
  [@bs.send] external version : (t, unit) => Js.Promise.t(string) = "";
  [@bs.send] external wsEndpoint : (t, unit) => string = "";
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
