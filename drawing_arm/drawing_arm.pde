import processing.serial.*;

Serial port;

boolean serialOn = false;

int SVG = 1;
int MOUSE = 2;
int mode = SVG;

int time;
int wait = 10;

PVector target;
PVector origo;
PVector elbow;

//färger
color linje = color(255);
color linje2 = color(150);
color bg = color(0);
color targetcolor = color(200, 0, 0);

float baseAngle;
float vertexAngle;
int armLength;

PGraphics canvas;

//::::::::::::::::::::::::

import geomerative.*;
RShape grp;
RPoint[][] pointPaths;

int pathNum;
int pointNum;

PVector targetPoint;
PVector location;
PVector dir;

//::::::::::::::::::::::::

void setup() {
  size(700, 500);
  frameRate(60);

  time = millis();

  armLength = int(dist(50, 50, 450, 450)/2);  

  if (serialOn) {
    String arduinoPort = Serial.list()[0];
    port = new Serial(this, arduinoPort, 9600);
  }


  //geomerative
  RG.init(this);
  RG.setPolygonizer(RG.ADAPTATIVE);
  RG.ignoreStyles();
  grp = RG.loadShape("eolarna.svg");
  grp.centerIn(g, 200, 1, 1);
  grp.translate(500/2, height/2);
  pointPaths = grp.getPointsInPaths();
  location = new PVector(pointPaths[0][0].x, pointPaths[0][0].y);
  targetPoint = new PVector(location.x, location.y);//location.get();
  pathNum = 0;
  pointNum = 0;

  println("svg info:");
  println("Num paths = " + pointPaths.length);

  //canvas
  canvas = createGraphics(width, height);
  canvas.beginDraw();
  canvas.background(0);
  canvas.endDraw();

  //annat
  origo = new PVector(450, 450);
  target = new PVector(width/2, height/2); //behöver initialiseras
}


void draw() {

  //uppdatera::::::::::::::::::::::::::::::::::::

  if (mode == SVG) {
    stroke(255);
    strokeWeight(1);
    noFill();
    grp.draw();
    if (location.x < targetPoint.x + 2 && location.x > targetPoint.x - 2 && location.y < targetPoint.y +2 && location.y > targetPoint.y - 2) {
      pointNum++;  //nånting med när och hur den här ökas kan komma skapa problem med former som har väldigt få punkter eller långt mellan dem
      if (pointNum < pointPaths[pathNum].length) {
        targetPoint = new PVector(pointPaths[pathNum][pointNum].x, pointPaths[pathNum][pointNum].y);
        dir = PVector.sub(targetPoint, location);

        dir.normalize();
        dir.mult(1);
      } else {
        if ((pathNum+1)<pointPaths.length) {
          pathNum++;
          pointNum = 0;
          //println("current path = "+pathNum);
          //println("points in current path = " + pointPaths[pathNum].length);
        } else {
          dir = new PVector(0, 0);
        }
      }
    }
    location.add(dir);


    target = new PVector(location.x, location.y);//location.get();
    target.sub(origo);
    target.limit(armLength*2);
  }

  if (mode == MOUSE) {
    target = new PVector(mouseX, mouseY);
    target.sub(origo);
    target.limit(armLength*2);
    location = new PVector(target.x, target.y);
  }



  float cosv = (target.mag()/2) / armLength;
  float v = acos(cosv);
  float va = 90 - degrees(v);
  va*=2;

  float elbowServo = va;
  float origoServo = degrees(v);
  origoServo -=  degrees(abs(target.heading()));
  origoServo = abs(origoServo);
  origoServo = 180 - origoServo;

  if (serialOn) {
    
      if (millis() - time >= wait) {
        int origo = int(origoServo);
        int elbow = int(elbowServo);
        
        byte out[] = new byte[2];
        out[0] = byte(origo);
        out[1] = byte(elbow);
        port.write(out);
        
        time = millis();
        while (port.available () > 0) {
          String in = port.readStringUntil('\n');
          if (in != null) {
            println(in);
          }
        }
      }
  }

  //rita:::::::::::::::::::::::::::::::::::::::::

  background(bg);

  //canvas
  canvas.beginDraw();
  canvas.stroke(linje);
  canvas.strokeWeight(4);
  if (pointNum > 1) {
    canvas.point(location.x, location.y);
  }
  canvas.endDraw();
  image(canvas, 0, 0);

  //svg
  if (mode == SVG) {
    stroke(50);
    grp.draw();
  }

  //"penna"
  if (pointNum == 1) { //nån slags lyftapennan försök
    stroke(0);
  } else {
    stroke(200, 0, 0);
  }

  strokeWeight(10);
  ellipse(location.x, location.y, 5, 5);

  //boundingbox
  noFill();
  stroke(linje2);
  strokeWeight(1);
  rect(50, 50, 400, 400);

  //origoServoRange
  noFill();
  stroke(linje2);
  arc(origo.x, origo.y, 100, 100, PI, TWO_PI, CHORD);

  //targetdot
  strokeWeight(4);
  stroke(targetcolor);
  point(target.x, target.y);

  //targetline
  pushMatrix();
  strokeWeight(1);
  translate(origo.x, origo.y);
  line(0, 0, target.x, target.y);
  popMatrix();

  //target arc
  arc(origo.x, origo.y, 100, 100, PI, TWO_PI - abs(target.heading()));

  //overarm
  stroke(linje);
  strokeWeight(5);
  pushMatrix();
  translate(origo.x, origo.y);
  rotate(TWO_PI - abs(target.heading()));
  rotate(v);
  line(0, 0, armLength, 0);

  //elbowServoRange
  noFill();
  strokeWeight(1);
  stroke(linje2);
  arc(armLength, 0, 100, 100, PI, TWO_PI, CHORD);

  //underarm
  pushMatrix();
  translate(armLength, 0);
  rotate(PI - radians(-va));
  stroke(linje);
  strokeWeight(5);
  line(0, 0, armLength, 0);
  stroke(200, 0, 0);
  strokeWeight(10);
  point(0, 0);
  popMatrix();
  popMatrix();

  //text
  fill(linje);
  textSize(15);
  text("elbowServo = " + va, 500, height/2);
  text("origoServo = " + origoServo, 500, 470);
}
