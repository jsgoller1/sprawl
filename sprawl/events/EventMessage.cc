#include "EventMessage.hh"

#include "IBehaviorComponent.hh"

/*
 * EventMessage subclasses implement the Visitor pattern. We don't want BehaviorComponents to have to do
 * dynamic_casts to figure out what kind of message they're getting, so we use the Visitor pattern to
 * dispatch the message to the correct method. Tradeoff: Messages now know about the methods of IBehaviorComponent.
 */

EventMessage::EventMessage(UUID senderId, UUID receiverId) : senderId(senderId), receiverId(receiverId){};
EventMessage::~EventMessage() = default;

GameLoopMessage::GameLoopMessage() : EventMessage("", ""){};
void GameLoopMessage::accept(IBehaviorComponent& component) const { component.onGameLoop(); };

ActorCreationMessage::ActorCreationMessage(UUID receiverId) : EventMessage("", receiverId){};
void ActorCreationMessage::accept(IBehaviorComponent& component) const { component.onActorCreation(); };

ActorDestructionMessage::ActorDestructionMessage(UUID receiverId) : EventMessage("", receiverId){};
void ActorDestructionMessage::accept(IBehaviorComponent& component) const { component.onActorDestruction(); };

CollisionMessage::CollisionMessage(UUID senderId, UUID receiverId) : EventMessage(senderId, receiverId){};
void CollisionMessage::accept(IBehaviorComponent& component) const { component.onCollision(); };
