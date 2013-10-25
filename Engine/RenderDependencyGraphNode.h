/*
 * File :
 *      ./Engine/RenderEngineDependencyGraph.h
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      This is the base node structure is used in RenderDependenciesGraph
 *
 *      All other node types inherit this class
 */

#ifndef _F_H_RENDER_DEPENDENCY_GRAPH_NODE_
#define _F_H_RENDER_DEPENDENCY_GRAPH_NODE_

#include <list>
#include <map>

class  RenderDependencyNodeBase {
  private:
    //WEIGHT is a constant of that is changed per node type
    const int WEIGHT = -1;

  protected:
    //Parent Node
    RenderDependencyNodeBase* parent;

    //Self
    std::list<RenderDependencyNodeBase*>::iterator self;

    //Children List
    //Explanation of map of lists
    //  We map the weight to each list
    //  Complexity (n is node types, m is number of nodes in list)
    //   - Insertion: log n
    //   - Deletion: constant time
    //   - Traverse: linear time (n * m)
    std::map<int, std::list<RenderDependencyNodeBase*> > children;

  public:
    //Get node Constant
    const int getWeight();

    //Do whatever it is this node does
    //Base node does nothing
    void parseNode();
};

#endif //_F_H_RENDER_DEPENDANCY_GRAPH_NODE_
