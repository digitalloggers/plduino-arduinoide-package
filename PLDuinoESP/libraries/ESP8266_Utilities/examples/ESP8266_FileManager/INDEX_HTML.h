static const char INDEX_HTML[] PROGMEM = R"INDEX_HTML(

<!DOCTYPE html>
<html lang="en">
  <head>
    <title>SD Editor</title>
    <style type="text/css" media="screen">
      .contextMenu {
        z-index: 300;
        position: absolute;
        left: 5px;
        border: 1px solid #444;
        background-color: #F5F5F5;
        display: none;
        box-shadow: 0 0 10px rgba( 0, 0, 0, .4 );
        font-size: 12px;
        font-family: sans-serif;
        font-weight:bold;
      }
      .contextMenu ul {
        list-style: none;
        top: 0;
        left: 0;
        margin: 0;
        padding: 0;
      }
      .contextMenu li {
        position: relative;
        min-width: 60px;
        cursor: pointer;
      }
      .contextMenu span {
        color: #444;
        display: inline-block;
        padding: 6px;
      }
      .contextMenu li:hover { background: #444; }
      .contextMenu li:hover span { color: #EEE; }
    
      .css-treeview ul, .css-treeview li {
        padding: 0;
        margin: 0;
        list-style: none;
      }

      .css-treeview input {
        position: absolute;
        opacity: 0;
      }

      .css-treeview {
        font: normal 11px Verdana, Arial, Sans-serif;
        -moz-user-select: none;
        -webkit-user-select: none;
        user-select: none;
      }

      .css-treeview span {
        color: #00f;
        cursor: pointer;
      }

      .css-treeview span:hover {
        text-decoration: underline;
      }

      .css-treeview input + label + ul {
        margin: 0 0 0 22px;
      }

      .css-treeview input ~ ul {
        display: none;
      }

      .css-treeview label, .css-treeview label::before {
        cursor: pointer;
      }

      .css-treeview input:disabled + label {
        cursor: default;
        opacity: .6;
      }

      .css-treeview input:checked:not(:disabled) ~ ul {
        display: block;
      }

      .css-treeview label, .css-treeview label::before {
        background: url("data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAACgCAYAAAAFOewUAAAAGXRFWHRTb2Z0d2FyZQBBZG9iZSBJbWFnZVJlYWR5ccllPAAAApxJREFUeNrslM1u00AQgGdthyalFFOK+ClIIKQKyqUVQvTEE3DmAhLwAhU8QZoH4A2Q2gMSFace4MCtJ8SPBFwAkRuiHKpA6sRN/Lu7zG5i14kctaUqRGhGXnu9O/Pt7MzsMiklvF+9t2kWTDvyIrAsA0aKRRi1T0C/hJ4LUbt5/8rNpWVlp8RSr9J40b48fxFaTQ9+ft8EZ6MJYb0Ok+dnYGpmPgXwKIAvLx8vYXc5GdMAQJgQEkpjRTh36TS2U+DWW/D17WuYgm8pwJyY1npZsZKOxImOV1I/h4+O6vEg5GCZBpgmA6hX8wHKUHDRBXQYicQ4rlc3Tf0VMs8DHBS864F2YFspjgUYjKX/Az3gsdQd2eeBHwmdGWXHcgBGSkZXOXohcEXebRoQcAgjqediNY+AVyu3Z3sAKqfKoGMsewBeEIOPgQxxPJIjcGH6qtL/0AdADzKGnuuD+2tLK7Q8DhHHbOBW+KEzcHLuYc82MkEUekLiwuvVH+guQBQzOG4XdAb8EOcRcqQvDkY2iCLuxECJ43JobMXoutqGgDa2T7UqLKwt9KRyuxKVByqVXXqIoCCUCAqhUOioTWC7G4TQEOD0APy2/7G2Xpu1J4+lxeQ4TXBbITDpoVelRN/BVFbwu5oMMJUBhoXy5tmdRcMwymP2OLQaLjx9/vnBo6V3K6izATmSnMa0Dq7ferIohJhr1p01zrlz49rZF4OMs8JkX23vVQzYp+wbYGV/KpXKjvspl8tsIKCrMNAYFxj2GKS5ZWxg4ewKsJfaGMIY5KXqPz8LBBj6+yDvVP79+yDp/9F9oIx3OisHWwe7Oal0HxCAAAQgAAEIQAACEIAABCAAAQhAAAIQgAAEIAABCEAAAhCAAAQgwD8E/BZgAP0qhKj3rXO7AAAAAElFTkSuQmCC") no-repeat;
      }

      .css-treeview label, .css-treeview span, .css-treeview label::before {
        display: inline-block;
        height: 16px;
        line-height: 16px;
        vertical-align: middle;
      }

      .css-treeview label {
        background-position: 18px 0;
      }

      .css-treeview label::before {
        content: "";
        width: 16px;
        margin: 0 22px 0 0;
        vertical-align: middle;
        background-position: 0 -32px;
      }

      .css-treeview input:checked + label::before {
        background-position: 0 -16px;
      }

      /* webkit adjacent element selector bugfix */
      @media screen and (-webkit-min-device-pixel-ratio:0)
      {
        .css-treeview{
          -webkit-animation: webkit-adjacent-element-selector-bugfix infinite 1s;
        }

        @-webkit-keyframes webkit-adjacent-element-selector-bugfix 
        {
          from  { 
            padding: 0;
          } 
          to  { 
            padding: 0;
          }
        }
      }

      #uploader { 
        position: absolute;
        top: 0;
        right: 0;
        left: 0;
        height:28px;
        line-height: 24px;
        padding-left: 10px;
        background-color: #444;
        color:#EEE;
      }
      #tree { 
        position: absolute;
        top: 28px;
        bottom: 0;
        left: 0;
        width:200px;
        padding: 8px;
      }
      #editor, #preview { 
        position: absolute;
        top: 28px;
        right: 0;
        bottom: 0;
        left: 200px;
      }
      #preview {
        background-color: #EEE;
        padding:5px;
      }
    </style>
    <script>
      function createFileUploader(element, tree, editor){
        var xmlHttp;
        var root = document.getElementById(element);
        var input;
        var path;
        var button;
        var mkfile;
        root.appendChild((function(){
          input = document.createElement("input");
          input.type = "file";
          input.multiple = false;
          input.name = "data";
          return input;
        })());
        root.appendChild((function(){
          path = document.createElement("input");
          path.id = "upload-path";
          path.type = "text";
          path.name = "path";
          path.defaultValue = "/";
          return path;
        })());
        root.appendChild((function(){
          button = document.createElement("button");
          button.innerHTML = 'Upload';
          return button;
        })());
        root.appendChild((function(){
          mkfile = document.createElement("button");
          mkfile.innerHTML = 'MkFile';
          return mkfile;
        })());
        root.appendChild((function(){
          var help = document.createElement('span');
          help.innerHTML = 'Press Ctrl+S to save changes in the editor.';
          help.style.paddingLeft = '50px';
          help.style.paddingTop = '5px';
          return help;
        })());

        input.onchange = function(e){
          if(input.files.length === 0) return;
          var filename = input.files[0].name;
          var ext = /(?:\.([^.]+))?$/.exec(filename)[1];
          var name = /(.*)\.[^.]+$/.exec(filename)[1];
          if(typeof name !== undefined){
            if(name.length > 8) name = name.substring(0, 8);
            filename = name;
          }
          if(typeof ext !== undefined){
            if(ext === "html") ext = "htm";
            else if(ext === "jpeg") ext = "jpg";
            filename = filename + "." + ext;
          }
          if(path.value === "/" || path.value.lastIndexOf("/") === 0){
            path.value = "/"+filename;
          } else {
            path.value = path.value.substring(0, path.value.lastIndexOf("/")+1)+filename;
          }
        }

        mkfile.onclick = function(e){
          if(path.value.indexOf(".") === -1) return;
          createPath(path.value);
          editor.loadUrl(path.value);
        };
        
        button.onclick = function(e){
          if(input.files.length === 0){
            return;
          }
          xmlHttp = new XMLHttpRequest();
          xmlHttp.onreadystatechange = httpPostProcessRequest;
          var formData = new FormData();
          formData.append("data", input.files[0], path.value);
          xmlHttp.open("POST", "/edit");
          xmlHttp.send(formData);
        }
  
        function httpPostProcessRequest(){
          if (xmlHttp.readyState == 4){
            if(xmlHttp.status != 200)
              alert("ERROR["+xmlHttp.status+"]: "+xmlHttp.responseText);
            else {
              tree.refreshPath(path.value);
            }
          }
        }
        
        function createPath(p){
          xmlHttp = new XMLHttpRequest();
          xmlHttp.onreadystatechange = httpPostProcessRequest;
          var formData = new FormData();
          formData.append("path", p);
          xmlHttp.open("PUT", "/edit");
          xmlHttp.send(formData);
        }
      }

      function createTree(element, editor){
        var preview = document.getElementById("preview");
        var treeRoot = document.createElement("div");
        treeRoot.className = "css-treeview";
        document.getElementById(element).appendChild(treeRoot);
  
        function loadDownload(path){
          document.getElementById('download-frame').src = path+"?download=true";
        }
  
        function loadPreview(path){
          document.getElementById("editor").style.display = "none";
          preview.style.display = "block";
          preview.innerHTML = '<img src="'+path+'" style="max-width:100%; max-height:100%; margin:auto; display:block;" />';
        }
  
        function fillFolderMenu(el, path){
          var list = document.createElement("ul");
          el.appendChild(list);
          var action = document.createElement("li");
          list.appendChild(action);
          var isChecked = document.getElementById(path).checked;
          var expnd = document.createElement("li");
          list.appendChild(expnd);
          if(isChecked){
            expnd.innerHTML = "<span>Collapse</span>";
            expnd.onclick = function(e){
              document.getElementById(path).checked = false;
              if(document.body.getElementsByClassName('contextMenu').length > 0) document.body.removeChild(el);
            };
            var refrsh = document.createElement("li");
            list.appendChild(refrsh);
            refrsh.innerHTML = "<span>Refresh</span>";
            refrsh.onclick = function(e){
              var leaf = document.getElementById(path).parentNode;
              if(leaf.childNodes.length == 3) leaf.removeChild(leaf.childNodes[2]);
              httpGet(leaf, path);
              if(document.body.getElementsByClassName('contextMenu').length > 0) document.body.removeChild(el);
            };
          } else {
            expnd.innerHTML = "<span>Expand</span>";
            expnd.onclick = function(e){
              document.getElementById(path).checked = true;
              var leaf = document.getElementById(path).parentNode;
              if(leaf.childNodes.length == 3) leaf.removeChild(leaf.childNodes[2]);
              httpGet(leaf, path);
              if(document.body.getElementsByClassName('contextMenu').length > 0) document.body.removeChild(el);
            };
          }
          var upload = document.createElement("li");
          list.appendChild(upload);
          upload.innerHTML = "<span>Upload</span>";
          upload.onclick = function(e){
            var pathEl = document.getElementById("upload-path");
            if(pathEl){
              var subPath = pathEl.value;
              if(subPath.lastIndexOf("/") < 1) pathEl.value = path+subPath;
              else pathEl.value = path.substring(subPath.lastIndexOf("/"))+subPath;
            }
            if(document.body.getElementsByClassName('contextMenu').length > 0) document.body.removeChild(el);
          };
          var delFile = document.createElement("li");
          list.appendChild(delFile);
          delFile.innerHTML = "<span>Delete</span>";
          delFile.onclick = function(e){
            httpDelete(path);
            if(document.body.getElementsByClassName('contextMenu').length > 0) document.body.removeChild(el);
          };
        }
  
        function fillFileMenu(el, path){
          var list = document.createElement("ul");
          el.appendChild(list);
          var action = document.createElement("li");
          list.appendChild(action);
          if(isTextFile(path)){
            action.innerHTML = "<span>Edit</span>";
            action.onclick = function(e){
              editor.loadUrl(path);
              if(document.body.getElementsByClassName('contextMenu').length > 0) document.body.removeChild(el);
            };
          } else if(isImageFile(path)){
            action.innerHTML = "<span>Preview</span>";
            action.onclick = function(e){
              loadPreview(path);
              if(document.body.getElementsByClassName('contextMenu').length > 0) document.body.removeChild(el);
            };
          }
          var download = document.createElement("li");
          list.appendChild(download);
          download.innerHTML = "<span>Download</span>";
          download.onclick = function(e){
            loadDownload(path);
            if(document.body.getElementsByClassName('contextMenu').length > 0) document.body.removeChild(el);
          };
          var delFile = document.createElement("li");
          list.appendChild(delFile);
          delFile.innerHTML = "<span>Delete</span>";
          delFile.onclick = function(e){
            httpDelete(path);
            if(document.body.getElementsByClassName('contextMenu').length > 0) document.body.removeChild(el);
          };
        }
  
        function showContextMenu(e, path, isfile){
          var divContext = document.createElement("div");
          var scrollTop = document.body.scrollTop ? document.body.scrollTop : document.documentElement.scrollTop;
          var scrollLeft = document.body.scrollLeft ? document.body.scrollLeft : document.documentElement.scrollLeft;
          var left = e.clientX + scrollLeft;
          var top = e.clientY + scrollTop;
          divContext.className = 'contextMenu';
          divContext.style.display = 'block';
          divContext.style.left = left + 'px';
          divContext.style.top = top + 'px';
          if(isfile) fillFileMenu(divContext, path);
          else fillFolderMenu(divContext, path);
          document.body.appendChild(divContext);
          var width = divContext.offsetWidth;
          var height = divContext.offsetHeight;
          divContext.onmouseout = function(e){
            if(e.clientX < left || e.clientX > (left + width) || e.clientY < top || e.clientY > (top + height)){
              if(document.body.getElementsByClassName('contextMenu').length > 0) document.body.removeChild(divContext);
            }
          };
        }
  
        function createTreeLeaf(path, name, size){
          var leaf = document.createElement("li");
          leaf.id = (((path == "/")?"":path)+"/"+name);
          var label = document.createElement("span");
          label.textContent = name;
          leaf.appendChild(label);
          leaf.onclick = function(e){
            if(isTextFile(leaf.id)){
              editor.loadUrl(leaf.id);
            } else if(isImageFile(leaf.id)){
              loadPreview(leaf.id);
            }
          };
          leaf.oncontextmenu = function(e){
            e.preventDefault();
            e.stopPropagation();
            showContextMenu(e, leaf.id, true);
          };
          return leaf;
        }
  
        function createTreeBranch(path, name, disabled){
          var leaf = document.createElement("li");
          var check = document.createElement("input");
          check.type = "checkbox";
          check.id = ((path == "/")?"":path)+"/"+name;
          if(typeof disabled !== "undefined" && disabled) check.disabled = "disabled";
          leaf.appendChild(check);
          var label = document.createElement("label");
          label.for = check.id;
          label.textContent = name;
          leaf.appendChild(label);
          check.onchange = function(e){
            if(check.checked){
              if(leaf.childNodes.length == 3) leaf.removeChild(leaf.childNodes[2]);
              httpGet(leaf, check.id);
            }
          };
          label.onclick = function(e){
            if(!check.checked){
              check.checked = true;
              if(leaf.childNodes.length == 3) leaf.removeChild(leaf.childNodes[2]);
              httpGet(leaf, check.id);
            } else {
              check.checked = false;
            }
          };
          leaf.oncontextmenu = function(e){
            e.preventDefault();
            e.stopPropagation();
            showContextMenu(e, check.id, false);
          }
          return leaf;
        }
  
        function addList(parent, path, items){
          var list = document.createElement("ul");
          parent.appendChild(list);
          var ll = items.length;
          for(var i = 0; i < ll; i++){
            var item = items[i];
            var itemEl;
            if(item.type === "file"){
              itemEl = createTreeLeaf(path, item.name, item.size);
            } else {
              itemEl = createTreeBranch(path, item.name);
            }
            list.appendChild(itemEl);
          }
    
        }
  
        function isTextFile(path){
          var ext = /(?:\.([^.]+))?$/.exec(path)[1];
          if(typeof ext !== undefined){
            switch(ext){
              case "txt":
              case "htm":
              case "html":
              case "js":
              case "json":
              case "c":
              case "h":
              case "cpp":
              case "css":
              case "xml":
                return true;
            }
          }
          return false;
        }
  
        function isImageFile(path){
          var ext = /(?:\.([^.]+))?$/.exec(path)[1];
          if(typeof ext !== undefined){
            switch(ext){
              case "png":
              case "jpg":
              case "gif":
              case "ico":
                return true;
            }
          }
          return false;
        }
  
        this.refreshPath = function(path){
          if(path.lastIndexOf('/') < 1){
            path = '/';
            treeRoot.removeChild(treeRoot.childNodes[0]);
            httpGet(treeRoot, "/");
          } else {
            path = path.substring(0, path.lastIndexOf('/'));
            var leaf = document.getElementById(path).parentNode;
            if(leaf.childNodes.length == 3) leaf.removeChild(leaf.childNodes[2]);
            httpGet(leaf, path);
          }
        };
  
        function delCb(path){
          return function(){
            if (xmlHttp.readyState == 4){
              if(xmlHttp.status != 200){
                alert("ERROR["+xmlHttp.status+"]: "+xmlHttp.responseText);
              } else {
                if(path.lastIndexOf('/') < 1){
                  path = '/';
                  treeRoot.removeChild(treeRoot.childNodes[0]);
                  httpGet(treeRoot, "/");
                } else {
                  path = path.substring(0, path.lastIndexOf('/'));
                  var leaf = document.getElementById(path).parentNode;
                  if(leaf.childNodes.length == 3) leaf.removeChild(leaf.childNodes[2]);
                  httpGet(leaf, path);
                }
              }
            }
          }
        }
  
        function httpDelete(filename){
          xmlHttp = new XMLHttpRequest();
          xmlHttp.onreadystatechange = delCb(filename);
          var formData = new FormData();
          formData.append("path", filename);
          xmlHttp.open("DELETE", "/edit");
          xmlHttp.send(formData);
        }
  
        function getCb(parent, path){
          return function(){
            if (xmlHttp.readyState == 4){
              //clear loading
              if(xmlHttp.status == 200) addList(parent, path, JSON.parse(xmlHttp.responseText));
            }
          }
        }
  
        function httpGet(parent, path){
          xmlHttp = new XMLHttpRequest(parent, path);
          xmlHttp.onreadystatechange = getCb(parent, path);
          xmlHttp.open("GET", "/list?dir="+path, true);
          xmlHttp.send(null);
          //start loading
        }
  
        httpGet(treeRoot, "/");
        return this;
      }

      function createEditor(element, file){
        if (typeof file === "undefined")
          file = "/index.htm";
        var xmlHttp = null;
        var editor = ace.edit(element);
  
        //post
        function httpPostProcessRequest(){
          if (xmlHttp.readyState == 4){
            if (xmlHttp.status != 200)
              alert("ERROR["+xmlHttp.status+"]: "+xmlHttp.responseText);
          }
        }
        function httpPost(filename, data){
          xmlHttp = new XMLHttpRequest();
          xmlHttp.onreadystatechange = httpPostProcessRequest;
          var formData = new FormData();
          formData.append("data", new Blob([data], { type: "text/plain" }), filename);
          xmlHttp.open("POST", "/edit");
          xmlHttp.send(formData);
        }
        //get
        function httpGetProcessRequest(){
          if (xmlHttp.readyState == 4){
            document.getElementById("preview").style.display = "none";
            document.getElementById("editor").style.display = "block";
            if (xmlHttp.status == 200)
              editor.setValue(xmlHttp.responseText);
            else editor.setValue("");
            editor.clearSelection();
          }
        }
        function httpGet(theUrl){
            xmlHttp = new XMLHttpRequest();
            xmlHttp.onreadystatechange = httpGetProcessRequest;
            xmlHttp.open("GET", theUrl, true);
            xmlHttp.send(null);
        }
  
        editor.$blockScrolling = Infinity;
        editor.getSession().setUseSoftTabs(true);
        editor.getSession().setTabSize(2);
        editor.setHighlightActiveLine(true);
        editor.setShowPrintMargin(false);
        editor.commands.addCommand({
            name: 'saveCommand',
            bindKey: {win: 'Ctrl-S',  mac: 'Command-S'},
            exec: function(editor) {
              httpPost(file, editor.getValue()+"");
            },
            readOnly: false
        });
        editor.commands.addCommand({
            name: 'undoCommand',
            bindKey: {win: 'Ctrl-Z',  mac: 'Command-Z'},
            exec: function(editor) {
              editor.getSession().getUndoManager().undo(false);
            },
            readOnly: false
        });
        editor.commands.addCommand({
            name: 'redoCommand',
            bindKey: {win: 'Ctrl-Shift-Z',  mac: 'Command-Shift-Z'},
            exec: function(editor) {
              editor.getSession().getUndoManager().redo(false);
            },
            readOnly: false
        });
        httpGet(file);
        editor.loadUrl = function(filename){
          file = filename;
          httpGet(file);
        }
        return editor;
      }
      function onBodyLoad(){
        var vars = {};
        var parts = window.location.href.replace(/[?&]+([^=&]+)=([^&]*)/gi, function(m,key,value) { vars[key] = value; });
        var editor = createEditor("editor", vars.file);
        var tree = createTree("tree", editor);
        createFileUploader("uploader", tree, editor);
      };
    </script>
    <script src="/ace.js"></script>
  </head>
  <body onload="onBodyLoad();">
    <div id="uploader"></div>
    <div id="tree"></div>
    <div id="editor"></div>
    <div id="preview" style="display:none;"></div>
    <iframe id=download-frame style='display:none;'></iframe>
  </body>
</html>


)INDEX_HTML";

