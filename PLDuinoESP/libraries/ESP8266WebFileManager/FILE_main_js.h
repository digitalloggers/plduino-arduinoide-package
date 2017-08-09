static const char FILE_mainjs[] PROGMEM = R"FILE_MAIN_JS(
function send(params) {
  var xhr = new XMLHttpRequest();
  xhr.onreadystatechange = function() {
    if (xhr.readyState == 4) {
      if (params.callback)
        params.callback(xhr.status==200, xhr);
    }
  }
  function makeFormData() {
    var fd = new FormData();
    for(var i=0; i<params.formdata.length; ++i) {
      var param = params.formdata[i];
      fd.append(param[0], param[1], (param.length>2? param[2] : undefined));
    }
    return fd;
  }
  xhr.open(params.method, params.url);
  xhr.send(params.formdata? makeFormData() : null);
}

function isTextFile(path) {
  var ext = /(?:\.([^.]+))?$/.exec(path)[1];
  if (typeof ext !== undefined) {
    switch(ext) {
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

function isImageFile(path) {
  var ext = /(?:\.([^.]+))?$/.exec(path)[1];
  if (typeof ext !== undefined) {
    switch(ext) {
      case "png":
      case "jpg":
      case "jpeg":
      case "gif":
      case "ico":
      case "bmp":
        return true;
    }
  }
  return false;
}

function delete_file(filename, callback) {
  send({
    method: 'GET',
    url: '/delete?filename='+filename,
    callback: function(succeed, path) {
      if (!succeed) {
        alert("ERROR["+xmlHttp.status+"]: "+xmlHttp.responseText);
      }
      else {
        if (callback) callback();
      }
    }
  });
}

function load_filelist(callback) {
  send({
    method: 'GET',
    url: '/list',
    callback: function(succeed, xhr) {
      if (succeed && callback)
        callback(JSON.parse(xhr.responseText));
    }
  });
}

function upload_file(file, cbk) {
  send({
    method: 'POST',
    url: '/update',
    formdata: [['data', file, file.name]],
    callback: cbk
  });
}

function upload_files(files, callback) {
  var index = 0;
  function file_callback(succeed, xhr) {
    if (succeed) {
      ++index;
      if (index >= files.length) {
        if (callback) callback();
      }
      else
        upload_file(files[index], file_callback);
    }
    else {
      alert("ERROR["+xhr.status+"]: "+xhr.responseText);
    }
  }
  upload_file(files[index], file_callback);
}

function create_file(filename, success_cbk) {
  send({
    method: 'GET',
    url: '/create?filename='+filename,
    callback: function(succeed, xhr) {
      if (succeed && success_cbk)
        success_cbk();
    }
  });
}


function createFileUploader(element, tree, editor){
  function createUploadButton() {
    var button = document.createElement("button");
    button.innerHTML = 'Upload files';
    return button;
  }
  function createUploadInput() {
    var input = document.createElement("input");
    input.type = "file";
    input.multiple = true;
    input.name = "data";
    return input;
  }
  function createCreateFileButton() {
    var mkfile = document.createElement("button");
    mkfile.innerHTML = 'Create file';
    return mkfile;
  }
  function createNewFileNameInput() {
    var path = document.createElement("input");
    path.id = "upload-path";
    path.type = "text";
    path.name = "path";
    path.defaultValue = "/data.txt";
    return path;
  }
  function createHelpText() {
    var help = document.createElement('span');
    help.innerHTML = 'Press Ctrl+S to save changes in the editor.';
    help.style.paddingLeft = '50px';
    help.style.paddingTop = '5px';
    help.id = 'help-text';
    return help;
  }
  var btn_upload_files = createUploadButton();
  var fil_upload_list = createUploadInput();
  var btn_create_file = createCreateFileButton();
  var txt_new_file_name = createNewFileNameInput();
  var root = document.getElementById(element);
  root.appendChild(btn_upload_files);
  root.appendChild(fil_upload_list);
  root.appendChild(btn_create_file);
  root.appendChild(txt_new_file_name);
  root.appendChild(createHelpText());
  btn_create_file.onclick = function(e) {
    var path = txt_new_file_name.value;
    if (path.length==0 || path.charAt(path.length-1)=='/') return;
    create_file(path, function() { tree.refreshPath(); editor.loadUrl(path); });
  };
  btn_upload_files.onclick = function(e) {
    upload_files(fil_upload_list.files, function() { tree.refreshPath(); });
  }
}

function createTree(element, editor) {
  var preview = document.getElementById("preview");
  var treeRoot = document.createElement("div");
  treeRoot.className = "css-treeview";
  document.getElementById(element).appendChild(treeRoot);
  var tree = this;

  function loadDownload(filename) {
    document.getElementById('download-frame').src = '/read?filename=' + filename + '&download=true';
  }

  function showPreview(filename) {
    document.getElementById("editor").style.display = "none";
    preview.style.display = "block";
    preview.innerHTML = '<img src="/read?filename='+filename+'" style="max-width:100%; max-height:100%; margin:auto; display:block;" />';
  }

  function fillFileMenu(el, path) {
    var list = document.createElement("ul");
    el.appendChild(list);

    function hideMenu() {
      if (document.body.getElementsByClassName('contextMenu').length > 0)
        document.body.removeChild(el);
    }

    var action = document.createElement("li");
    list.appendChild(action);
    if (isTextFile(path)) {
      action.innerHTML = "<span>Edit</span>";
      action.onclick = function(e) {
        editor.loadUrl(path);
        hideMenu();
      };
    }
    else if(isImageFile(path)) {
      action.innerHTML = "<span>Preview</span>";
      action.onclick = function(e) {
        showPreview(path);
        hideMenu();
      };
    }
    
    var download = document.createElement("li");
    list.appendChild(download);
    download.innerHTML = "<span>Download</span>";
    download.onclick = function(e) {
      loadDownload(path);
      hideMenu();
    };

    var delFile = document.createElement("li");
    list.appendChild(delFile);
    delFile.innerHTML = "<span>Delete</span>";
    delFile.onclick = function(e) {
      delete_file(path, function() {
        tree.refreshPath();
      });
      hideMenu();
    };
  }

  function showContextMenu(e, path, isfile) {
    var divContext = document.createElement("div");
    var scrollTop = (document.body.scrollTop? document.body.scrollTop : document.documentElement.scrollTop);
    var scrollLeft = (document.body.scrollLeft? document.body.scrollLeft : document.documentElement.scrollLeft);
    var left = e.clientX + scrollLeft;
    var top = e.clientY + scrollTop;
    divContext.className = 'contextMenu';
    divContext.style.display = 'block';
    divContext.style.left = left + 'px';
    divContext.style.top = top + 'px';
    fillFileMenu(divContext, path);
    document.body.appendChild(divContext);
    var width = divContext.offsetWidth;
    var height = divContext.offsetHeight;
    divContext.onmouseout = function(e) {
      if (e.clientX < left || e.clientX > (left + width) || e.clientY < top || e.clientY > (top + height))
        if (document.body.getElementsByClassName('contextMenu').length > 0)
          document.body.removeChild(divContext);
    };
  }

  function createTreeLeaf(name) {
    var leaf = document.createElement("li");
    leaf.id = "/" + name;

    var label = document.createElement("span");
    label.textContent = name;
    leaf.appendChild(label);
    
    leaf.onclick = function(e) {
      if (isTextFile(leaf.id))
        editor.loadUrl(leaf.id);
      else if (isImageFile(leaf.id))
        showPreview(leaf.id);
    };
    leaf.oncontextmenu = function(e) {
      e.preventDefault();
      e.stopPropagation();
      showContextMenu(e, leaf.id);
    };
    return leaf;
  }

  this.refreshPath = function() {
    load_filelist(function(items) {
      treeRoot.innerHTML = "";
      var list = document.createElement("ul");
      treeRoot.appendChild(list);
      for(var i=0; i<items.length; i++) {
        var item = items[i];
        list.appendChild(createTreeLeaf(item.name));
      }
    });
  };
  this.refreshPath();
  return this;
}

function createEditor(element, file) {
  var editor = ace.edit(element);
  function load_file_into_editor(filename) {
    send({
      method: 'GET',
      url: '/read?filename='+filename,
      callback: function(succeed, xhr) {
        document.getElementById("preview").style.display = 'none';
        document.getElementById("editor").style.display = 'block';
        editor.setValue(succeed? xhr.responseText : "");
        editor.clearSelection();
      }
    });
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
      send({
        method: 'POST',
        url: '/update',
        formdata: [[
          "data",
          new Blob([editor.getValue()+""], {type: "text/plain"}),
          file
        ]],
        callback: function(succeed, xhr) {
          if (!succeed)
            alert("ERROR " + xhr.status + ": " + xhr.responseText);
        }
      });
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
  if (typeof file === "undefined") file = "/index.html";
  load_file_into_editor(file);
  editor.loadUrl = function(filename) {
    file = filename;
    load_file_into_editor(file);
  }
  return editor;
}

function onBodyLoad() {
  var vars = {};
  var parts = window.location.href.replace(/[?&]+([^=&]+)=([^&]*)/gi, function(m,key,value) { vars[key] = value; });
  var editor = createEditor("editor", vars.file);
  var tree = createTree("tree", editor);
  createFileUploader("uploader", tree, editor);
};
)FILE_MAIN_JS";
