//==============================================================================================================
// Copyright Dassault Systemes Provence 2013-2016, All Rights Reserved 
//==============================================================================================================
// Usage notes:
//==============================================================================================================
// 2020-04-10 - rno : Controle que les vecteurs d'entrées sont non vide pour appeler begin dessus
// 2016-08-18 - MMO : Ajout de #include <iterator>  pour corriger l'erreur de compilation VS2015
// 2014-09-02 - T6L : Sweep line for box rejection;
// 2014-06-23 - T6L : Pixellization of box rejection;
//==============================================================================================================


#ifndef CATExpSweepLineBoxRejection_H
#define CATExpSweepLineBoxRejection_H

#include "CATExpBoundingBox.h"

#include <vector>
#include <deque>
#include <set>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <functional>
#include <iterator> 
#include <iostream>


// template <class Object1, class Object2>
// struct CATExpSweepLineTypes
// {
  // typedef std::set<Object1> std::set<Object1>;
  // typedef std::set<Object2> std::set<Object2>;
  // typedef std::vector<std::pair<double, Object1> > VectorCoords1;
  // typedef std::vector<std::pair<double, Object2> > VectorCoords2;
  // typedef std::unordered_map<Object1, std::deque<Object2> > CandidatesMap12;
  // typedef std::unordered_map<Object2, std::deque<Object1> > CandidatesMap21;
// };

/**
* @pre We can iterate over Input1 deterministically.
*/
template <class Object1, class Input1, class Output1, class Object2>
class CATExpSweepLineHelper /*: private CATExpSweepLineTypes<Object1, Object2>*/ //c'est pas la peine de faire une dérivation juste pour définir trois typedef...
{
  template <class, class, class> friend class CATExpSweepLineBoxRejection;
  template <class, class, class, class, class, class> friend class CATExpSweepLineDualBoxRejection;

  static void RecordBoundingBoxes( const Input1 &input, const std::function<const CATExpBoundingBox * (const Object1 &)> &bounding_box_getter,
							      std::vector<std::pair<double, Object1>> &min_x,  std::vector<std::pair<double, Object1>> &max_x, 
								   std::vector<std::pair<double, Object1>> &min_y,  std::vector<std::pair<double, Object1>> &max_y )
  {
    auto const size = input.size();
    min_x.reserve(size);
    max_x.reserve(size);
    min_y.reserve(size);
    max_y.reserve(size);
    for (const auto &object : input)
    {
      auto bb = bounding_box_getter(object);
      min_x.push_back(std::make_pair(bb->x_lb, object));
      max_x.push_back(std::make_pair(bb->x_ub, object));
      min_y.push_back(std::make_pair(bb->y_lb, object));
      max_y.push_back(std::make_pair(bb->y_ub, object));
    }

    std::sort(min_x.begin(), min_x.end());
    std::sort(max_x.begin(), max_x.end());
    std::sort(min_y.begin(), min_y.end());
    std::sort(max_y.begin(), max_y.end());
  }

  static void Record
  (
    typename std::vector<std::pair<double, Object1>>::const_iterator &min1,
    std::set<Object1> &active_objects1, std::set<Object2> &active_objects2,
    std::unordered_map<Object1, std::deque<Object2> > &candidates1, std::unordered_map<Object2, std::deque<Object1> > &candidates2
  )
  {
    for (const auto &object2 : active_objects2)
    { 
      candidates2[object2].push_back(min1->second);
      candidates1[min1->second].push_back(object2);
    }
    active_objects1.insert(min1->second);
    ++min1;
  }

  static void Erase (typename std::vector<std::pair<double, Object1>>::const_iterator &max1, std::set<Object1> &active_objects1)
  {
    active_objects1.erase(max1->second);
    ++max1;
  }

