#pragma once

#include <MathBase\math\Box3D.h>

enum class ObjectType : char
{
	OT_BOX,
	OT_EMITTER,
	OT_DETECTOR,
	OT_RAY
};

class IObject
{
protected:
  bool m_to_delete;
public:
  IObject():m_to_delete(false){}
	virtual ~IObject(){}

	virtual void Update(long i_elpsed_time) = 0;
	virtual void Render() = 0;
  bool         ToDelete() {return m_to_delete;}

	virtual Box3D GetBBox() const = 0;
  virtual void  CollisionDetected(const std::set<std::shared_ptr<IObject>>& i_objects) = 0;
};

typedef std::shared_ptr<IObject> ObjectPtr;