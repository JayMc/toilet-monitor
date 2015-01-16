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

//POJO representation of the visit
//when the Firebase visitRef gets a value change event it will update this obj
//So we can monitor data easily
var visit = {}; 

//Express routes
//Receives IOT data
app.post('/', function (req, res) {
console.log('connection..')
    //if light is passed in as on,
    if(req.body.on == 1){
        console.log('  light on')
        //set light status in current visit and light on datetime to now
        visitRef.update({
            lightOn: true,
            lightOnAt: Date.now()
        })

    }   
    //if light is passed in as off
    else if(req.body.on == 0){
        console.log('  light off')
        //set light status to off and light off datetime to now
        visitRef.update({
            lightOn: false,
            lightOffAt: Date.now()
        })

        //push current visit into visits if it is valid (has a lightOnAt and Off Datetime)
        if(typeof visit.lightOnAt !== 'undefined' && typeof visit.lightOffAt !== 'undefined'){
            console.log('pushing current visit into visits')
            visitsRef.push({
                lightOnAt: visit.lightOnAt,
                lightOffAt: visit.lightOffAt,
                duration: visit.lightOffAt - visit.lightOnAt
            })

            //clear current visit
            visitRef.set({
                lightOnAt: null,
                lightOffAt: null,
            })
            
        }else{
            console.log('current visit is not valid')
        }

    }

    return res.json(200)

});


//Firebase events handlers
visitRef.on("value", function(snapshot) {
  //console.log(snapshot.val());
  visit = snapshot.val();
}, function (errorObject) {
  console.log("The read failed: " + errorObject.code);
});

//start Express server
var server = app.listen(7777, function () {
    var host = server.address().address;
    var port = server.address().port;

    console.log('Listening at http://localhost:'+port)
});