  static void IntersectCandidates
    (const Input1 &input, std::unordered_map<Object1, std::deque<Object2> > &x_candidates, std::unordered_map<Object1, std::deque<Object2> > &y_candidates, Output1 &result)
  {
    for (const auto &element : input)
    {
      std::sort(x_candidates[element].begin(), x_candidates[element].end());
      std::sort(y_candidates[element].begin(), y_candidates[element].end());
      std::set_intersection(x_candidates[element].begin(), x_candidates[element].end(),
        y_candidates[element].begin(), y_candidates[element].end(), std::back_inserter(result[element]));
    }
  }
};

//template <class Object1, class Object2>
//class CATExpSweepLineDualHelper
//{
//  template <class> friend class CATExpSweepLineBoxRejection;
//  template <class, class> friend class CATExpSweepLineDualBoxRejection;
//
//  typedef std::vector<std::pair<double, Object1> > std::vector<std::pair<double, Object1> >;
//  typedef std::map<Object1, std::deque<Object2> > Map1;
//  typedef std::map<Object2, std::deque<Object1> > Map2;
//
//};
//
//

/**
* @pre We can iterate over Input deterministically.
* @pre result is allocated: result[i] is an empty sequential container for all i in input.
*/
template <class Object, class Input, class Output>
class CATExpSweepLineBoxRejection /*: private CATExpSweepLineTypes<Object, Object>*/ //c'est pas la peine de faire une dérivation juste pour définir trois typedef...
{
public:
  static void Compute
  (
    const Input &input,
    const std::function<const CATExpBoundingBox * (const Object &)> &bounding_box_getter,
    Output &result
  )
  {
    std::vector<std::pair<double, Object> > min_x, max_x, min_y, max_y;
    std::unordered_map<Object, std::deque<Object> > x_candidates, y_candidates;

    CATExpSweepLineHelper<Object, Input, Output, Object>::RecordBoundingBoxes
      (input, bounding_box_getter, min_x, max_x, min_y, max_y);

    CATExpSweepLineBoxRejection<Object,Input,Output>::ComputeCandidatesAlongOneCoordinate(min_x, max_x, x_candidates);
    CATExpSweepLineBoxRejection<Object,Input,Output>::ComputeCandidatesAlongOneCoordinate(min_y, max_y, y_candidates);

    return CATExpSweepLineHelper<Object, Input, Output, Object>::IntersectCandidates
      (input, x_candidates, y_candidates, result);
  }
  
private:
  static void ComputeCandidatesAlongOneCoordinate
    (const std::vector<std::pair<double, Object> > &min_vector, const std::vector<std::pair<double, Object> > &max_vector, std::unordered_map<Object, std::deque<Object> > &map)
  {
	   //std::cout << "CATExpSweepLineBoxRejection::ComputeCandidatesAlongOneCoordinate"<< std::endl;
    if (min_vector.empty() || max_vector.empty()){       std::cout << "CATExpSweepLineBoxRejection::ComputeCandidatesAlongOneCoordinate empty input vectors " << std::endl;    return;}
    std::set<Object> active_objects;
    auto min = min_vector.begin(), max = max_vector.begin();
    const auto min_end = min_vector.end()/*, max_end = max_vector.end()*/;//RNO : max_end unused

    while (min < min_end)
    {
      if (min->first <= max->first) CATExpSweepLineHelper<Object, Input, Output, Object>::Record
        (min, active_objects, active_objects, map, map);
      else CATExpSweepLineHelper<Object, Input, Output, Object>::Erase(max, active_objects);
    }
  }

};


