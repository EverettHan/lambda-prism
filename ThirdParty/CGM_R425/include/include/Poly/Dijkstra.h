// COPYRIGHT DASSAULT SYSTEMES 2021, ALL RIGHTS RESERVED.
//===================================================================
//
// Dijkstra.h
// generic impl useful for proto & avoid dupl
//
//===================================================================
// Sept 2021 : F1Z : Creation
// 
//===================================================================

#pragma once

#ifndef _AIX

#pragma push_macro("max")
#undef max

//std
#include <functional>
#include <map>
#include <utility>
#include <queue>
#include <set>

namespace Poly
{
  // node and weight only
  // can not have severals bar between node
  template<typename Index, typename Weight>
  HRESULT Dijkstra(const Index iStart,
                   const Index iEnd,
                   std::function<HRESULT(const Index&, std::map<Index, Weight>&)>& iGetNeighb,
                   std::map<Index, std::pair<Index, Weight> >& oResult);

  // node and weight only
  // can not have severals bar between node
  // can provide a max weight value to stop the search
  template<typename Index, typename Weight>
  HRESULT Dijkstra(const Index iStart,
                   const Index iEnd,
                   std::function<HRESULT(const Index &, std::map<Index, Weight> &)> & iGetNeighb,
                   Weight iStopWeight,
                   bool & oIsEndReached,
                   std::map<Index, std::pair<Index, Weight> > & oResult);

  // node and bar
  // can have severals bars with different weight connection two nodes
  template<typename Index, typename IndexBar, typename Weight>
  HRESULT Dijkstra(const Index iStart,
                   const Index iEnd,
                   std::function<HRESULT(const Index, std::set<IndexBar>&)>& iGetNeighb,
                   std::function<Index(const IndexBar, const Index)>& iGetOtherNode,
                   std::function<Weight(const IndexBar)>& iGetWeigth,
                   std::map<Index, std::pair<IndexBar, Weight> >& oResult);
           
};

template<typename Index, typename Weight>
HRESULT Poly::Dijkstra(const Index iStart,
                       const Index iEnd,
                       std::function<HRESULT(const Index&, std::map<Index, Weight>&)>& iGetNeighb,
                       std::map<Index, std::pair<Index, Weight> >& oResult)
{
  HRESULT hr = S_OK;

  oResult.clear();

  auto comp = [](const std::pair<Index, Weight>& a, const std::pair<Index, Weight>& b)
  {
    return a.second > b.second;
  };

  std::priority_queue<std::pair<Index, Weight>, std::vector<std::pair<Index, Weight>>, decltype(comp)> Q(comp);
  Q.emplace(std::piecewise_construct,
            std::forward_as_tuple(iStart),
            std::forward_as_tuple());
  oResult.emplace(iStart, std::make_pair(iStart, 0));

  std::map<Index, Weight> neighb;

  while (!Q.empty() && SUCCEEDED(hr))
  {
    Index  v = Q.top().first;
    Weight w = Q.top().second;
    Q.pop();

    if (v!=iEnd && w <= oResult[v].second) // the best path
    {
      hr = iGetNeighb(v, neighb);
      for (auto iteN = neighb.begin(); iteN != neighb.end() && SUCCEEDED(hr); ++iteN)
      {
        Index vN = iteN->first;
        Weight addW = iteN->second;

        auto & result = oResult.emplace(vN, std::make_pair(v, std::numeric_limits<Weight>::max())).first->second;
        if ((w+addW) < result.second)
        {
          result.second = w + addW;
          result.first = v;
          Q.push(std::make_pair(vN, result.second));
        }
      }
    }
    
  }

  return hr;
}

template<typename Index, typename Weight>
HRESULT Poly::Dijkstra(const Index iStart,
                       const Index iEnd,
                       std::function<HRESULT(const Index &, std::map<Index, Weight> &)> & iGetNeighb,
                       Weight iStopWeight,
                       bool & oIsEndReached,
                       std::map<Index, std::pair<Index, Weight> > & oResult)
{
  HRESULT hr = S_OK;
  oIsEndReached = true;

  oResult.clear();

  auto comp = [](const std::pair<Index, Weight> & a, const std::pair<Index, Weight> & b)
  {
    return a.second > b.second;
  };

  std::priority_queue<std::pair<Index, Weight>, std::vector<std::pair<Index, Weight>>, decltype(comp)> Q(comp);
  Q.emplace(std::piecewise_construct,
            std::forward_as_tuple(iStart),
            std::forward_as_tuple());
  oResult.emplace(iStart, std::make_pair(iStart, 0));

  std::map<Index, Weight> neighb;

  while (!Q.empty() && SUCCEEDED(hr))
  {
    Index  v = Q.top().first;
    Weight w = Q.top().second;
    Q.pop();

    if (w > iStopWeight)
    {
      oIsEndReached = false;
      break;
    }

    if (v != iEnd && w <= oResult[v].second) // the best path
    {
      hr = iGetNeighb(v, neighb);
      for (auto iteN = neighb.begin(); iteN != neighb.end() && SUCCEEDED(hr); ++iteN)
      {
        Index vN = iteN->first;
        Weight addW = iteN->second;

        auto & result = oResult.emplace(vN, std::make_pair(v, std::numeric_limits<Weight>::max())).first->second;
        if ((w + addW) < result.second)
        {
          result.second = w + addW;
          result.first = v;
          Q.push(std::make_pair(vN, result.second));
        }
      }
    }

  }

  if(oResult[iEnd].second>iStopWeight)
    oIsEndReached = false; // the end seems to be reached but at a too high value, so not reached in fact.

  return hr;
}



template<typename Index, typename IndexBar, typename Weight>
HRESULT Poly::Dijkstra(const Index iStart,
                       const Index iEnd,
                       std::function<HRESULT(const Index, std::set<IndexBar>&)>& iGetNeighb,
                       std::function<Index(const IndexBar, const Index)>& iGetOtherNode,
                       std::function<Weight(const IndexBar)>& iGetWeigth,
                       std::map<Index, std::pair<IndexBar, Weight> >& oResult)
{
  HRESULT hr = S_OK;

  oResult.clear();

  auto comp = [](const std::pair<Index, Weight>& a, const std::pair<Index, Weight>& b)
  {
    return a.second > b.second;
  };

  std::priority_queue<std::pair<Index, Weight>, std::vector<std::pair<Index, Weight>>, decltype(comp)> Q(comp);
  Q.emplace(std::piecewise_construct,
            std::forward_as_tuple(iStart),
            std::forward_as_tuple());
  oResult.emplace(iStart, std::make_pair(iStart, 0));

  std::set<IndexBar> neighb;

  while (!Q.empty() && SUCCEEDED(hr))
  {
    Index  v = Q.top().first;
    Weight w = Q.top().second;
    Q.pop();

    if (v!=iEnd && w <= oResult[v].second) // the best path
    {
      hr = iGetNeighb(v, neighb);
      for (auto iteN = neighb.begin(); iteN != neighb.end() && SUCCEEDED(hr); ++iteN)
      {
        IndexBar bN = *iteN;
        Index vN = iGetOtherNode(bN, v);
        Weight addW = iGetWeigth(bN);

        auto &result = oResult.emplace(vN, std::make_pair(bN, std::numeric_limits<Weight>::max())).first->second;
        if ((w + addW) < result.second)
        {
          result.second = w + addW;
          result.first = bN;
          Q.push(std::make_pair(vN, result.second));
        }
      }
    }

  }


  return hr;
}

#pragma pop_macro("max")
#endif
