#include "engine.h"

Engine::Engine() {

}

Engine::~Engine() {

}

Engine* Engine::Instance() {
  static Engine oEngine;
  return &oEngine;
}

Component* Engine::CreateComponent() {
  return &Component();
}