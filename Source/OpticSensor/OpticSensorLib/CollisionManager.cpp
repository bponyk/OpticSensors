#include "stdafx.h"

#include "CollisionManager.h"
#include "Application.h"
#include "Controller.h"
#include "IObject.h"

#include <MathBase/math/Box3D.h>

#include <algorithm>
#include <map>
#include <set>

//////////////////////////////////////////////////////////////////////////

CollisionManager::CollisionManager()
  {  }

CollisionManager::~CollisionManager()
  {  }

void CollisionManager::Update()
  {
  std::map<ObjectPtr, std::set<ObjectPtr>> objects_collision_map;

  std::vector<ObjectPtr>& objects = Application::GetInstance().GetController().GetObjects();

  // oh my God, O(n^2) - this is ridiculous!!!
  // move realization to KD tree
  for (size_t i = 0; i < objects.size(); ++i)
    {
    ObjectPtr p_object = objects[i];
    Box3D object_bbox = p_object->GetBBox();
    
    for (size_t j = i + 1; j < objects.size(); ++j)
      {
      ObjectPtr p_candidate = objects[j];
      if (object_bbox.Intersects(p_candidate->GetBBox()))
        {
        objects_collision_map[p_object].insert(p_candidate);
        objects_collision_map[p_candidate].insert(p_object);
        }
        
      }
    }

  std::for_each(objects_collision_map.begin(), objects_collision_map.end(), [&objects](std::pair<ObjectPtr, std::set<ObjectPtr>> obj_pair)
    {
    obj_pair.first->CollisionDetected(obj_pair.second);
    });

  }