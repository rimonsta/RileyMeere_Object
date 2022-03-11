/*
This P5 sketch is a template for getting started with Serial Communication. 
The SerialEvent callback is where incoming data is received 


By Riley Meere, adapted from Arielle Hein and ITP Phys Comp Serial Labs

*/


var serial; //variable to hold an instance of the serial port library
var portName = 'COM3';


var timer = 60; // variable to count down time
var score = 0; // variable to keep track of score
var player_color_num = 0; // variable to assign serial data from photoresistor
var player_num_sides = 0; // variable to assign serial data from potentiometer
var keep_shape = 0; // int to determine if player has had enough feedback/time to match shape
var game_num_sides = 0; // variable to assign random number of sides to game shape
var game_color = 0; // variable to assign random color to game shape


function setup() {
  createCanvas(800, 700);
  frameRate(1); // 1 frame per second

  serial = new p5.SerialPort(); //a new instance of serial port library

  //set up events for serial communication
  serial.on('connected', serverConnected);
  serial.on('open', portOpen);
  serial.on('data', serialEvent);
  serial.on('error', serialError);
  serial.on('close', portClose);

  //open our serial port
  serial.open(portName);

  //let's figure out what port we're on - useful for determining your port
  // serial.on('list', printList); //set a callback function for the serialport list event
  // serial.list(); //list the serial ports
}

// https://p5js.org/examples/form-regular-polygon.html
// creates a polygon based on given parameters
function polygon(x, y, radius, npoints) {
  let angle = TWO_PI / npoints;
  beginShape();
  for (let a = 0; a < TWO_PI; a += angle) {
    let sx = x + cos(a) * radius;
    let sy = y + sin(a) * radius;
    vertex(sx, sy);
  }
  endShape(CLOSE);
}

// determines color of shape based on variable integer 0-3
// https://www.december.com/html/spec/colorsvg.html
function determineColor(shape_color_num) {
  if (shape_color_num == 0) {
    return 'white';
  }
  else if (shape_color_num == 1) {
    return 'red';
  }
  else if (shape_color_num == 2) {
    return 'lawngreen';
  }
  else if (shape_color_num == 3) {
    return 'dodgerblue';
  }
}

function draw() {
  background('yellow');
  
  // check if time is up
  https://p5js.org/reference/#/p5/noLoop
  if(timer == 0) {
    noLoop();
  }
  
  // https://p5js.org/reference/#/p5/text
  // display timer at top/right of canvas
  textSize(40);
  fill('red');
  text(timer, 750, 50);
  // decrease timer count
  timer--;
  
  // string joins updated score with label
  var display_score = 'score: ' + score;
  textSize(32);
  fill('purple');
  // display score/label string at top/center of canvas
  text(display_score, 315, 100);
  
  // checks if new game shape should be drawn
  if (keep_shape == 0) {
    // generates random number between 3 and 8 to determine the 
    // number of sides of sides of shape the player must match
    // https://www.w3schools.com/jsref/jsref_random.asp
    game_num_sides = Math.floor((Math.random() * 8) + 3);
    // generates random number between 0 and 4 to determine the 
    // color of the shape the player must match to 
    game_color_num = Math.floor(Math.random()*4);
    // determine_color() determines which color to fill shape
    // based on randomly genrated value of game_color_num
    game_color = determineColor(game_color_num);
    keep_shape++;
  }
  // 9+1 = number of iterations shape will stay the same
  // probably should make this a variable
  else if (keep_shape < 7) {
    keep_shape++;
  }
  // if iteration limit is reached, set number of iterations back
  // to zero so the shape can be redrawn in the next iteration
  else {
    keep_shape = 0;
  } 
  
  // draw game shape (left side)
  fill(game_color);
  polygon(200, 350, 100, game_num_sides);
  
  // determine player shape color from photoresistor data
  var player_color = determineColor(player_color_num);
  fill(player_color);
  // draw polygon with num sides based on potentiometer data
  polygon(550, 350, 100, player_num_sides);
  
  // if shapes are perfect match, increase score by 3
  if (player_color == game_color && player_num_sides == game_num_sides) {
    score += 3;
  }
  // if shapes only match in color or number of sides, increase 
  // score by 1 
  else if (game_color == player_color || game_num_sides == player_num_sides) {
    score++;
  }
}


//all my callback functions are down here:
//these are useful for giving feedback

function serverConnected(){
	console.log('connected to the server');
}

function portOpen(){
  console.log('the serial port opened!');
}

//THIS IS WHERE WE RECEIVE DATA!!!!!!
//make sure you're reading data based on how you're sending from arduino
function serialEvent(){
	//receive serial data here
  
  var data = serial.readLine();
  if(data === "") return;
  
  //https://www.geeksforgeeks.org/split-string-java-examples/
  var split = data.split(',');
  console.log(split[0], split[1]);
  
  player_color_num = split[0];
  player_num_sides = split[1];
  
}

function serialError(err){
  console.log('something went wrong with the port. ' + err);
}

function portClose(){
  console.log('the port was closed');
}

// get the list of ports:
function printList(portList) {
 // portList is an array of serial port names
 for (var i = 0; i < portList.length; i++) {
 // Display the list the console:
 print(i + " " + portList[i]);
 }
}