#include <Arduino.h>
#include "ESP8266WebFileManager.h"
#include "FILE_index_html.h"
#include "FILE_ace_js.h"
#include "FILE_styles_css.h"
#include "FILE_main_js.h"
#include <ESP8266WebServer.h>
#include <FS.h>

namespace {

  ESP8266WebServer *http = NULL;
  File currently_uploaded_file;

  bool GUARD(bool condition, int fail_response_code, String fail_body) {
    if (!condition) http->send(fail_response_code, "text/plain", fail_body);
    return condition;
  }

  String quote(const String &src) {
    return "\"" + src + "\"";
  }

  String dequote(const String &src) {
    return (src.startsWith("\"") && src.endsWith("\"")? src.substring(1, src.length()-1) : src);
  }

  String extract_filename(const String &path) {
    return path.startsWith("/")? path.substring(1) : path;
  }

  void handle_update_upload() {
    HTTPUpload &upload = http->upload();
    switch(upload.status) {
      case UPLOAD_FILE_START: {
        String filename = dequote(upload.filename);
        filename = (filename.startsWith("/")? "" : "/") + filename;
        currently_uploaded_file = SPIFFS.open(filename, "w");
        break;
      }
      case UPLOAD_FILE_WRITE: {
        if (currently_uploaded_file)
          currently_uploaded_file.write(upload.buf, upload.currentSize);
        break;
      }
      case UPLOAD_FILE_END: {
        Serial.println("Done uploading.");
        if (currently_uploaded_file)
          currently_uploaded_file.close();
        break;
      }
    }
  }

  void handle_delete() {
    if (GUARD(http->hasArg("filename"), 500, "BAD ARGS")) {
      String filename = http->arg("filename");
      if (GUARD(SPIFFS.exists(filename), 404, "File not found")) {
        SPIFFS.remove(filename);
        http->send(200, "text/plain", "FILE REMOVED");
      }
    }
  }

  void handle_create() {
    if (GUARD(http->hasArg("filename"), 500, "BAD_ARGS")) {
      String filename = http->arg("filename");
      if (GUARD(!SPIFFS.exists(filename), 500, "FILE_EXISTS")) {
        File file = SPIFFS.open(filename, "w");
        if (GUARD((bool)file, 500, "CREATE FAILED")) {
          file.close();
          http->send(200, "text/plain", "FILE CREATED");
        }
      }
    }
  }

  void handle_list() {
    Dir dir = SPIFFS.openDir("/");
    String output = "[";
    while(dir.next()) {
      File entry = dir.openFile("r");
      if (output != "[") output += ',';
      output += "{" +
        quote("type") + ":" + quote("file") + "," +
        quote("name") + ":" + quote(extract_filename(entry.name())) +
      "}";
      entry.close();
    }
    output += "]";
    http->send(200, "text/json", output);
  }

  const char *getContentTypeByFilename(String filename) {
    static const struct {
      const char *ext;
      const char *content_type;
    } types[] = {
      { ".htm",   "text/html"               },
      { ".html",  "text/html"               },
      { ".css",   "text/css"                },
      { ".js",    "application/javascript"  },
      { ".png",   "image/png"               },
      { ".bmp",   "image/bmp"               },
      { ".gif",   "image/gif"               },
      { ".jpg",   "image/jpeg"              },
      { ".jpeg",  "image/jpeg"              },
      { ".ico",   "image/x-icon"            },
      { ".xml",   "text/xml"                },
      { ".pdf",   "application/x-pdf"       },
      { ".zip",   "application/x-zip"       },
      { ".gz",    "application/x-gzip"      },
      {0,0}
    };
    for(int i=0; types[i].ext; ++i)
      if (filename.endsWith(types[i].ext))
        return types[i].content_type;
    return "text/plain";
  }

  void handle_read() {
    if (GUARD(http->hasArg("filename"), 500, "BAD ARGS")) {
      String filename = http->arg("filename");
      if (GUARD(SPIFFS.exists(filename), 404, "NOT FOUND")) {
        File file = SPIFFS.open(filename, "r");
        if (http->hasArg("download")) {
          http->sendHeader("Content-Disposition", "filename="+quote(extract_filename(filename)));
          http->streamFile(file, "application/octet-stream");
        } else {
          http->streamFile(file, getContentTypeByFilename(filename));
        }
        file.close();
      }
    }
  }

} // anonymous namespace



namespace ESP8266WebFileManager {

  void begin(int port) {
    http = new ESP8266WebServer(port);
    http->on("/", [](){ http->send_P(200, "text/html", FILE_indexhtml); });
    http->on("/ace.js", [](){ http->send_P(200, "text/javascript", FILE_acejs); });
    http->on("/main.js", [](){ http->send_P(200, "text/javascript", FILE_mainjs); });
    http->on("/styles.css", [](){ http->send_P(200, "text/css", FILE_stylescss); });
    http->on("/create", HTTP_GET, handle_create);
    http->on("/update", HTTP_POST, [](){ http->send(200, "text/plain", "FILE UPLOADED"); }, handle_update_upload);
    http->on("/delete", HTTP_GET, handle_delete);
    http->on("/list", HTTP_GET, handle_list);
    http->on("/read", HTTP_GET, handle_read);
    http->begin();
  }

  void end() {
    http->close();
    http->stop();
    delete http;
    http = NULL;
  }

  bool handleClient() {
    if (http) {
      http->handleClient();
      return true;
    } else {
      // Error: call begin() before handle clients
      return false;
    }
  }

} // namespace ESP8266WebFileManager
