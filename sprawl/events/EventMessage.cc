#include "EventMessage.hh"

#include "IBehaviorComponent.hh"

/*
 * EventMessage subclasses implement the Visitor pattern. We don't want BehaviorComponents to have to do
 * dynamic_casts to figure out what kind of message they're getting, so we use the Visitor pattern to
 * dispatch the message to the correct method. Tradeoff: Messages now know about the methods of IBehaviorComponent.
 */

EventMessage::EventMessage(UUID senderId, UUID receiverId)
    : senderId(senderId), receiverId(receiverId), _fromEngine(false){};

EventMessage::EventMessage(UUID receiverId) : senderId(""), receiverId(receiverId), _fromEngine(true){};
EventMessage::~EventMessage() = default;

bool EventMessage::fromEngine() const { return this->_fromEngine; };

OnLoopMessage::OnLoopMessage(UUID receiverId) : EventMessage(receiverId){};
OnLoopMessage::OnLoopMessage(UUID senderId, UUID receiverId) : EventMessage(senderId, receiverId){};
void OnLoopMessage::accept(IBehaviorComponent& component) const { component.onLoop(); };

OnActorCreationMessage::OnActorCreationMessage(UUID receiverId) : EventMessage(receiverId){};
OnActorCreationMessage::OnActorCreationMessage(UUID senderId, UUID receiverId) : EventMessage(senderId, receiverId){};
void OnActorCreationMessage::accept(IBehaviorComponent& component) const { component.onActorCreation(); };

OnActorDestructionMessage::OnActorDestructionMessage(UUID receiverId) : EventMessage(receiverId){};
OnActorDestructionMessage::OnActorDestructionMessage(UUID senderId, UUID receiverId)
    : EventMessage(senderId, receiverId){};
void OnActorDestructionMessage::accept(IBehaviorComponent& component) const { component.onActorDestruction(); };

OnCollisionMessage::OnCollisionMessage(UUID receiverId) : EventMessage(receiverId){};
OnCollisionMessage::OnCollisionMessage(UUID senderId, UUID receiverId) : EventMessage(senderId, receiverId){};
void OnCollisionMessage::accept(IBehaviorComponent& component) const { component.onCollision(); };
