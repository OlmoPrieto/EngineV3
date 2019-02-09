#include "engine.h"

Engine::Engine() {

}

Engine::~Engine() {

}

Engine* Engine::Instance() {
  static Engine engine;
  return &engine;
}

template <typename T>
Component<T>* Engine::CreateComponent() {

}