/**
* @pre We can iterate over Input deterministically.
* @pre result is allocated: result[i] is an empty sequential container for all i in input.
*/
template <class Object1, class Input1, class Output1, class Object2, class Input2, class Output2>
class CATExpSweepLineDualBoxRejection /*: private CATExpSweepLineTypes<Object1, Object2>*/ //c'est pas la peine de faire une dérivation juste pour définir trois typedef...
{
public:
  static void Compute
  (
    const Input1 &input1,
    const std::function<const CATExpBoundingBox * (const Object1 &)> &bounding_box_getter1,
    Output1 &result1,
    const Input2 &input2,
    const std::function<const CATExpBoundingBox * (const Object2 &)> &bounding_box_getter2,
    Output2 &result2
  )
  {
    std::vector<std::pair<double, Object1> > min_x1, max_x1, min_y1, max_y1;
    std::vector<std::pair<double, Object2> >  min_x2, max_x2, min_y2, max_y2;
    std::unordered_map<Object1, std::deque<Object2> > x_candidates1, y_candidates1;
    std::unordered_map<Object2, std::deque<Object1> > x_candidates2, y_candidates2;

    CATExpSweepLineHelper<Object1, Input1, Output1, Object2>::RecordBoundingBoxes
      (input1, bounding_box_getter1, min_x1, max_x1, min_y1, max_y1);
    CATExpSweepLineHelper<Object2, Input2, Output2, Object1>::RecordBoundingBoxes
      (input2, bounding_box_getter2, min_x2, max_x2, min_y2, max_y2);

    ComputeCandidatesAlongOneCoordinate(min_x1, max_x1, min_x2, max_x2, x_candidates1, x_candidates2);
    ComputeCandidatesAlongOneCoordinate(min_y1, max_y1, min_y2, max_y2, y_candidates1, y_candidates2);

    CATExpSweepLineHelper<Object1, Input1, Output1, Object2>::IntersectCandidates
      (input1, x_candidates1, y_candidates1, result1);
    CATExpSweepLineHelper<Object2, Input2, Output2, Object1>::IntersectCandidates
      (input2, x_candidates2, y_candidates2, result2);
  }
  
private:
  static void ComputeCandidatesAlongOneCoordinate
  (
    const std::vector<std::pair<double, Object1> > &min_vector1, const std::vector<std::pair<double, Object1> > &max_vector1,
    const std::vector<std::pair<double, Object2> >  &min_vector2, const std::vector<std::pair<double, Object2> >  &max_vector2,
    std::unordered_map<Object1, std::deque<Object2> > &map1, std::unordered_map<Object2, std::deque<Object1> > &map2
  )
  {
    if (min_vector1.empty() || max_vector1.empty()) { std::cout << "CATExpSweepLineBoxRejection::ComputeCandidatesAlongOneCoordinate empty input vectors1" << std::endl;    return; }
    if (min_vector2.empty() || max_vector2.empty()) { std::cout << "CATExpSweepLineBoxRejection::ComputeCandidatesAlongOneCoordinate empty input vectors2" << std::endl;    return; }
    std::set<Object1> active_objects1;
    std::set<Object2> active_objects2;
    auto min1 = min_vector1.begin(), max1 = max_vector1.begin();
    auto min2 = min_vector2.begin(), max2 = max_vector2.begin();
    const auto min_end1 = min_vector1.end(), max_end1 = max_vector1.end();
    const auto min_end2 = min_vector2.end(), max_end2 = max_vector2.end();

    while (min1 < min_end1 || min2 < min_end2)
    {
      double min_coord = DBL_MAX;
      if (min1 < min_end1) min_coord = std::min<double>(min_coord, min1->first);
      if (max1 < max_end1) min_coord = std::min<double>(min_coord, max1->first);
      if (min2 < min_end2) min_coord = std::min<double>(min_coord, min2->first);
      if (max2 < max_end2) min_coord = std::min<double>(min_coord, max2->first);
      
      bool insertion = false;

      if (min1 < min_end1 && min_coord == min1->first)
      {
        CATExpSweepLineHelper<Object1, Input1, Output1, Object2>::Record
          (min1, active_objects1, active_objects2, map1, map2);
        insertion = true;
      }

      if (min2 < min_end2 && min_coord == min2->first)
      {
        CATExpSweepLineHelper<Object2, Input2, Output2, Object1>::Record
          (min2, active_objects2, active_objects1, map2, map1);
        insertion = true;
      }

      if (! insertion)
      {
        if (max1 < max_end1 && min_coord == max1->first)
          CATExpSweepLineHelper<Object1, Input1, Output1, Object2>::Erase (max1, active_objects1);

        if (max2 < max_end2 && min_coord == max2->first)
          CATExpSweepLineHelper<Object2, Input2, Output2, Object1>::Erase (max2, active_objects2);
      }
    }
  }
};







