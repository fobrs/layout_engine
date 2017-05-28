fontsize = document.getElementById("fontsize");

fontsize.onchange = function() {
    selected_size = fontsize.options[fontsize.selectedIndex].value;
    websocket.send(JSON.stringify({type: "fontsize", size: selected_size}));
    websocket.send(JSON.stringify({type: "paint"}));
};

document.addEventListener("keydown", function(event) {

    //console.log(event);
    event.preventDefault();
    
    websocket.send(JSON.stringify({type: "keydown", key: event.key,keyCode: event.keyCode, ctrlKey: event.ctrlKey, altKey: event.altKey, shiftKey: event.shiftKey}));
    websocket.send(JSON.stringify({type: "paint"}));
}, true );

canvas.addEventListener("mousedown", function(event) {
    //console.log(event);
    websocket.send(JSON.stringify(
	{type: "mousedown", x: event.clientX, y: event.clientY}
    ));
} );

var host = window.location.hostname;
var websocket = new WebSocket('ws://'+host+':8080','le_web_protocol');
websocket.onopen = function() {
    console.log("onopen");
}

websocket.onerror = function() {
    console.log("onerror");
}

websocket.onmessage = function(message) {
    console.log("onmessage!!");
    console.log(message.data);
    var reader = new FileReader();

    reader.onload = function(e) {
	var img = new Image();

	img.onload = function() {
	    var canvas = document.getElementById('canvas');
	    var ctx = canvas.getContext('2d');
	    canvas.width = img.width;
	    canvas.height = img.height;
	    ctx.drawImage(img, 0, 0);
	};
	
	img.src = e.target.result;
    };
    reader.readAsDataURL(message.data);
}
