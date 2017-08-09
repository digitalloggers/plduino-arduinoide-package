static const char FILE_indexhtml[] PROGMEM = R"FILE_INDEX_HTML(
<!DOCTYPE html>
<html lang="en">
  <head>
    <title>SD Editor</title>
    <link rel="stylesheet" type="text/css" href="styles.css">
    <script src="main.js"></script>
    <script src="ace.js"></script>
  </head>
  <body onload="onBodyLoad();">
    <div id="uploader"></div>
    <div id="tree"></div>
    <div id="editor"></div>
    <div id="preview" style="display:none;"></div>
    <iframe id=download-frame style='display:none;'></iframe>
  </body>
</html>
)FILE_INDEX_HTML";
