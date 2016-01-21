
var imageName = 'blushing-2.png';
var dataName = 'blushing-2';
var color = 'eyes_blink_color';

window.onload = function() {
    var c = document.getElementById("input");
    var ctx = c.getContext("2d");
   
   	var input_image = new Image();

   	input_image.onload = function(){
	    ctx.drawImage(input_image,0,0);

	    var imgData = ctx.getImageData(0,0,c.width,c.height);
		var data = imgData.data;

		// enumerate all pixels
		// each pixel's r,g,b,a datum are stored in separate sequential array elements

		var outputArray = [];

		var x = 0;
		var y = 0;

		for(var i = 0; i < data.length; i += 4) {
			var red = data[i];
			var green = data[i+1];
			var blue = data[i+2];
			//console.log(red, green, blue);
			if(red !== 0 && green !== 0 && blue !== 0) {

				outputArray.push({
					x : x,
					y : y
				})

				console.log(x + " " + y);
			}

			x++;
			if(x == 32) {
				x = 0;
				y += 1;
			}
		}

		console.log(outputArray);

		/*var c_output = ""; // = "for(int i = 0; i < " + outputArray.length + "; i++) {";
			outputArray.forEach(function(pixel, ind) {
				c_output += dataName + "Pixels[" + ind + "] = {" + pixel.x + "," + pixel.y + "};";
			});

			c_output += "<br/><br/>Pixel " + dataName + "Pixels[" + outputArray.length + "];";
			c_output += "<br/><br/>const int " + dataName + "_count =  " + outputArray.length + ";";*/


		var c_output = ""; // = "for(int i = 0; i < " + outputArray.length + "; i++) {";
			outputArray.forEach(function(pixel, ind) {
				c_output += "matrix.drawPixel(" + pixel.x + "," + pixel.y + ", " + color + ");";
			});

			//c_output += "<br/><br/>Pixel " + dataName + "Pixels[" + outputArray.length + "];";
			//c_output += "<br/><br/>const int " + dataName + "_count =  " + outputArray.length + ";";

		document.getElementById('output').innerHTML = c_output;
	}

	input_image.src = 'input/' + imageName;
};