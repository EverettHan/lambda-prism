//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2015/11/24
//===================================================================

#ifndef EKAutoScalingCriterion_H
#define EKAutoScalingCriterion_H

#include "EKExportedByKernel.h"
#include <string>

namespace JSON
{
class JIStream;
class JOStream;
}

namespace EK
{
enum CriterionStrategy
{
  linearDistribution,
  linearDistributionByMemory,
  maximizeDistribution,
  cloud,
  onPremise,
  custom,
  maxStrategy
};

class ExportedByKernel AutoScalingStrategy
{
public:
  AutoScalingStrategy(const CriterionStrategy strategy = linearDistribution, unsigned int maxRAMPercent = 0);

  void Serialize(JSON::JOStream& jos) const;
  void SerializeV2(JSON::JOStream& jos) const;
  static AutoScalingStrategy UnSerialize(const JSON::JIStream& jis, std::string& error);
  static AutoScalingStrategy UnSerializeV2(const JSON::JIStream& jis, std::string& error);
  bool IsV2Strategy() const;

public:
  CriterionStrategy strategy_;
  unsigned int maxRAMPercent_;
};

class ExportedByKernel AutoScalingCriterion
{
public:
  static AutoScalingCriterion ByConnection(int maxConnections, double timeoutInSeconds, const AutoScalingStrategy& strategy, double reducedTimeoutInSeconds = -1.0);
  static AutoScalingCriterion ByIdentifier(double timeoutInSeconds, const AutoScalingStrategy& strategy, double reducedTimeoutInSeconds = -1.0);

  bool IsCompatible(const JSON::JIStream& jis) const;

  double GetTimeoutInSeconds() const;
  double GetReducedTimeoutInSeconds() const;

  int GetMaxNumConnectionsPerNode() const;
  AutoScalingStrategy GetStrategy() const;

  void Serialize(JSON::JOStream& jos) const;
  void SerializeV2(JSON::JOStream& jos, JSON::JOStream& pool) const;
  static AutoScalingCriterion UnSerialize(const JSON::JIStream& jis, std::string& error);
  static AutoScalingCriterion UnSerializeV2(const AutoScalingStrategy& strategy, const JSON::JIStream& jis, std::string& error);

private:
  AutoScalingCriterion(const AutoScalingStrategy& criterionStrategy, int maxNumConnectionsPerNode, double timeoutInSeconds, double reducedTimeoutInSeconds);

private:
  AutoScalingStrategy strategy_;
  int maxNumConnectionsPerNode_;
  double timeoutInSeconds_;
  double reducedTimeoutInSeconds_;
};

}

#endif /*EKAutoScalingCriterion_H*/
