#include "Schalter.h"
#include <Arduino.h>


Schalter::Schalter(int pin){
  this->pin = pin;
  pinMode(this->pin, INPUT_PULLUP);
  this->reset();
}

Schalter* Schalter::update(){
	if ((this->schalter_war_load == false) && this->isLoad()) {
		this->schalter_war_load = true;
	}
  if ((this->schalter_war_load == true) && this->isInject()) {
    this->schalter_war_load = false;
    if(this->schalter_modus){
      this->setTrigger();
    }
  }
  return this;
}

bool Schalter::getStatus(){
	return this->schalter_war_load;
}

bool Schalter::getStatusFromPin(){
	return digitalRead(this->pin);
}

void Schalter::reset(){
  this->schalter_war_load=false;
  this->trigger=false;
}

bool Schalter::isLoad(){
  return this->getStatusFromPin() != this->schalter_inject;
}

bool Schalter::isInject(){
  return this->getStatusFromPin() == this->schalter_inject;
}

void Schalter::setTrigger(){
  this->trigger=true;
}

void Schalter::resetTrigger(){
  this->trigger=false;
}

bool Schalter::getTrigger(){
  return this->trigger;
}




