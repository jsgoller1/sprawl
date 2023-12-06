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

typedef struct OnLoopMessage : public EventMessage {
 public:
  OnLoopMessage();
  void accept(IBehaviorComponent& component) const override;
} OnLoopMessage;

typedef struct OnActorCreationMessage : public EventMessage {
 public:
  OnActorCreationMessage(UUID receiverId);
  void accept(IBehaviorComponent& component) const override;
} OnActorCreationMessage;

typedef struct OnActorDestructionMessage : public EventMessage {
 public:
  OnActorDestructionMessage(UUID receiverId);
  void accept(IBehaviorComponent& component) const override;
} OnActorDestructionMessage;

typedef struct OnCollisionMessage : public EventMessage {
 public:
  OnCollisionMessage(UUID senderId, UUID receiverId);
  void accept(IBehaviorComponent& component) const override;
} OnCollisionMessage;
