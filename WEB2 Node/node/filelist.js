const folder = './data'
const fs = require('fs');

fs.readdir(folder, function(err, files){
    console.log(files);
});