#include "EntityManager.hh"
#include "PhysicsComponent.hh"
#include "Types.hh"

typedef string EntityName;

class Entity {
  shared_ptr<Identity> getIdentity() const;

 protected:
  Entity();
  ~Entity();

 private:
  shared_ptr<Identity> identity;
  shared_ptr<EntityName> name;

  // NOTE: This is a technique we use to allow for covariant returns
  // with smart pointers; unfortunately, it doesn't also work for
  // setters because of restrictions on parameters that don't apply to
  // return types. We might be able to get a complicated solution mixing
  // inheiritance and templates, but we'll settle with some unfortunate name
  // hiding for now.
  // https://www.fluentcpp.com/2017/09/12/how-to-return-a-smart-pointer-and-use-covariance/

  virtual void setPhysicsComponent_impl(PhysicsComponent* const comp) = 0;
  virtual PhysicsComponent* getPhysicsComponent_impl() const = 0;
};
