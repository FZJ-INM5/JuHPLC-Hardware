#include "LED.h"
#include <Arduino.h>


LED::LED(int port,bool state){

  this->port = port;
  this->state = state;
  
  //initialize port and config it as output
  pinMode(port, OUTPUT);

  //set port to given initial state
  digitalWrite(port, state);

}

void LED::setState(bool state){

  //the desired state is already reached, nothing to do, return
  if(this->state == state){
    return;
  }

  this->state = state;
  digitalWrite(this->port,this->state);
    
}

bool LED::getState(){
  return this->state;
}

void LED::toggle(){
  this->state=!this->state;
  digitalWrite(this->port,this->state);
}





