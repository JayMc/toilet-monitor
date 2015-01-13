var express = require('express');
var bodyParser = require('body-parser');
var Firebase = require('firebase');
var config = require('./config.js');
var app = express();
app.use(bodyParser.json());

//Firebase references
//The current visit
var visitRef = new Firebase(config.firebaseUrl+'/visit');
//Past visits
var visitsRef = new Firebase(config.firebaseUrl+'/visits');

//Express routes
//Receives IOT data
app.post('/', function (req, res) {

    //set current visit with new data (all connected clients will be updated instantly)
    visitRef.set({
    	lightOn: req.body.lightOn
    })

    //push into past visits
    visitsRef.push({
    	lightOn: req.body.lightOn,
    	date: Date.now()
    })

    return res.json(200)
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

    console.log('Listening at http://localhost:'+port)
});