// Pixellization
//
//class GridMap
//{
//public:
//  GridMap() : x_min(DBL_MAX), x_max(DBL_MIN), y_min(DBL_MAX), y_max(DBL_MIN), x_length_(1), y_length_(1) {}
//
//  GridMap (double xmin, double xmax, double ymin, double ymax, unsigned x_len, unsigned y_len)
//  : x_min(xmin), x_max(xmax), y_min(ymin), y_max(ymax), x_length_(x_len), y_length_(y_len),
//    x_step_((xmax - xmin) / x_len), y_step_((ymax - ymin) / y_len) {}
//
//  void SetLengths(unsigned x_len, unsigned y_len)
//  { 
//    x_length_ = x_len;
//    y_length_ = y_len;
//    x_step_ = (x_max - x_min) / x_len;
//    y_step_ = (y_max - y_min) / y_len;
//  }
//
//  unsigned x_length() const { return x_length_; }
//  unsigned y_length() const { return y_length_; }
//
//  void Locate (const CATExpBoundingBox &box, unsigned &i_min, unsigned &i_max, unsigned &j_min, unsigned &j_max) const;
//
//  double x_right (unsigned i) const
//  {
//    if (i == x_length_ - 1) return x_max;
//    else return x_min + (i + 1) * x_step_;
//  }
//
//  double y_right (unsigned j) const
//  {
//    if (j == y_length_ - 1) return y_max;
//    else return y_min + (j + 1) * y_step_;
//  }
//
//  double x_min, x_max, y_min, y_max;
//
//private:
//  double x_step_, y_step_;
//  unsigned x_length_, y_length_;
//}; 
//
//
//class EquationsDispatcher
//{
//public:
//  typedef std::pair<std::deque<ArcsDeque>, std::deque<SegsDeque> > Box;
//  typedef std::vector<Box> Container;
//
//  EquationsDispatcher(const IntersectionParameters &intersection_parameters, const TranslationContext &translation_context)
//  : intersection_parameters_(intersection_parameters),
//    translation_context_(translation_context),
//    x_total_(0.), y_total_(0.), nb_elements_(0) {}
//
//  template <class ObjectsContainer>
//  int TakeIntoAccount (const ObjectsContainer &arcs_eqns);
//
//  void Init ();
//
//  void Register (ArcsVector &arcs_eqns);
//  void Register (SegsVector &segs_eqns);
//
//  Container &GetEquations() { return container_; }
//  
//  void PrintGrid () const; // for debug
//
//  //std::size_t x_length () const { return matrix_.size(); }
//  //std::size_t y_length () const { return matrix_[0].size(); }
//
//  //const std::deque<ArcsDeque> &GetArcs(unsigned i, unsigned j) const
//  //{ return matrix_[i][j].first; }
//
//  //const std::deque<SegsDeque> &GetSegs(unsigned i, unsigned j) const
//  //{ return matrix_[i][j].second; }
//
//private:
//  //typedef std::vector<EquationsRow> EquationsMatrix;
//  unsigned Linearize (unsigned i, unsigned j) const { return i + j * map_.x_length(); } 
//
//  Box &GetBox (unsigned i, unsigned j) { return container_[Linearize(i, j)]; }
//
//  Container container_;
//  GridMap map_;
//  const IntersectionParameters &intersection_parameters_;
//  const TranslationContext &translation_context_;
//  double x_total_, y_total_;
//  std::size_t nb_elements_;
//};


//} // namespace CATMathExp


#endif
