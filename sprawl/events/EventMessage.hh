#pragma once
#include "Types.hh"

// fwd decls
class IBehaviorComponent;

typedef struct EventMessage {
  /*
   * Base class for all event messages. This is essentially a data class, but
   * it also implements the Visitor pattern.
   */
 public:
  EventMessage(UUID receiverId);
  EventMessage(UUID senderId, UUID receiverId);
  virtual ~EventMessage();
  virtual void accept(IBehaviorComponent& component) const = 0;

  UUID senderId;
  UUID receiverId;
  bool _fromEngine;
} EventMessage;

typedef struct OnLoopMessage : public EventMessage {
 public:
  OnLoopMessage(UUID receiverId);
  OnLoopMessage(UUID senderId, UUID receiverId);
  void accept(IBehaviorComponent& component) const override;
} OnLoopMessage;

typedef struct OnActorCreationMessage : public EventMessage {
 public:
  OnActorCreationMessage(UUID receiverId);
  OnActorCreationMessage(UUID senderId, UUID receiverId);
  void accept(IBehaviorComponent& component) const override;
} OnActorCreationMessage;

typedef struct OnActorDestructionMessage : public EventMessage {
 public:
  OnActorDestructionMessage(UUID receiverId);
  OnActorDestructionMessage(UUID senderId, UUID receiverId);
  void accept(IBehaviorComponent& component) const override;
} OnActorDestructionMessage;

typedef struct OnCollisionMessage : public EventMessage {
 public:
  OnCollisionMessage(UUID receiverId);
  OnCollisionMessage(UUID senderId, UUID receiverId);
  void accept(IBehaviorComponent& component) const override;
} OnCollisionMessage;
