//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2014/03/10
//===================================================================

#ifndef EKHypervisorSettings_H
#define EKHypervisorSettings_H

#include "EKExportedByKernel.h"
#include "DSUnicodeString.h"

namespace JSON
{
class JIStream;
class JOStream;
}

namespace EK
{
class AuthenticationSettings;
class AutoScalingCriterion;
class Context;
class ExecuteAutoScalingOptions;
class HypervisorSettingsImpl;

class ExportedByKernel HypervisorSettings
{
public:
   HypervisorSettings();
  ~HypervisorSettings();

  HypervisorSettings(const HypervisorSettings&) = delete;
  HypervisorSettings& operator=(const HypervisorSettings&) = delete;

public:
  /**
   * Read the settings from a file.
   */
  bool LoadFromFile(const CATUnicodeString& filename);
  bool LoadFromFile(const CATUnicodeString& filename, Context& context);

  /**
   * Set the address used for connections to this Hypervisor.
   */
  HypervisorSettings& SetPublicAddress(const CATUnicodeString& publicAddress);

  /**
   * Set the ports that can be used by Nodes from this Hypervisor for connection with web Nodes.
   * You can specify multiple port numbers, separated by commas. You can also include a range of port numbers by separating the low and high values with a hyphen.
   */
  HypervisorSettings& SetWebSocketRange(const CATUnicodeString& webSocketRange);

  /**
  * Set the private IP used for connections to this Hypervisor.
  */
  HypervisorSettings& SetPrivateIP(const CATUnicodeString& privateIP);

  /**
   * Set the ports that can be used by Nodes from this Hypervisor for connection with C++ Nodes.
   * You can specify multiple port numbers, separated by commas. You can also include a range of port numbers by separating the low and high values with a hyphen.
   */
  HypervisorSettings& SetSocketRange(const CATUnicodeString& socketRange);

  /**
   * Set the certificate file (PEM format) used by this Hypervisor.
   */
  HypervisorSettings& SetCertificate(const CATUnicodeString& certificate);

  /**
   * Set the private key file (PEM format, no passphrase) used by this Hypervisor.
   */
  HypervisorSettings& SetPrivateKey(const CATUnicodeString& privateKey);

  /**
   * Set the group key of this Hypervisor. Used by the scale out probe to filter hypervisors.
   */
  HypervisorSettings& SetGroup(const CATUnicodeString& group);

  /**
   * Set the instance ID of the Hypervisor's VM. Used by the scale in to remove VM.
   */
  HypervisorSettings& SetVmInstanceId(const CATUnicodeString& vmInstanceId);

  /**
   * Set the instance number of the Hypervisor's VM. Used to exclude VM0 from the scale in.
   */
  HypervisorSettings& SetVmInstanceNumber(int vmInstanceNumber);

  /**
   * Set the initial count to define how many clones of this VM Definition will be deployed. Used to prevent scale in if the number of clones <= vmInitialCount.
   */
  HypervisorSettings& SetVmInitialCount(int vmInitialCount);

  /**
   * Set the socket port used by this Hypervisor.
   */
  HypervisorSettings& SetSocketPort(int port);

  /**
   * Set the websocket port used by this Hypervisor.
   */
  HypervisorSettings& SetWebSocketPort(int port);

  /**
   * Set the Hypervisor to only accept incoming connection from localhost.
   */
  HypervisorSettings& SetOnlyLocalConnection();

  /**
   * Set the ElasticScalability key of this Hypervisor. Parameters specify the CSI function to call.
   */
  HypervisorSettings& SetElasticScalability(int version, double updateInSeconds, const CATUnicodeString& pool, const CATUnicodeString& function, int functionVersion, const CATUnicodeString& CATInstallPath);

  /**
   * Add auto scaling to a pool. New virtual machines and new nodes will be added when the autoScalingCriterion is met.
   */
  HypervisorSettings& AddAutoScaling(const CATUnicodeString& poolName,
                                     const ExecuteAutoScalingOptions& execute,
                                     const AutoScalingCriterion& autoScalingCriterion,
                                     int maxNumberOfNodes = defaultMaxNumberOfNodes,
                                     bool limitConnectionToFirstCASUser = false,
                                     int minNumberOfNodes = 0);

  /**
   * Set the mapping between URIs and the associated websocket port.
   */
  HypervisorSettings& SetReverseProxyURIs(const JSON::JIStream& jis);
  HypervisorSettings& SetReverseProxyURIs(const JSON::JOStream& jos);

  /**
  * Set the reverse proxy mapper (a script returning a valid URI to the hypervisor).
  */
  HypervisorSettings& SetReverseProxyMapper(const CATUnicodeString& mapper);

  /**
  * Set the reverse proxy timeout in seconds.
  * The reverse proxy mapper must give a response before this timeout.
  */
  HypervisorSettings& SetReverseProxyTimeoutInSeconds(double timeoutInSeconds);

  /**
   * Add CAS Authentication for this Hypervisor.
   */
  HypervisorSettings& AddAuthentication(const AuthenticationSettings& authenticationSettings);

public:
  static const int defaultMaxNumberOfNodes = 1000;
  static const int defaultMinNumberOfNodes = 0;

private:
  HypervisorSettingsImpl* impl_;
  friend HypervisorSettingsImpl& getImpl(const HypervisorSettings& settings);
};
}

#endif /*EKHypervisorSettings_H*/
