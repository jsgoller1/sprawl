#include "EventMessage.hh"

#include "IBehaviorComponent.hh"

/*
 * EventMessage subclasses implement the Visitor pattern. We don't want BehaviorComponents to have to do
 * dynamic_casts to figure out what kind of message they're getting, so we use the Visitor pattern to
 * dispatch the message to the correct method. Tradeoff: Messages now know about the methods of IBehaviorComponent.
 */

EventMessage::EventMessage(UUID senderId, UUID receiverId) : senderId(senderId), receiverId(receiverId){};
EventMessage::~EventMessage() = default;

OnLoopMessage::OnLoopMessage() : EventMessage("", ""){};
void OnLoopMessage::accept(IBehaviorComponent& component) const { component.onLoop(); };

OnActorCreationMessage::OnActorCreationMessage(UUID receiverId) : EventMessage("", receiverId){};
void OnActorCreationMessage::accept(IBehaviorComponent& component) const { component.onActorCreation(); };

OnActorDestructionMessage::OnActorDestructionMessage(UUID receiverId) : EventMessage("", receiverId){};
void OnActorDestructionMessage::accept(IBehaviorComponent& component) const { component.onActorDestruction(); };

OnCollisionMessage::OnCollisionMessage(UUID senderId, UUID receiverId) : EventMessage(senderId, receiverId){};
void OnCollisionMessage::accept(IBehaviorComponent& component) const { component.onCollision(); };
