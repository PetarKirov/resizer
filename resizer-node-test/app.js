var resizer = require('resizer');
var fs = require('fs');

var inputPath = process.argv[2];
var outputImage = process.argv[3];

fs.readFile(inputPath, function(err, input) {
    if (err) throw err;

    // use downscaled portion of the image
    var options = { x0: 20, y0: 10, x1: 800, y1: 590, scale: 90 };

    var r = resizer.resize(input, options, function(err, result) {
        if (err) throw err;

        fs.writeFile(outputImage, result, function(err) {
            if (err) throw err;
        });
    });

    console.log(r);
});
