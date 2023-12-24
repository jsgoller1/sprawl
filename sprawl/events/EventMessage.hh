#pragma once
#include "Types.hh"

// fwd decls
class IBehaviorComponent;

/*
 * Base class for all event messages. This is essentially a data class, but
 * it also implements the Visitor pattern.
 *
 * UUID senderId: the UUID of the Actor that sent the message. If empty,
 * indicates that the message was sent by the engine itself.
 *
 * UUID receiverId: the UUID of the Actor that should receive the message.
 * If empty, indicates that the message should be broadcast to all Actors.
 */
typedef struct EventMessage {
 public:
  EventMessage(UUID senderId = "", UUID receiverId = "");
  virtual ~EventMessage();
  virtual void accept(IBehaviorComponent& component) const = 0;

  UUID senderId;
  UUID receiverId;
} EventMessage;

/*
 * Message broadcast to all Actors on every game loop.
 */
typedef struct GameLoopMessage : public EventMessage {
 public:
  GameLoopMessage();
  void accept(IBehaviorComponent& component) const override;
} GameLoopMessage;

/*
 * Message sent to an actor when it is created.
 */
typedef struct ActorCreationMessage : public EventMessage {
 public:
  ActorCreationMessage(UUID receiverId);
  void accept(IBehaviorComponent& component) const override;
} ActorCreationMessage;

/*
 * Message sent to an actor when it is destroyed.
 */
typedef struct ActorDestructionMessage : public EventMessage {
 public:
  ActorDestructionMessage(UUID receiverId);
  void accept(IBehaviorComponent& component) const override;
} ActorDestructionMessage;

/*
 * Message sent to an actor when it collides with another actor.
 */
typedef struct CollisionMessage : public EventMessage {
 public:
  CollisionMessage(UUID senderId, UUID receiverId);
  void accept(IBehaviorComponent& component) const override;
} CollisionMessage;
