#pragma once

#include <string>
#include <typeindex>

#include "BehaviorComponentConfig.hh"
#include "BehaviorComponentFactory.hh"
#include "BindableVariableMetadata.hh"
#include "Component.hh"
#include "Logging.hh"

// forward decls
class WADLoader;
class EventBus;
class EventMessage;

class IBehaviorComponent : public Component {
 public:
  IBehaviorComponent() : Component() {}
  virtual ~IBehaviorComponent() override;

  virtual std::string toString() const override;
  void managerRegister() override;
  void managerUnregister() override;

  // TODO: IBehaviorComponent::accept() implements a Visitor pattern; EventMessage visits IBehaviorComponent
  // when IBehaviorComponent::receiveEvent() calls EventMessage::accept(). No class other than EventMessage
  // subclasses should be able to call accept(), but we can't use friend relationships here because friendships
  // are not inheirited. It would be better if this were private (they're public in Unity though), but it's too complex
  // for now.
  virtual void onLoop() {}
  virtual void onActorCreation() {}
  virtual void onActorDestruction() {}
  virtual void onCollision() {}

 private:
  // Only EventBus should be able to call receiveEvent(); IBehaviorComponent is (at present)
  // the only thing that should be recieving events from the EventBus, and it shouldn't recieve
  // them from anywhere else.
  friend EventBus;
  void receiveEvent(const EventMessage& message);

  // Unfortunately, initializeBindables has to exist here for now. It's a bit of a hack, but it's the only way to
  // get the WADLoader to be able to call it. (It would be better if this was in the LoadableBehaviorComponent class,
  // but because LoadableBehaviorComponent is a CRTP class, it's hard to do Liskov substitution with it)
  friend WADLoader;
  virtual void initializeBindables(const BehaviorComponentConfig& config) = 0;
};

/*
 * Whenever you subclass BehaviorComponent, you must register it with Sprawl. This is done by calling the
 * REGISTER_COMPONENT macro in the header file of the subclass. For example:
 *
 * class CombatComponent: public BehaviorComponent { ... };
 * REGISTER_COMPONENT(CombatComponent);
 */
#define REGISTER_COMPONENT(TYPE) static bool TYPE##_isRegistered = BehaviorComponentFactory::Register<TYPE>(#TYPE);
