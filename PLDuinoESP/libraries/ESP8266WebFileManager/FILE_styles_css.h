static const char FILE_stylescss[] PROGMEM = R"FILE_STYLES_CSS(
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
  font: normal 12pt Arial, Helvetica, Sans-serif;
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

.css-treeview label, .css-treeview span, .css-treeview label::before {
  display: inline-block;
  height: 22px;
  line-height: 22px;
  vertical-align: middle;
}

.css-treeview label {
  background-position: 18px 0;
}

.css-treeview label::before {
  content: "";
  width: 22px;
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
  background-color: #ddddff;
  color:#000;
}
#tree { 
  position: absolute;
  top: 28px;
  bottom: 0;
  left: 0;
  width:200px;
  padding: 8px;
  background-color: #f4f4f4;
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
)FILE_STYLES_CSS";
