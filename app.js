var express = require('express');
var bodyParser = require('body-parser');
var Firebase = require('firebase');
var config = require('./config.js');
var app = express();
app.use(bodyParser.json());

//Firebase references
var Firebase = require('firebase');
var visitRef = new Firebase(config.firebaseUrl+'/visit');

var Firebase = require('firebase');
var visitsRef = new Firebase(config.firebaseUrl+'/visits');


//Express routes

//Receives IOT data
app.post('/', function (req, res) {
    console.log(req.body)
    
    res.sendStatus(200);
});


//Firebase events handlers
visitRef.on("value", function(snapshot) {
  console.log(snapshot.val());
}, function (errorObject) {
  console.log("The read failed: " + errorObject.code);
});

//start Express server
var server = app.listen(7777, function () {
    var host = server.address().address;
    var port = server.address().port;

    console.log('Listening at http://%s:%s', host, port)
});

