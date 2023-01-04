#ifndef HealingControlMode_h_
#define HealingControlMode_h_

/**
  * Defines the healing control mode.
  * @param    global
  * The global continuity of the body has to be improved by the
  * healing process for a given order.
  * @param   local   
  * For a given order the continuity of each edge has to be improved by the
  * healing process (No degradation is authorized for the given order relatively 
  * to the corresponding tolerance).
  * @param   strict
  * For a given order the continuity of each edge has to be improved by the
  * healing process (No degradation is authorized for the given order relatively 
  * to a percentage of the initial default).
  */
enum CATHealingControlMode {CATHealingControlMode_global , CATHealingControlMode_local , CATHealingControlMode_strict};

#endif /* HealingControlMode_h_ */
