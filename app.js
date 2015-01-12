var express = require('express');
var bodyParser = require('body-parser');
var config = require('config');

var app = express();
app.use(bodyParser.json());

app.post('/', function (req, res) {
    console.log(req.body)
    res.sendStatus(200);
});

var Firebase = require('firebase');
var myRootRef = new Firebase(config.firebaseUrl);

var server = app.listen(7777, function () {
    var host = server.address().address;
    var port = server.address().port;

    console.log('Listening at http://%s:%s', host, port)
});

